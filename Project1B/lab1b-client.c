/*#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>*/
#include <getopt.h>
#include <termios.h>
#include <string.h>
#include <poll.h>

#include "fxns.c"
#include "client-fxns.c"

void sigint_handler(int sig);
void intercept_input();

int socket_fd = -1;

int main(int argc, char *argv[]) {
	struct option options[]= {
		{"port", required_argument, 0, 'p'},
		{"log", required_argument, 0, 'l'},
		{"encrypt", required_argument, 0, 'e'},
		{"debug", no_argument, 0, 'd'}
	};
  int port;

  char opt = -1;
	while((opt=getopt_long(argc, argv, "p:l:e:d", options, NULL)) != -1) {
		switch(opt) {
			case 'p':
        port = atoi(optarg);
				break;
      case 'l': break;
      case 'e': break;
      case 'd': break;
			default:
				error_out("Incorrect argument. Usage: lab1b-client [port p]\np: Port to open\n", 1);
		}
	}

  //signal(SIGINT, sigint_handler);
	
  store_stdin_settings(&termios_init);
  set_non_canonical_no_echo_mode();
  socket_fd = create_socket(port);
  if (socket_fd < 0) {
    fprintf(stderr, "Could not connect to server. Error: ");
    error_out(strerror(errno), errno);
  }
  intercept_input();

  close(socket_fd);
  set_termios(termios_init);
  
	exit(0);
}

void sigint_handler(int sig) {
  int ugh = sig;
  sig = ugh;
}

void intercept_input() {
  struct pollfd sources[2] = {
    {STDIN_FILENO, POLLIN, 0},
    {socket_fd, POLLIN, 0}
  };
  //signal(SIGPIPE, sigpipe_handler);

  while (1) {
    int result = poll(sources, 2, 0);
    if (result == -1)
      error_out("Could not poll sources.", 1);
    poll_stdin(sources[0], socket_fd);
    poll_server(sources[1]);
  }
}