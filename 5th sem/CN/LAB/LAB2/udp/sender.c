#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8000

int main() {
    int sockfd, b1, bytes_received, byte_send;
    struct sockaddr_in serveraddr = {0}, clientaddr = {0};
    char buffer[1024];
    socklen_t length = sizeof(clientaddr);
    char *response = "HELLO Client";

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 || 
        (b1 = bind(sockfd, (const struct sockaddr *)&serveraddr, sizeof(serveraddr))) < 0 || 
        (bytes_received = recvfrom(sockfd, buffer, sizeof(buffer), 0, 
         (struct sockaddr *)&clientaddr, &length)) < 0 || 
        (byte_send = sendto(sockfd, response, strlen(response), 0, 
         (const struct sockaddr *)&clientaddr, length)) < 0) {
        perror("Error");
        close(sockfd);
        return EXIT_FAILURE;
    }

    printf("Hello message sent to client\n");
    close(sockfd);
    return 0;
}
