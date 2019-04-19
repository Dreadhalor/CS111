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
int port;
int client_socket_fd;

struct pollfd fds[1];

void intercept_input(int pipes[2], int shell_pid);
void create_shell();

void sigpipe_handler(int sig) {
  sigpipe = 1;
  int ugh = sig;
  sig = ugh;
  //signal(sig, sigpipe_handler);
}

int main(int argc, char *argv[]) {
  struct option options[]= {
		{"port", required_argument, 0, 'p'},
		{"log", required_argument, 0, 'l'},
		{"encrypt", required_argument, 0, 'e'},
		{"debug", no_argument, 0, 'd'}
	};

  char opt = -1;
	while((opt = getopt_long(argc, argv, "p:l:e:d", options, NULL)) != -1) {
		switch(opt) {
			case 'p':
        port = atoi(optarg);
				break;
      case 'l': break;
      case 'e': break;
      case 'd': break;
			default:
				error_out("Incorrect argument. Usage: lab1b-server [port p]\np: Port to open\n");
		}
	}

  server_socket_fd = create_server_socket(port);
  if (server_socket_fd < 0) {
    fprintf(stderr, "Error creating server socket.");
    exit(1);
  }

  client_socket_fd = accept(server_socket_fd, NULL, NULL);
  if (client_socket_fd < 0) error_out("Could not connect to client socket.");

  /*fds[0].fd = client_socket_fd;
  fds[0].events = POLLIN;



  while (1) {
    int pollval = poll(fds, 1, 0);
    if (pollval < 0) {
      error_out("Error polling for input from client!");
    } else {
      char buffer[BUFFER_SIZE];
      int len = recv(client_socket_fd, buffer, sizeof(buffer), 0);
      for (int i = 0; i < len; i++) {
        switch (buffer[i]) {
          default: write(, buffer[i]);
        }
      }
    }
  }*/

  create_shell();
  
  close(server_socket_fd);

  exit(0);
}

void intercept_input(int pipes[2], int shell_pid) {
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
      error_out("Could not poll sources.");
    if (shutdown && !(sources[1].revents & POLLIN)) {
      int shell_status = 0;
      if (waitpid(shell_pid, &shell_status, 0) == -1)
        error_out("Could not get shell exit status.");

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
                error_out("Failed to KILL shell.");
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
        send(client_socket_fd, input_buffer, n_read, 0);
        /*if (xwrite_noncanonical(STDOUT_FILENO, input_buffer, n_read)) {
          shutdown = 1;
          if (!closed) {
            close(pipes[WRITE_END]);
            closed = 1;
          }
        }*/
      } else if (sources[1].revents & (POLLERR | POLLHUP)) {
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
}

void create_shell() {
  int pipes[2];
  int pid = fork_and_set_pipes(pipes);
  if (pid == 0) {
    //child process: execute shell program
    //redirect stdin, stdout, stderr to shell
    redirect_stdio(pipes);

    if (execl("/bin/bash", "bash", (char*)NULL) == -1) {
      write(STDERR_FILENO, (void*)"Error: ", strlen("Error: "));
      error_out("Unable to execute shell.");
    }
  } else if (pid > 0) {
    //parent process: handle echoing of input and forwarding to shell
    intercept_input(pipes, pid);
  } else error_out("Failed to create child process.");
}