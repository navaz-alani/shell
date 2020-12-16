#ifndef __DIRS_H__
#define __DIRS_H__

// `struct _dirs_node_` is a node in the directory stack.
struct _dirs_node_ {
  const char *dir;
  struct _dirs_node_ *next;
};

// `dirs` is a linked-list implementation of a directory stack. It behaves like
// the `dirs` command in *nix systems. This means that it is negatively zero
// indexed i.e. the indices go 0, -1, -2, ...
typedef struct _dirs_ {
  // `count` is number of directory entries on the directory stack, times -1.
  int count;
  // `c_len` is the cummulative length of all of the directory entries on the
  // directory stack.
  int c_len;
  // `head` points to the head of the linked-list containing the directory stack
  // entries.
  struct _dirs_node_ *head;
} dirs;

// `pwd` returns the directory entry at the top of the directory stack `d`.
const char *pwd(dirs *d);

// `pushd` pushes the diven directory name to the directory stack. `dirs`
// assumes that the given `char *dir` is dynamically allocated and takes
// ownership of it. It will be freed when `cleard` is called on the directory
// stack `d`.
int pushd(dirs *d, const char *dir);

// `popd` pops a directory off the directory stack and returns it. If the
// directory stack is empty, `NULL` is returned.
const char *popd(dirs *d);

// `popn` removes the `n`th entry in the directory stack and returns its value.
// If no such entry exists, then the return value is `NULL`.
// Note that the directory stack is negatively zero-indexed i.e. 0, -1, -2, ...
const char *popn(dirs *d, int n);

// `_repr_` returns a readable dynamically allocated c-string representing the
// current contents of the directory stack `d`.
const char *_repr_(dirs *d);

// `cleard` frees memory allocated by the directory stack `d` and returns `d` to a
// fresh state.
int cleard(dirs *d);

#endif
