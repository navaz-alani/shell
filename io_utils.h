#ifndef _IO_UTILS_H_
#define _IO_UTILS_H_

#include <stdio.h>

// realine reads from the given input stream, until EOF or the `delim` character
// is encountered (whichever happens first). The caller is responsible for
// freeing the returned character array. If the returned pointer is NULL, a
// failure in memory allocation has occurred.
char *readline(FILE *istream, char delim);

char **tokenize(char *s, char *delims, int *num_tokens);

#endif
