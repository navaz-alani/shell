#ifndef __GLOB_H__
#define __GLOB_H__

// glob_tokens performs glob expansion on the given token. It returns a
// (dynamically allocated) c-string containing the expanded form of `tok`. The
// caller is responsible for freeing the returned c-string.
char *glob_token(char *tok);

#endif
