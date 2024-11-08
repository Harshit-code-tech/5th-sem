#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define FILE_NAME "received_file.txt"

void handle_client(int client_fd) {
    FILE *file;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;

    // Open file for writing
    if ((file = fopen(FILE_NAME, "wb")) == NULL) {
        perror("File open failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    // Receive file contents
    while ((bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, 1, bytes_received, file);
        printf("Received %ld bytes\n", bytes_received); // Debugging statement
    }

    // Ensure all data is written to the file
    fflush(file);
    fclose(file);

    // Send acknowledgment
    char *ack_message = "File received successfully";
    send(client_fd, ack_message, strlen(ack_message), 0);

    close(client_fd);
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <Port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", port);

    while (1) {
        // Accept client connection
        if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len)) < 0) {
            perror("Accept failed");
            continue;
        }

        // Fork a new process to handle the client
        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            close(client_fd);
        } else if (pid == 0) {
            // Child process
            close(server_fd);
            handle_client(client_fd);
        } else {
            // Parent process
            close(client_fd);
            // Optionally, wait for child processes to prevent zombie processes
            while (waitpid(-1, NULL, WNOHANG) > 0);
        }
    }

    close(server_fd);
    return 0;
}