#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
// gcc server.c -o server
#define PORT 8080
#define BUFFER_SIZE 1024
#define END_OF_FILE "END_OF_FILE"

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    FILE *fp;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Fill server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    len = sizeof(cliaddr); // Length of client's address

    // Receive file name from client
    int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&cliaddr, &len);
    buffer[n] = '\0'; // Null-terminate the file name
    printf("Client requested file: %s\n", buffer);

    // Open the requested file
    fp = fopen(buffer, "rb");
    if (fp == NULL) {
        perror("File not found");
        sendto(sockfd, "File not found", strlen("File not found"), 0, (struct sockaddr *)&cliaddr, len);
    } else {
        // Read file contents and send them to the client in chunks
        while ((n = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) {
            sendto(sockfd, buffer, n, 0, (struct sockaddr *)&cliaddr, len);
        }
        fclose(fp);

        // Send the end-of-file signal to the client
        sendto(sockfd, END_OF_FILE, strlen(END_OF_FILE), 0, (struct sockaddr *)&cliaddr, len);
        printf("File sent successfully\n");
    }

    close(sockfd);
    return 0;
}

