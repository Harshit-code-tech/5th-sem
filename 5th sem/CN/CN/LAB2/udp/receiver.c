#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>  // Include this header for inet_addr
#include <unistd.h>

#define PORT 8000

int main() {
    int sockfd;
    int bytes_sent;
    char buffer[1024];
    int byte_received;
    char *msg = "hi server";
    struct sockaddr_in serveraddr;

    // Create a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up the server address structure
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Replace with actual server IP if needed

    // Send a message to the server
    bytes_sent = sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (bytes_sent < 0) {
        perror("Send failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Receive a response from the server
    byte_received = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
    if (byte_received < 0) {
        perror("Receive failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    buffer[byte_received] = '\0'; // Null-terminate the received data

    // Print the received message
    printf("Server: %s\n", buffer);

    // Close the socket
    close(sockfd);
    return 0;
}
