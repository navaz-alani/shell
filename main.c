#include <unistd.h>
#include <stdbool.h>
#include <limits.h>

#include "shell.h"
#include "io_utils.h"

int main(int argc, char **argv) {
  shell sh;
  sh.name = argv[0];
  sh.done = false;
  // initialize pwd
  char pwd[PATH_MAX];
  if (getcwd(pwd, sizeof(pwd)) != NULL) sh.pwd = pwd;
  else { perror("init: getcwd() error"); return 1; }
  // start shell
  return read_eval(&sh);
}
