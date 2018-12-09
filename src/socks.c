#include <arpa/inet.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

/*
 * Didn't wind up using this, but it's code to do sockets via standard network
 * ports instead of using a UNIX domain socket
 */
void bind_and_read_socket(char *buf, unsigned short port) {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    int fd = socket(PF_INET, SOCK_RAW, IPPROTO_RAW);

    if (fd == -1) {
        printf("Could not bind to socket on port %d\n", port);
        exit(1);
    }

    // Listen for IPv4 connections
    addr.sin_family = PF_INET;
    // On `port` (htons puts us in network big-endian byte order)
    addr.sin_port = htons(port);
    // To connections coming from localhost
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(fd, (struct sockaddr*) &addr, sizeof(addr));
    listen(fd, 1);
    int cd = accept(fd, NULL, NULL);
    while(read(cd, buf, 10) != 0) {
        printf("read %s\n", buf);
        buf += 10;
    }

    // Clean up
    close(fd);
}

void bind_and_read_domain_socket(char *buf, char *path) {
    // Open a socket for writing to at "socket"
    // We need this so we can write non-ASCII characters to our buffer
    // String overflows are _more limiting_ than this one, but that doesn't mean
    // they can't still be used to do damage, especially to availability.
    int fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    struct sockaddr_un addr;
    addr.sun_family = PF_LOCAL;
    strncpy(addr.sun_path, path, sizeof(addr.sun_path));
    bind(fd, (struct sockaddr*)&addr, sizeof(addr));

    // Read from the socket
    listen(fd, 1);
    int cd = accept(fd, NULL, NULL);
    while(read(cd, buf, 30) != 0) {
        printf("read %s\n", buf);
    }

    // Clean up
    close(fd);
    unlink(path);
}
