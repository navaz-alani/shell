# `shell`

This is a simple POSIX shell application written in pure C. It is an attempt to
understand the \*nix Programming Interface. Currently, the shell can perform
basic execution of commands with arguments (such as `ls`, `cat <path_to_file>`).
Globbing has been implemented using `glob.h`, so commands such as `ls *.c` work
as expected.

To build the shell, run `make` and a binary called `shell` will be produced if
no errors occur.
