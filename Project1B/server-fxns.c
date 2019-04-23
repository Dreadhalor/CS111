int create_server_socket(int port) {
  int socket_fd;
  struct sockaddr_in server_address;
  prepare_socket_vals(port, &socket_fd, &server_address);
	if (socket_fd < 0) return -1;

  bind(socket_fd, (struct sockaddr *) &server_address, sizeof(server_address));
  listen(socket_fd, 5);

  return socket_fd;
}

void poll_client(struct pollfd src, int destfd){
  if (src.revents & POLLIN) {
    char buffer[BUFFER_SIZE];
    int len = read(src.fd, &buffer, sizeof(buffer));
    for (int i = 0; i < len; i++) {
      switch (buffer[i]) {
        case '\003':
          raise(SIGINT);
          break;
        default: {
          write(destfd, buffer + i, 1);
          //write(src.fd, buffer + i, 1);
        }
      }
    }
  }
}
void poll_shell(){

}
int write_to_shell(int fd, const char *buffer, size_t n_chars, int shell_pid) {
  ssize_t n_written = 0;
  for (int i = 0; i < n_chars; i++) {
    switch (buffer[i]) {
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
        n_written = write(fd, buffer + i, 1);
        break;
    }

    if (n_written == -1) error_out("Could not write to display.", 1);
  }

  return 0;
}