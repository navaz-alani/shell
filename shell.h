#ifndef __SHELL_H__
#define __SHELL_H__

// struct _shell_ (or just `shell`) is a shell implementation.
typedef struct _shell_ {
  // the name of the shell (set at init)
  char *name;
  // current working directory of the shell (set at init)
  char *pwd;
  // whether the shell should exit its loop
  bool done;
} shell;

// `read_eval` starts the read-eval loop of the given shell.
int read_eval(shell *sh);

#endif
