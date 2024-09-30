#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8000

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serveraddr = { .sin_family = AF_INET, .sin_port = htons(PORT), .sin_addr.s_addr = INADDR_ANY };
    struct sockaddr_in clientaddr;
    char buffer[1024], *response = "HELLO Client";
    socklen_t client_len = sizeof(clientaddr);

    bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(sockfd, 5);

    int newsockfd = accept(sockfd, (struct sockaddr *)&clientaddr, &client_len);
    int bytes_received = recv(newsockfd, buffer, sizeof(buffer), 0);
    buffer[bytes_received] = '\0';

    send(newsockfd, response, strlen(response), 0);
    printf("Hello message sent to client\n");

    close(newsockfd);
    close(sockfd);
    return 0;
}