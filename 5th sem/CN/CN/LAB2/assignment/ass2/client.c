#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024  // Define buffer size for messages

int main(int argc, char *argv[]) {
    if (argc != 5) return 1;  // Ensure correct usage with command-line arguments

    char *client_ip = argv[1];  // Extract client IP from arguments
    int client_port = atoi(argv[2]);  // Extract client port from arguments
    char *server_ip = argv[3];  // Extract server IP from arguments
    int server_port = atoi(argv[4]);  // Extract server port from arguments

    int client_fd = socket(AF_INET, SOCK_STREAM, 0);  // Create a TCP socket

    struct sockaddr_in client_addr = {AF_INET, htons(client_port), inet_addr(client_ip)}, 
                       server_addr = {AF_INET, htons(server_port), inet_addr(server_ip)};
    
    bind(client_fd, (struct sockaddr*)&client_addr, sizeof(client_addr));  // Bind client to IP and port
    connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));  // Connect to the server

    socklen_t server_len = sizeof(server_addr);  // Get server info
    getpeername(client_fd, (struct sockaddr*)&server_addr, &server_len);
    char server_conn_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &server_addr.sin_addr, server_conn_ip, INET_ADDRSTRLEN);
    int server_conn_port = ntohs(server_addr.sin_port);

    char buffer[BUFFER_SIZE];  // Buffer to hold messages
    printf("Enter message to send: ");
    fgets(buffer, BUFFER_SIZE, stdin);  // Get input from the user
    buffer[strcspn(buffer, "\n")] = '\0';  // Remove the newline character

    send(client_fd, buffer, strlen(buffer), 0);  // Send the message
    printf("Client IP: %s, Sent: \"%s\"\n", client_ip, buffer);

    int bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);  // Receive the reversed message
    buffer[bytes_received] = '\0';  // Null-terminate the received message

    // Display the server's IP, port, and the received message
    printf("Received from Server IP: %s, Port: %d, Message: \"%s\"\n", server_conn_ip, server_conn_port, buffer);

    close(client_fd);  // Close the socket

    return 0;
}
