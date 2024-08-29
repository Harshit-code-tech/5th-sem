#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

// Function to reverse a string
void reverse_string(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server_ip> <server_port>\n", argv[0]);
        exit(1);
    }

    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_size;
    int port = atoi(argv[2]);

    // Creating socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    // Bind the socket to the specified IP and port
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(1);
    }

    printf("Server is listening on %s:%d\n", argv[1], port);

    // Accept incoming connection
    addr_size = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);
    if (client_socket < 0) {
        perror("Client connection failed");
        close(server_socket);
        exit(1);
    }

    // Receive message from client
    recv(client_socket, buffer, BUFFER_SIZE, 0);
    printf("Received from Client IP: %s, Port: %d, Message: \"%s\"\n",
           inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);

    // Reverse the message
    reverse_string(buffer);

    // Send the reversed message back to the client
    send(client_socket, buffer, strlen(buffer), 0);
    printf("Server IP: %s, Sent: \"%s\"\n", argv[1], buffer);

    // Close sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
