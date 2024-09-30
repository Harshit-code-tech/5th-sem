#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
// gcc client.c -o client
#define PORT 8080
#define BUFFER_SIZE 1024
#define END_OF_FILE "END_OF_FILE"

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in servaddr;
    socklen_t len;
    FILE *fp;
    char *filename = "received_file";

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Fill server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    // Send file name to server
    printf("Enter file name to request: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
    sendto(sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("File name sent: %s\n", buffer);

    // Open file to write received contents
    fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("File could not be opened");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    len = sizeof(servaddr);

    // Receive file contents from the server
    int n;
    while (1) {
        n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&servaddr, &len);
        if (n <= 0) {
            break;
        }
        buffer[n] = '\0'; // Null-terminate the buffer

        // Check if we received the end-of-file signal
        if (strcmp(buffer, END_OF_FILE) == 0) {
            break;
        }

        // Write the received chunk to the file
        fwrite(buffer, 1, n, fp);
    }

    printf("File received and saved as %s\n", filename);

    fclose(fp);
    close(sockfd);
    return 0;
}

