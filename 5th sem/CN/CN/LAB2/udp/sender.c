#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8000

int main() {
    int sockfd;
    int b1;
    struct sockaddr_in serveraddr, clientaddr;
    char buffer[1024];
    char *response = "HELLO Client";
    int bytes_received;
    int byte_send;
    int length = sizeof(clientaddr);

    // Zero out the structures
    memset(&serveraddr, 0, sizeof(serveraddr));
    memset(&clientaddr, 0, sizeof(clientaddr));

    // Set up the server address structure
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket
    b1 = bind(sockfd, (const struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (b1 < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Receive data
    bytes_received = recvfrom(sockfd, (char *)buffer, sizeof(buffer), MSG_WAITALL,
                             (struct sockaddr *)&clientaddr, &length);
    if (bytes_received < 0) {
        perror("Receive failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Send response
    byte_send = sendto(sockfd, (const char *)response, strlen(response), MSG_CONFIRM,
                       (const struct sockaddr *)&clientaddr, length);
    if (byte_send < 0) {
        perror("Send failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Hello message sent to client\n");

    // Close socket
    close(sockfd);
    return 0;
}
