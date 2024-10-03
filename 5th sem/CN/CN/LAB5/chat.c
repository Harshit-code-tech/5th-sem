#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void chat(int sockfd) {
    char buffer[BUFFER_SIZE];
    int n;

    while (1) {
        bzero(buffer, BUFFER_SIZE);
        printf("You: ");
        n = 0;

        // Get user input
        while ((buffer[n++] = getchar()) != '\n');

        // Send the message to the server
        send(sockfd, buffer, strlen(buffer), 0);

        // Check if the user wants to exit
        if (strncmp(buffer, "logout", 6) == 0) {
            printf("Logging out...\n");
            break;
        }

        // Receive the server's response
        bzero(buffer, BUFFER_SIZE);
        recv(sockfd, buffer, BUFFER_SIZE, 0);
        printf("Server: %s", buffer);
    }
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection to the server failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Start the chat
    chat(sockfd);

    // Close the socket
    close(sockfd);
    return 0;
}
