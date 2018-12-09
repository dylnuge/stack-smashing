#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "./socks.c"

char * SOCKET_PATH = "socket";

void root_mode() {
    printf("Exploit succeeded\n");
}

void login() {
    char username[4];
    //bind_and_read_domain_socket(username, SOCKET_PATH);
    // Open a socket for writing to at "socket"
    // We need this so we can write non-ASCII characters to our buffer
    // String overflows are _more limiting_ than this one, but that doesn't mean
    // they can't still be used to do damage, especially to availability.
    int fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    struct sockaddr_un addr;
    addr.sun_family = PF_LOCAL;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path));
    bind(fd, (struct sockaddr*)&addr, sizeof(addr));

    // Read from the socket
    listen(fd, 1);
    int cd = accept(fd, NULL, NULL);
    read(cd, username, 30);
    // Clean up
    close(fd);
    unlink(SOCKET_PATH);
    printf("User %s connected\n", username);
}

int main(int argc, char **args) {
    if (argc != 1) {
        return 1;
    }
    login();
    printf("Execution completed\n");
}
