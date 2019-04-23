/*#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <poll.h>*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>

#include "cslib.c"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

#ifndef READ_END
#define READ_END 0
#endif

#ifndef WRITE_END
#define WRITE_END 1
#endif

struct termios termios_init;

void error_out(char *error_msg, int print_errno) {
  tcsetattr(STDIN_FILENO, TCSANOW, &termios_init);

  if (print_errno) fprintf(stderr, "%s - %s", error_msg, strerror(errno));
  else fprintf(stderr, "Error - %s", error_msg);

  exit(1);
}

int set_non_canonical_no_echo_mode(){
  struct termios settings;
  store_stdin_settings(&settings);
  settings.c_iflag = ISTRIP;
  settings.c_oflag = 0;
  settings.c_lflag = 0;

  return set_termios(settings);
}

void redirect_stdio(int pipes[2]){
  dup2(pipes[WRITE_END], STDOUT_FILENO);
  dup2(pipes[WRITE_END], STDERR_FILENO);
  dup2(pipes[READ_END], STDIN_FILENO);
  close(pipes[READ_END]);
  close(pipes[WRITE_END]);
}

int fork_and_set_pipes(int pipes[2]){

  int to_shell[2], from_shell[2];

  if ((pipe(to_shell) == -1) || (pipe(from_shell) == -1)) return -1;

  int pid = fork();
  if (pid == 0) {
    //child process
    //close write end to shell + read end from shell
    close(to_shell[WRITE_END]);
    close(from_shell[READ_END]);
    //set child pipes
    pipes[READ_END] = to_shell[READ_END];
    pipes[WRITE_END] = from_shell[WRITE_END];

  } else if (pid > 0) {
    //parent process
    //close read end to shell + write end from shell
    close(to_shell[READ_END]);
    close(from_shell[WRITE_END]);
    //set parent pipes
    pipes[READ_END] = from_shell[READ_END];
    pipes[WRITE_END] = to_shell[WRITE_END];
  }
  return pid;
}

ssize_t xwrite_noncanonical(int fd, const char *buf, size_t n_chars) {
  unsigned int i = 0;
  ssize_t n_written = 0;

  for (; i < n_chars; i++) {
    switch (buf[i]) {
      case '\n':
      case '\r':
        n_written = write(fd, (void*)"\r\n", 2);
        break;
      case 0x004: return 1;
      default:
        n_written = write(fd, (void*)(buf + i), 1);
        break;
    }

    if (n_written == -1) error_out("Could not write to display in non canonical mode.", 1);
  }

  return 0;
}

ssize_t xread(int fd, void *buf, size_t nbyte) {
  ssize_t n_read = read(fd, buf, nbyte);

  if (n_read == -1)
    error_out("Failed to read from file.", 1);

  return n_read;
}

int xwrite_shell(int fd, const char *buf, size_t n_chars, int shell_pid) {
  ssize_t n_written = 0;
  for (int i = 0; i < n_chars; i++) {
    switch (buf[i]) {
      case 0x003:
        if (kill(shell_pid, SIGINT) == -1) error_out("Could not KILL shell.", 1);
        fprintf(stderr, "Signal successfully forwarded!\r\n");
        break;
      case 0x004: return 1;
      case '\r':
        n_written = write(fd, "\n", 1);
        break;
      default:
        n_written = write(fd, (void*)(buf + i), 1);
        break;
    }

    if (n_written == -1) error_out("Could not write to display.", 1);
  }

  return 0;
}

void prepare_socket_vals(int port, int *socket_fd, struct sockaddr_in *server_address){
  int domain = AF_INET; //(IPv4 protocol)
  int type = SOCK_STREAM; //(TCP)
  int protocol = 0;

  *socket_fd = socket(domain, type, protocol);

  server_address -> sin_family = domain;
  server_address -> sin_port = htons(port);
  server_address -> sin_addr.s_addr = INADDR_ANY;
}