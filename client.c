#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
    // create server info
    struct sockaddr_in server_info = {0};
    server_info.sin_family = AF_INET;
    server_info.sin_addr.s_addr = htonl(0x7f000001);
    server_info.sin_port = htons(8080);

    socklen_t server_info_len = sizeof(server_info);

    // create socket
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (0 > sfd) {
        perror("socket");
        return -1;
    }

    // connect to server
    if (0 > connect(sfd, (struct sockaddr*)&server_info, server_info_len)) {
        perror("connect");
        return -1;
    }

    char buffer[1024];
    // client
    ssize_t recvd = recv(sfd, buffer, sizeof(buffer), 0);
    printf("%s\n", buffer);

    // clean up and close
    close(sfd);
    return 0;
}