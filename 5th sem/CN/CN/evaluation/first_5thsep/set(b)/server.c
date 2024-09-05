#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080
#define BUFFER_SIZE 1024

// Compare function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    struct sockaddr_in serverAddr, clientAddr;
    int serverSocket, len, recvLen;
    char buffer[BUFFER_SIZE];
    int numbers[5];
    
    // Create UDP socket
    if ((serverSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Server address configuration
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(serverSocket, (const struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    len = sizeof(clientAddr);

    // Receive 5 numbers from the client
    recvLen = recvfrom(serverSocket, numbers, sizeof(numbers), 0, (struct sockaddr *)&clientAddr, &len);
    if (recvLen < 0) {
        perror("Receive failed");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    // Calculate sum, average, and median
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += numbers[i];
    }
    double average = sum / 5.0;

    // Sort for median calculation
    qsort(numbers, 5, sizeof(int), compare);
    double median = numbers[2];

    // Prepare and send result
    sprintf(buffer, "Sum: %d, Average: %.2f, Median: %.2f", sum, average, median);
    sendto(serverSocket, buffer, strlen(buffer), 0, (struct sockaddr *)&clientAddr, len);

    close(serverSocket);
    return 0;
}
