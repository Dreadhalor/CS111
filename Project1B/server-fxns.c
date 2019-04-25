#include "compression.c"

int create_server_socket(int port) {
  int socket_fd;
  struct sockaddr_in server_address;
  prepare_socket_vals(port, &socket_fd, &server_address);
	if (socket_fd < 0) return -1;

  bind(socket_fd, (struct sockaddr *) &server_address, sizeof(server_address));
  listen(socket_fd, 5);

  return socket_fd;
}

int write_to_shell(int fd, const char *buffer, int n_chars, int shell_pid) {
  ssize_t n_written = 0;
  for (int i = 0; i < n_chars; i++) {
    switch (buffer[i]) {
      case 0x003:
        if (kill(shell_pid, SIGINT) == -1)
          error_out("Could not KILL shell.", 1);
        else fprintf(stderr, "Signal successfully forwarded!\r\n");
        break;
      case 0x004: return 1;
      case '\r':
        n_written = write(fd, "\n", 1);
        break;
      default:
        n_written = write(fd, buffer + i, 1);
        break;
    }
    if (n_written == -1) error_out("Could not write to display.", 1);
  }
  return 0;
}

int poll_client(struct pollfd src, int destfd, int pid, int shutdown){
  if (!shutdown && src.revents & POLLIN) {
    char buffer[BUFFER_SIZE];
    int len = read(src.fd, &buffer, sizeof(buffer));
    return write_to_shell(destfd, buffer, len, pid);
  }
  else return 0;
}
void poll_shell(struct pollfd src, int destfd, int shutdown){
  if (!shutdown && src.revents & POLLIN) {
    char buffer[BUFFER_SIZE];
    int len = read(src.fd, &buffer, sizeof(buffer));
    xwrite_noncanonical(destfd, buffer, len);
  }
}