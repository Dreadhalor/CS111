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
int compression_flag = 0;

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
	while((opt = getopt_long(argc, argv, "", options, NULL)) != -1) {
		switch(opt) {
			case 'p':
        port = atoi(optarg);
				break;
      case 'c':
        compression_flag = 1;
        break;
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
    int test = poll_client(fds[0], shell_fds[WRITE_END], shell_pid, sigpipe, compression_flag);
    if (test < 0) break;
    poll_shell(fds[1], client_socket_fd, sigpipe, compression_flag);
  }
  
  close(server_socket_fd);

  exit(0);
}

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