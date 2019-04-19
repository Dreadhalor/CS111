#include <errno.h>
#include <termios.h>
#include <unistd.h>

int store_stdin_settings(struct termios *init){
  return tcgetattr(STDIN_FILENO, init);
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