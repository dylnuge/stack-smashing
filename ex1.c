#include <stdio.h>

// Standard C compilers look for a function called "main" and make it the entry
// point for execution when building an executable (as opposed to linking). Two
// variables are passed to this function: the number of arguments (an integer)
// and the arguments the function itself is called with (an array of strings,
// in C strings are themselves represented as an array of characters, and arrays
// are referenced using pointers).
int main(int argc, char **args) {
    // Standard shells (bash, zsh, ksh, etc) pass the name of the executable
    // itself as the first argument to the program. For this program, we don't
    // want to accept any arguments on run.
    if (argc != 1) {
        // In C, the main function is expected to return an integer, which tells
        // the calling system the outcome of the program. POSIX standard (which
        // practically all modern operating systems follow) is to return 0 on a
        // successful execution and any other positive number on a failure (a
        // nonzero exit code may contain information about the failure).
        return 1;
    }

    // The stack is built bottom-up from high memory addresses on most operating
    // systems. Assuming this program is built on a 32-bit system or in 32-bit
    // compatible mode, sizeof(int) should be 4 bytes (and 1 byte should be 8
    // bits). This means that after allocating space for these variables, our
    // memory space will look like this:
    // |------- 4 bytes -------|
    // | username (0x00000000) |   lower memory addresses
    // |-----------------------|            |
    // | username (0x00000000) |            |
    // |-----------------------|            |
    // | username (0x00000000) |            |
    // |-----------------------|            V
    // |   key (0xdeadbeef)    |  higher memory addresses
    // |-----------------------|
    int key = 0xdeadbeef;
    // TODO(dylan): Compiler optimization is messing with longer strings,
    // probably placing them onto the heap instead of the stack. Fix?
    char username[4];

    // Now we're going to read user input and copy it into the "uid" string we
    // just allocated. We only have space for 12 bytes, but by not explicitly
    // checking this, we introduce a buffer overflow exploit.
    gets(username);

    // We now check the value in "key" to see if it matches the magic value we
    // want it to. In ASCII, this value is equivalent to "AAAA" to make life
    // easy on us.
    if (key == 0x41414141) {
        printf("Exploit succeeded\n");
        return 0;
    } else {
        printf("User unauthorized, key is %x\n", key);
        return 1;
    }
}
