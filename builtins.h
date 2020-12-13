#ifndef __BUILTINS_H__
#define __BUILTINS_H__

// `handle_builtin` checks if the given command is a builtin shell command and
// executes the command. A return value of 0 indicates that the command was
// builtin and has been handled. A non-zero return value indicates that the
// command is _not_ builtin and further processing is needed.
int handle_builtin(shell *sh, char **tokens, int num_tokens);

#endif
