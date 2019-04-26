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

void poll_stdin(struct pollfd src, int socket_fd, FILE *logfile, int compression_flag){
  if (src.revents & POLLIN) {
    unsigned char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    unsigned char compressed[BUFFER_SIZE];
    memset(compressed, 0, BUFFER_SIZE);

    unsigned char final[BUFFER_SIZE];
    memset(final, 0, BUFFER_SIZE);
    int final_len;
    
    int len = read(STDIN_FILENO, &buffer, BUFFER_SIZE);
    final_len = len;
    memcpy(final, buffer, len);
    if (compression_flag){
      compress_buffer(compressed, BUFFER_SIZE, buffer, BUFFER_SIZE);
      final_len = (int)strlen((char *)compressed);
      memcpy(final, compressed, final_len);
    }
    if (logfile){
      fprintf(logfile,"SENT %i bytes: %s\n", final_len, final);
    }
    write(STDOUT_FILENO, buffer, len);
    write(socket_fd, final, final_len);
  }
}

void poll_server(struct pollfd src, int *close_flag, FILE *logfile, int compression_flag){
  if (src.revents & POLLIN) {
    unsigned char server_response[BUFFER_SIZE];
    memset(server_response, 0, BUFFER_SIZE);
    int len = read(src.fd, &server_response, sizeof(server_response));
    int final_len = len;
    if (compression_flag){
      unsigned char final_buffer[BUFFER_SIZE];
      memset(final_buffer, 0, BUFFER_SIZE);
      compress_buffer(final_buffer, BUFFER_SIZE, server_response, BUFFER_SIZE);
      final_len = (int)strlen((char *)compress_buffer);
      if (logfile && len > 0)
        fprintf(logfile, "RECEIVED %i bytes: %s\n", final_len, final_buffer);
    }
    if (logfile && len > 0 && !compression_flag){
      fprintf(logfile, "RECEIVED %i bytes: %s\n", len, server_response);
    }
    if (len == 0) *close_flag = 1;
    write(STDOUT_FILENO, server_response, len);
  } else if (src.revents & (POLLERR | POLLHUP)){
    *close_flag = 1;
  }
}