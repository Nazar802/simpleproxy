#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define MAX_LISTEN_BACKLOG 1024
#define BUFFER_SIZE 4096

/*
Writing some wrappers
for syscalls to
make my life easier
*/

// Socket wrappers
int w_socket(int domain, int type, int protocol) {
    int rc = socket(AF_INET, SOCK_STREAM, 0);
    if (0 > rc) {
        perror("socket");
        return -1;
    }
    return rc;
}

int w_setsockopt(int socket_fd, int level, 
                 int optname, const void *optval, 
                 socklen_t optlen) {
    int rc = setsockopt(socket_fd, level, optname, optval, optlen);
    if (0 > rc) {
        perror("setsockopt");
    }
    return rc;
}

int w_bind(int socket_fd, const struct sockaddr *addr, socklen_t addrlen) {
    int rc = bind(socket_fd, addr, addrlen);
    if (0 > rc) {
        perror("bind");
    }
    return rc;
}

int w_listen(int socket_fd, int backlog) {
    int rc = listen(socket_fd, backlog);
    if (0 > rc) {
        perror("listen");
    }
    return rc;
}

int w_accept(int socket_fd, struct sockaddr *restrict addr,
             socklen_t *restrict addrlen) {
    int rc = accept(socket_fd, addr, addrlen);
    if (0 > rc) {
        perror("accept");
    }
    return rc;
}

int w_connect(int socket_fd, const struct sockaddr *addr, socklen_t addrlen) {
    int rc = connect(socket_fd, addr, addrlen);
    if (0 > rc) {
        perror("connect");
    }
    return rc;
}

// I/O wrappers

ssize_t w_read(int fd, void *buf, size_t count) {
    ssize_t rc = read(fd, buf, count);
    if (0 > rc) {
        perror("read");
    }
    return rc;
}

ssize_t w_write(int fd, const void *buf, size_t count) {
    ssize_t rc = write(fd, buf, count);
    if (0 > rc) {
        perror("write");
    }
    return rc;
}

int w_open(const char *pathname, int flags, mode_t mode) {
    int rc = open(pathname, flags, mode);
    if (0 > rc) {
        perror("open");
    }
    return rc;
}

int w_close(int fd) {
    int rc = close(fd);
    if (0 > rc) {
        perror("close");
    }
    return rc;
}


/*
Sockets
*/

int open_socket(int port) {
    /*
    Create a socket and accept requests
    */

    // server info
    struct sockaddr_in server_info = {0};
    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(port);
    socklen_t server_info_len = sizeof(server_info);
    
    // client info
    struct sockaddr client_info = {0};
    socklen_t client_info_len = sizeof(client_info);

    // create server socket
    int server_fd = w_socket(AF_INET, SOCK_STREAM, 0);

    // bind
    w_bind(server_fd, (struct sockaddr*)&server_info, server_info_len);

    // listen
    w_listen(server_fd, 0);

    // accept
    w_accept(server_fd, &client_info, &client_info_len);
    return server_fd;
}

int read_response() {
    return 0;
}

int write_response() {
    return 0;
}


int main(int argc, char *argv) {
    // accept client requests

    // proxy client requests to the destination host

    // read the response

    // send it back to the client
    return 0;
}