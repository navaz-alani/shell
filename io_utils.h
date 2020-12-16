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

// `__is_in_str__` returns whether the character `c` is in the c-string `str`.
bool __is_in_str__(const char *str, char c);

// `__concat_str__` concatenates the individual c-string parts into one
// c-string, with the `sep` c-string separating any two parts. The returned
// c-string is dynamically allocated and the caller is responsible for freeing
// the memory.
//
// Requires that `num_parts` >= 1.
char *__concat_str__(char **parts, int num_parts, char *sep);

// `__l_strip_str__` returns the index of the first character in `str` which
// does not appear in `strip`.
int __l_strip_str__(const char *str, const char *strip);

// `__r_strip_str__` returns the index of the last character in `str` which
// does not appear in `strip`.
int __r_strip_str__(const char *str, const char *strip);

// `__strip_str__` strips off all of the initial and final consecutive
// characters in `str` which appear in `strip`. Internally, it modifies `str` so
// that the right-stripped characters are '\0'. The returned value is a pointer
// to the first character in `str` after the left-stripped characters.
// Therefore, no allocations are performed. If `str` is allocated on the heap,
// the caller must retain `str` in order to free it.
char *__strip_str__(char *str, const char *strip);

#endif
