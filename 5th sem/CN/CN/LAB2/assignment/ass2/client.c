#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <client_ip> <client_port> <server_ip> <server_port>\n", argv[0]);
        exit(1);
    }

    int client_socket;
    struct sockaddr_in client_addr, server_addr;
    char buffer[BUFFER_SIZE];
    int client_port = atoi(argv[2]);
    int server_port = atoi(argv[4]);

    // Creating socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Configure client address
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(client_port);
    client_addr.sin_addr.s_addr = inet_addr(argv[1]);

    // Bind the client socket to the specified IP and port
    if (bind(client_socket, (struct sockaddr*)&client_addr, sizeof(client_addr)) < 0) {
        perror("Bind failed");
        close(client_socket);
        exit(1);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(argv[3]);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection to server failed");
        close(client_socket);
        exit(1);
    }

    // Get message from user
    printf("Enter message: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Remove newline character

    // Send message to server
    send(client_socket, buffer, strlen(buffer), 0);
    printf("Client IP: %s, Sent: \"%s\"\n", argv[1], buffer);

    // Receive reversed message from server
    recv(client_socket, buffer, BUFFER_SIZE, 0);
    printf("Received from Server IP: %s, Port: %d, Message: \"%s\"\n",
           argv[3], server_port, buffer);

    // Close socket
    close(client_socket);

    return 0;
}
