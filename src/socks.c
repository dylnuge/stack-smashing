#include <arpa/inet.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

// Check if a socket exists at `path` and clear it if it does.
// Such an ugly way of handling this case, but it works.
// TODO(dylan): Better ways of handling this:
// * Capture SIGINT (Ctrl+C) and clean up sockets on exit
// * Actual error handling in the bind_and_read function
void clear_domain_socket_if_exists(char *path) {
    if(access(path, F_OK) == 0) {
        unlink(path);
    }
}

// For the most part, this code isn't crucial to understand. It's basically the
// boilerplate minimum for working with sockets. It's not very good socket code.
// If you're thinking of learning how sockets work, seriously, this is bad code
void unsafe_bind_and_read_domain_socket(char *buf, char *path) {
    // Ugly hack: Clear the domain socket if there's already something at path.
    // This happens because this function never cleaned up, usually caused by
    // exiting the program with SIGINT (CTRL-C). We should just handle SIGINT
    // cleanup but this works for now.
    clear_domain_socket_if_exists(path);
    // Open a unix (PF_LOCAL) socket and capture the file descriptor
    int fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    // Bind that socket to a file at `path`
    struct sockaddr_un addr;
    addr.sun_family = PF_LOCAL;
    strncpy(addr.sun_path, path, sizeof(addr.sun_path));
    bind(fd, (struct sockaddr*)&addr, sizeof(addr));

    // Listen to incoming connection from the socket
    listen(fd, 1);
    // Wait for an incoming connection, then accept it and capture the
    // connection's file descriptor
    int cd = accept(fd, NULL, NULL);

    // XXX THIS IS A BUFFER OVERFLOW VULNERABILITY XXX
    // Read 8 bytes at a time
    // Here's where the unsafe code comes into play. We don't check the size of
    // the buffer we're passed, so we'll keep reading until the connection
    // closes (8 bytes at a time), even if the buffer has run out of space for
    // us.
    // XXX THIS IS A BUFFER OVERFLOW VULNERABILITY XXX
    while(read(cd, buf, 8) != 0) {
        buf += 8;
    }

    // Clean up by closing our files and unlinking the socket path
    close(fd);
    close(cd);
    unlink(path);
}

/*
 * Didn't wind up using this, but it's code to do sockets via standard network
 * ports instead of using a UNIX domain socket. It has similar properties to the
 * function above. I haven't tested it.
 */
void unsafe_bind_and_read_socket(char *buf, unsigned short port) {
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
    // XXX THIS IS A BUFFER OVERFLOW VULNERABILITY XXX
    while(read(cd, buf, 8) != 0) {
        buf += 8;
    }

    // Clean up
    close(fd);
    close(cd);
}
