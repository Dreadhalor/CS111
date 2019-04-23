int create_socket(int port) {
  int socket_fd;
  struct sockaddr_in server_address;
  prepare_socket_vals(port, &socket_fd, &server_address);
	if (socket_fd < 0) return -1;

  int connected = connect(socket_fd, (struct sockaddr *) &server_address, sizeof(server_address));
  if (connected < 0) return -1;

  return socket_fd;
}

void poll_stdin(struct pollfd src, int socket_fd){
  if (src.revents & POLLIN) {
    char buffer[1024];
    int len = read(STDIN_FILENO, &buffer, sizeof(buffer));
    int i;
    for (i = 0; i < len; i++){
      switch (buffer[i]) {
        default: {
          write(STDOUT_FILENO, buffer + i, 1);
          write(socket_fd, buffer + i, 1);
        }
      }
    }
  }
}

void poll_server(struct pollfd src){
  if (src.revents & POLLIN) {
    char server_response[BUFFER_SIZE];
    int len = read(src.fd, &server_response, sizeof(server_response));
    for (int i = 0; i < len; i++){
      switch (server_response[i]) {
        default:
          write(STDOUT_FILENO, server_response + i, 1);
      }
    }
  }
}