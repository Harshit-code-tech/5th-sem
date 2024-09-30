#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8000

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serveraddr = { .sin_family = AF_INET, .sin_port = htons(PORT), .sin_addr.s_addr = inet_addr("127.0.0.1") };
    char buffer[1024], *msg = "hi server";

    connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    send(sockfd, msg, strlen(msg), 0);
    int byte_received = recv(sockfd, buffer, sizeof(buffer), 0);
    buffer[byte_received] = '\0';

    printf("Server: %s\n", buffer);
    close(sockfd);
    return 0;
}