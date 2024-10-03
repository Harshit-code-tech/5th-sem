#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int server_socket;  // Global server socket to close on exit

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;

    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        buffer[bytes_received] = '\0'; // Null-terminate the received data
        if (strcmp(buffer, "logout\n") == 0) {
            printf("Client requested logout. Shutting down server.\n");
            kill(getppid(), SIGINT);  // Send SIGINT to the parent (server)
            break;
        }
        send(client_socket, buffer, bytes_received, 0);
    }

    close(client_socket);
    exit(0);
}

void sigint_handler(int sig) {
    printf("Server is shutting down...\n");
    close(server_socket);
    exit(0);
}

int main() {
    int client_socket;
    struct sockaddr_in server_addr;

    // Handle SIGINT to gracefully shut down the server
    signal(SIGINT, sigint_handler);

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the address and port
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Ignore SIGCHLD to prevent zombie processes
    signal(SIGCHLD, SIG_IGN);

    printf("Server listening on port %d\n", PORT);

    // Main loop to accept and handle clients
    while (1) {
        client_socket = accept(server_socket, NULL, NULL);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        // Fork a new process for each client
        if (fork() == 0) {  // Child process
            close(server_socket);  // Child does not need the server socket
            handle_client(client_socket);
        } else {  // Parent process
            close(client_socket);  // Parent does not need the client socket
        }
    }

    // Close the server socket (not really needed since SIGINT handler does this)
    close(server_socket);
    return 0;
}
