#include "compression.c"

int create_socket(int port) {
  int socket_fd;
  struct sockaddr_in server_address;
  prepare_socket_vals(port, &socket_fd, &server_address);
	if (socket_fd < 0) return -1;

  int connected = connect(socket_fd, (struct sockaddr *) &server_address, sizeof(server_address));
  if (connected < 0) return -1;

  return socket_fd;
}

void poll_stdin(struct pollfd src, int socket_fd, FILE *logfile){
  if (src.revents & POLLIN) {
    char buffer[1024];
    int len = read(STDIN_FILENO, &buffer, sizeof(buffer));
    if (logfile) fprintf(logfile,"SENT %i bytes: %s\n", len, buffer);
    for (int i = 0; i < len; i++){
      switch (buffer[i]) {
        default: {
          write(STDOUT_FILENO, buffer + i, 1);
          write(socket_fd, buffer + i, 1);
        }
      }
    }
  }
}

void poll_server(struct pollfd src, int *close_flag, FILE *logfile){
  if (src.revents & POLLIN) {
    char server_response[1024];
    int len = read(src.fd, &server_response, sizeof(server_response));
    if (logfile && len > 0) fprintf(logfile, "RECEIVED %i bytes: %s\n", len, server_response);
    if (len == 0) *close_flag = 1;
    for (int i = 0; i < len; i++){
      switch (server_response[i]) {
        default:
          write(STDOUT_FILENO, server_response + i, 1);
      }
    }
  } else if (src.revents & (POLLERR | POLLHUP)){
    *close_flag = 1;
  }
}