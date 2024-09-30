#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <Server IP> <Port> <File Name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *server_ip = argv[1];
    int port = atoi(argv[2]);
    char *file_name = argv[3];

    int sockfd;
    struct sockaddr_in server_addr;
    FILE *file;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_sent;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Open file
    if ((file = fopen(file_name, "rb")) == NULL) {
        perror("File open failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Send file contents
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        if ((bytes_sent = send(sockfd, buffer, bytes_read, 0)) < 0) {
            perror("Send failed");
            fclose(file);
            close(sockfd);
            exit(EXIT_FAILURE);
        }
        printf("Sent %ld bytes\n", bytes_sent); // Debugging statement
    }

    fclose(file);

    // Receive acknowledgment
    if ((bytes_read = recv(sockfd, buffer, BUFFER_SIZE, 0)) < 0) {
        perror("Receive failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    buffer[bytes_read] = '\0';
    printf("Server: %s\n", buffer);

    close(sockfd);
    return 0;
}