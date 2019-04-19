#include <unistd.h>
#include <errno.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/wait.h>
#include <signal.h>
#include <poll.h>

#include "fxns.c"

#define BUFFER_SIZE 64

#ifndef READ_END
#define READ_END 0
#endif

#ifndef WRITE_END
#define WRITE_END 1
#endif

int sigpipe = 0;

void intercept_input(int pipes[2], int shell_pid);
void create_shell();

int xwrite(int fd, const char *buf, size_t n_chars, int cr_lf);
int xwrite_shell(int fd, const char *buf, size_t n_chars, int shell_pid);
ssize_t xread(int fd, void *buf, size_t nbyte);

void sigpipe_handler();

int main(int argc, char *argv[]) {
  int open_shell = 0;
  // store initial termios settings
  store_termios_settings(&termios_init);

  // put terminal into non canonical no echo mode
  set_non_canonical_no_echo_mode(termios_init);

  struct option options[] = {
    {"shell", no_argument, NULL, 's'},
    {0, 0, 0, 0}
  };

  int opt = -1;
  opterr = 0;
  while ((opt = getopt_long(argc, argv, "", options, NULL)) != -1) {
    switch (opt) {
      case 's':
        open_shell = 1;
        break;
      case '?':
        error_out("Unknown option.", 0);
        break;
      default:
        error_out("Undefined option behavior.", 0);
        break;
    }
  }

  //options & args are parsed, now do stuff
  if (open_shell) create_shell();
  else parse_input(BUFFER_SIZE);

  //reset initial termios settings - congrats, nothing crashed
  tcsetattr(STDIN_FILENO, TCSANOW, &termios_init);
  return 0;
}

void create_shell() {
  int pipes[2];
  int pid = fork_and_set_pipes(pipes);
  if (pid == 0) {
    //child process: execute shell program
    //redirect stdin, stdout, stderr to shell
    redirect_stdio(pipes);

    if (execl("/bin/bash","bash") == -1) {
      write(STDERR_FILENO, (void*)"Error", strlen("Error"));
      error_out("Unable to execute shell.", 1);
    }
    

  } else if (pid > 0) {
    //parent process: handle echoing of input and forwarding to shell
    intercept_input(pipes, pid);
  } else error_out("Failed to create child process.", 1);
}

void intercept_input(int pipes[2], int shell_pid) {
  struct pollfd sources[2] = {
    {STDIN_FILENO, POLLIN, 0},
    {pipes[READ_END], POLLIN, 0}
  };
  signal(SIGPIPE, sigpipe_handler);

  int result = 0, closed = 0, shutdown = 0;
  char input_buffer[BUFFER_SIZE];
  ssize_t n_read = 0;

  while (1) {
    result = poll(sources, 2, 0);
    if (result == -1)
      error_out("Could not poll sources.", 1);
    if (shutdown && !(sources[1].revents & POLLIN)) {
      int shell_status = 0;
      if (waitpid(shell_pid, &shell_status, 0) == -1)
        error_out("Could not get shell exit status.", 1);

      fprintf(stderr,
        "SHELL EXIT SIGNAL=%d STATUS=%d\n",
        WTERMSIG(shell_status),
        WEXITSTATUS(shell_status)
      );
      return;
    }
    if (sources[0].revents != 0) {
      if (sources[0].revents & POLLIN) {
        n_read = xread(
          sources[0].fd,
          (void*)input_buffer,
          BUFFER_SIZE
        );
        xwrite_noncanonical(STDOUT_FILENO, input_buffer, n_read);
        if (!closed) {
          if (xwrite_shell(pipes[WRITE_END], input_buffer, n_read, shell_pid)) {
            close(pipes[WRITE_END]);
            closed = 1;
          }
        } else {
          int i = 0;
          for (i = 0; i < n_read; i++) {
            if (input_buffer[i] == 0x003) {
              if (kill(shell_pid, SIGINT) == -1)
                error_out("Failed to KILL shell.", 1);
            }
          }
        }

        if (sigpipe) {
          shutdown = 1;
          if (!closed) {
            close(pipes[WRITE_END]);
            closed = 1;
          }
        }
      } else fprintf(stderr, "Error polling stdin.\r\n");
    }
    if (sources[1].revents != 0) {
      if (sources[1].revents & POLLIN) {
        n_read = xread(sources[1].fd, (void*)input_buffer, BUFFER_SIZE);

        if (xwrite_noncanonical(STDOUT_FILENO, input_buffer, n_read)) {
          shutdown = 1;
          if (!closed) {
            close(pipes[WRITE_END]);
            closed = 1;
          }
        }
      } else if (sources[1].revents & (POLLERR | POLLHUP)) {
        shutdown = 1;
        if (!closed) {
          close(pipes[WRITE_END]);
          closed = 1;
        }
      }
    }
  }
}

void sigpipe_handler(int sig) {
  sigpipe = 1;
  signal(sig, sigpipe_handler);
}

ssize_t xread(int fd, void *buf, size_t nbyte) {
  ssize_t n_read = read(fd, buf, nbyte);

  if (n_read == -1)
    error_out("Failed to read from file.", 1);

  return n_read;
}

int xwrite_shell(int fd, const char *buf, size_t n_chars, int shell_pid) {
  unsigned int i = 0;
  ssize_t n_written = 0;

  for (; i < n_chars; i++) {
    switch (buf[i]) {
      case 0x003:
        if (kill(shell_pid, SIGINT) == -1) error_out("Could not KILL shell.", 1);
        fprintf(stderr, "Signal successfully forwarded!\r\n");
        break;
      case 0x004: return 1;
      case '\r':
        n_written = write(fd, "\n", 1);
        break;
      //case '\n': break;
      default:
        n_written = write(fd, buf + i, 1);
        break;
    }

    if (n_written == -1) error_out("Could not write to display.", 1);
  }
  fprintf(stderr,"%s", buf);

  return 0;
}