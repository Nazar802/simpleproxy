#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
    // create socket info structs
    struct sockaddr_in server_info = {0};
    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(8080);

    socklen_t server_info_len = sizeof(server_info);

    struct sockaddr client_info = {0};
    socklen_t client_info_len = sizeof(client_info);

    // create socket
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (0 > sfd) {
        perror("socket");
        return -1;
    }

    // bind
    if (0 > bind(sfd, (struct sockaddr*)&server_info, server_info_len)) {
        perror("bind");
        return -1;
    }

    // listen
    if (0 > listen(sfd, 0)) {
        perror("listen");
        return -1;
    }

    // accept
    int cfd = accept(sfd, &client_info, &client_info_len);
    if (0 > cfd) {
        perror("accept");
        return -1;
    }

    // handle client
    char* hello = "Hello World!\n";
    ssize_t resp = send(cfd, hello, strlen(hello), 0);

    // clean up and close
    close(cfd);
    return 0;
}