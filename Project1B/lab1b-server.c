/*
#include <unistd.h>*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <getopt.h>
#include <poll.h>
#include <string.h>
#include <sys/wait.h>

#include "fxns.c"
#include "server-fxns.c"

#define N_POLL_SOURCES 3

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

#ifndef READ_END
#define READ_END 0
#endif

#ifndef WRITE_END
#define WRITE_END 1
#endif

int sigpipe = 0;
int server_socket_fd;
int port = 0;
int client_socket_fd;
int shell_pid;
int shell_fds[2];
int log_flag = 0;

struct pollfd fds[2];

void intercept_input(int pipes[2], int shell_pid);
int create_shell(int pipes[2]);

void sigpipe_handler(int sig) {
  sigpipe = 1;
  int ugh = sig;
  sig = ugh;
  //signal(sig, sigpipe_handler);
}


int main(int argc, char *argv[]) {
  struct option options[]= {
		{"port", required_argument, 0, 'p'},
		{"compress", no_argument, 0, 'c'}
	};

  char opt = -1;
	while((opt = getopt_long(argc, argv, "p:l:e:d", options, NULL)) != -1) {
		switch(opt) {
			case 'p':
        port = atoi(optarg);
				break;
      case 'c': break;
			default:
				error_out("Incorrect argument. Usage: lab1b-server [port p]\np: Port to open\n", 1);
		}
	}

  server_socket_fd = create_server_socket(port);
  if (server_socket_fd < 0) {
    fprintf(stderr, "Error creating server socket.");
    exit(1);
  }

  client_socket_fd = accept(server_socket_fd, NULL, NULL);
  if (client_socket_fd < 0) error_out("Could not connect to client socket.", 1);

  fds[0].fd = client_socket_fd;
  fds[0].events = POLLIN;

  shell_pid = create_shell(shell_fds);
  fds[1].fd = shell_fds[READ_END];
  fds[1].events = POLLIN;
  int shell_status = 0;

  signal(SIGPIPE, sigpipe_handler);

  while (1) {
    if (waitpid(shell_pid, &shell_status, WNOHANG)){
      sigpipe = 1;
      fprintf(stderr,
        "SHELL EXIT SIGNAL=%d STATUS=%d\n",
        WTERMSIG(shell_status),
        WEXITSTATUS(shell_status)
      );
    }
    if (sigpipe) break;
    int result = poll(fds, 2, 0);
    if (result < 0)
      error_out("Error polling for input from client!", 1);
    int test = poll_client(fds[0], shell_fds[WRITE_END], shell_pid, sigpipe);
    if (test < 0) break;
    poll_shell(fds[1], client_socket_fd, sigpipe);
  }
  
  close(server_socket_fd);

  exit(0);
}

/*oid intercept_input(int pipes[2], int shell_pid) {
  //input to shell
  struct pollfd sources[N_POLL_SOURCES] = {
    {STDIN_FILENO, POLLIN, 0},
    {pipes[READ_END], POLLIN, 0},
    {client_socket_fd, POLLIN, 0}
  };
  signal(SIGPIPE, sigpipe_handler);

  int result = 0, closed = 0, shutdown = 0;
  char input_buffer[BUFFER_SIZE];
  ssize_t n_read = 0;

  while (1) {
    result = poll(sources, N_POLL_SOURCES, 0);
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
        send(client_socket_fd, input_buffer, n_read, 0);*/
        /*if (xwrite_noncanonical(STDOUT_FILENO, input_buffer, n_read)) {
          shutdown = 1;
          if (!closed) {
            close(pipes[WRITE_END]);
            closed = 1;
          }
        }*/
      /*} else if (sources[1].revents & (POLLERR | POLLHUP)) {
        shutdown = 1;
        if (!closed) {
          close(pipes[WRITE_END]);
          closed = 1;
        }
      }
    }
    if (sources[2].revents != 0) {
      if (sources[2].revents & POLLIN) {
        char buffer[BUFFER_SIZE];
        int len = read(sources[2].fd, &buffer, sizeof(buffer));
        int i;
        for (i = 0; i < len; i++) {
          switch (buffer[i]) {
            default:
              write(pipes[1], buffer + i, 1);
              //printf("%c", buffer[i]);
          }
        }
      }
    }
  }

  exit(0);
}*/

int create_shell(int pipes[2]) {
  int pid = fork_and_set_pipes(pipes);
  if (pid == 0) {
    //child process: execute shell program
    //redirect stdin, stdout, stderr to shell
    redirect_stdio(pipes);

    if (execl("/bin/bash","bash", NULL) == -1) {
      write(STDERR_FILENO, (void*)"Error", strlen("Error"));
      error_out("Unable to execute shell.", 1);
    }

  } else if (pid > 0) {
    //parent process: handle echoing of input and forwarding to shell
    //intercept_input(pipes, pid);
    return pid;
  } else error_out("Failed to create child process.", 1);
  return 0;
}