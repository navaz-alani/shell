#include <string.h>
#include <stdbool.h>

#include "shell.h"

int handle_builtin(shell *sh, char **tokens, int num_tokens) {
  if (!num_tokens) return 0;
  if (!strcmp(tokens[0], "quit")) {
    sh->done = true;
    return 0;
  } else if (!strcmp(tokens[0], "cd")) {
    // change working directory of shell
    sh->pwd = tokens[1];
    return 0;
  }
  return 1;
}
