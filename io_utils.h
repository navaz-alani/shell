#ifndef _IO_UTILS_H_
#define _IO_UTILS_H_

#include <stdio.h>

// realine reads from the given input stream, until EOF or the `delim` character
// is encountered (whichever happens first). The caller is responsible for
// freeing the returned character array (c-string). If the returned pointer is
// NULL, a failure in memory allocation has occurred.
char *readline(FILE *istream, char delim);

// `esc_tokenize` tokenizes the given string `s`, according to the given
// delimiters `delim`. It escapes occurrences of the `delim` if preceeded by the
// escape character `esc`. The returned array of c-strings is dynamically
// allocated and the caller is responsible for freeing the memory.
char **esc_tokenize(char *s, char* delims, char esc, int *num_tokens);

// `__grow_str_buff__` grows the given c-string array to have `new_cap`
// capacity. A non-zero return value indicates that there was an error while
// reallocating the c-string array.
int __grow_str_buff__(char ***buff, int new_cap);

// `__concat_str__` concatenates the individual c-string parts into one
// c-string, with the `sep` c-string separating any two parts. The returned
// c-string is dynamically allocated and the caller is responsible for freeing
// the memory.
//
// Requires that `num_parts` >= 1.
char *__concat_str__(char **parts, int num_parts, char *sep);

#endif
