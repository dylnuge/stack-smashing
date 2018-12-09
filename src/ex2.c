#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "./socks.c"

char * SOCKET_PATH = "socket";

// This is the function we actually want to call. Here's a fun fact: neither the
// compiler or the linker will remove this function (by default), even though
// none of our code uses it. "Debug functions" which aren't called but are still
// _compiled_ into real world code are actually a decently common source of
// exploits.
void root_mode() {
    printf("Exploit succeeded\n");
}

void login() {
    // Allocate a 12 character buffer for our username.
    char username[12];
    // Open a domain socket for writing to at `socket`
    // We need this so we can write non-ASCII characters to our buffer
    // String overflows are _more limiting_ than this one, but that doesn't mean
    // they can't still be used to do damage, especially to availability.
    unsafe_bind_and_read_domain_socket(username, SOCKET_PATH);
    printf("User %s connected\n", username);
}

int main(int argc, char **args) {
    if (argc != 1) {
        return 1;
    }
    login();
    printf("Execution completed\n");
}
