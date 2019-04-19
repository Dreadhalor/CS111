#include <termios.h>
#include <stdlib.h>
#include <sys/types.h>

#ifndef READ_END
#define READ_END 0
#endif

#ifndef WRITE_END
#define WRITE_END 1
#endif

struct termios termios_init;
char *shell_program = NULL;

void error_out(char *error_msg, int print_errno) {
  if (shell_program) free(shell_program);

  tcsetattr(STDIN_FILENO, TCSANOW, &termios_init);

  if (print_errno) fprintf(stderr, "%s - %s", error_msg, strerror(errno));
  else fprintf(stderr, "Error - %s", error_msg);

  exit(1);
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

void redirect_stdio(int pipes[2]){
  dup2(pipes[WRITE_END], STDOUT_FILENO);
  dup2(pipes[WRITE_END], STDERR_FILENO);
  dup2(pipes[READ_END], STDIN_FILENO);
  close(pipes[READ_END]);
  close(pipes[WRITE_END]);
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

void store_termios_settings(struct termios *init){
  if (tcgetattr(STDIN_FILENO, init) == -1) {
    fprintf(stderr, "Could not get init terminal settings with tcgetattr. Error: %s\n", strerror(errno));
    exit(1);
  }
}

int set_termios(struct termios settings){
  tcsetattr(STDIN_FILENO, TCSANOW, &settings);

  struct termios success_check;
  if (tcgetattr(STDIN_FILENO, &success_check) == -1) return 0;

  int equals = (success_check.c_iflag == settings.c_iflag) && 
    (success_check.c_oflag == settings.c_oflag) &&
    (success_check.c_lflag == settings.c_lflag);
  if (!equals) return 0;

  return 1;
}

void set_non_canonical_no_echo_mode(struct termios init){
  struct termios termios_new = init;
  termios_new.c_iflag = ISTRIP;
  termios_new.c_oflag = 0;
  termios_new.c_lflag = 0;

  int success = set_termios(termios_new);
  if (!success)
    error_out("Failed to set termios to non-canonical no-echo mode.", 1);
}

void parse_input(int buffer_size) {
  size_t n_read;
  char input_buffer[buffer_size];

  int escape = 0;
  while (!escape) {
    n_read = read(STDIN_FILENO, (void*)input_buffer, buffer_size);
    escape = xwrite_noncanonical(STDOUT_FILENO, input_buffer, n_read);
  }
}