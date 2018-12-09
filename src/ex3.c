#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "./socks.c"

char * SOCKET_PATH = "socket";

// This challenge is a _substantial_ leap from the previous two. In it, we're
// going to write and execute our own assembly code. It's totally reasonable to
// get frustrated working on this challenge, and it may take several hours
// to fully figure out. Don't give up! This is _entirely_ doable with the
// knowledge you already have plus a little bit of assembly, and accomplishing
// it will feel extraordinary.
//
// If you need some hints, check the `hints` directory. Note that the file
// called `solution.md` in there contains the whole answer and won't give you
// any satisfaction...avoid reading it until you're done ;)

// This is the function we want to call
void root_mode(int key) {
    // Under the hood, the argument key is read from from the %edi register
    // here. If we were to wind up here somehow without doing a "normal" call,
    // whatever was already in the %edi register would be read.
    if (key == 0x41424344) {
        printf("Exploit succeeded\n");
    } else {
        printf("User unauthorized, key is 0x%08x\n", key);
    }
}

void login() {
    // Allocate a 12 character buffer for our username.
    char username[12];

    // "Leak" the stack address intentionally. This might seem like another
    // cheat, but it's not uncommon for stack address to be leaked in error
    // messages and other logging details. What's useful for devs is also useful
    // for us. This should stay nice and consistent across runs.
    printf("%p\n", &username);

    // Open a domain socket for writing to at `socket` This time, you need to
    // call root_mode with an argument. x64 calling conventions (at least in
    // clang and gcc) will put our first argument into the %edi register.
    // We'll need some way of setting that before jumping to root mode.
    unsafe_bind_and_read_domain_socket(username, SOCKET_PATH);
}

int main(int argc, char **args) {
    login();
    return 0;
}
