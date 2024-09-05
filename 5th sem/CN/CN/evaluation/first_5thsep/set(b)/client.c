#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    struct sockaddr_in serverAddr;
    int clientSocket, len;
    char buffer[BUFFER_SIZE];
    int numbers[5];

    // Create UDP socket
    if ((clientSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Server address configuration
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Input 5 numbers from the user
    printf("Enter 5 numbers:\n");
    for (int i = 0; i < 5; i++) {
        scanf("%d", &numbers[i]);
    }

    len = sizeof(serverAddr);

    // Send the numbers to the server
    sendto(clientSocket, numbers, sizeof(numbers), 0, (struct sockaddr *)&serverAddr, len);

    // Receive the result from the server
    int recvLen = recvfrom(clientSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&serverAddr, &len);
    if (recvLen < 0) {
        perror("Receive failed");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }

    buffer[recvLen] = '\0';  // Null-terminate the received string
    printf("Received from server: %s\n", buffer);

    close(clientSocket);
    return 0;
}
