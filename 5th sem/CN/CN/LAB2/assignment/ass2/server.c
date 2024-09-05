#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024  // Buffer size for messages

// Function to reverse a string
void reverse_string(char *str) {
    for (int i = 0, len = strlen(str); i < len / 2; i++) {
        char temp = str[i];               // Swap characters
        str[i] = str[len - i - 1];        // from start and end
        str[len - i - 1] = temp;
    }
}

int main(int argc, char *argv[]) {
    // Ensure correct usage of command-line arguments
    if (argc != 3) return printf("Usage: %s <server_ip> <server_port>\n", argv[0]), 1;

    // Create server socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0), client_fd;
    
    // Setup server address (IP, Port, and address family)
    struct sockaddr_in server_addr = {AF_INET, htons(atoi(argv[2])), inet_addr(argv[1])}, client_addr;
    
    // Buffer to store received message and variable for client IP address
    char buffer[BUFFER_SIZE], client_ip[INET_ADDRSTRLEN];
    
    // Variable to store size of client address
    socklen_t client_len = sizeof(client_addr);

    // Bind the server to IP and port
    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    // Listen for incoming connections
    listen(server_fd, 1);
    printf("Server listening on %s:%s\n", argv[1], argv[2]);

    // Accept a connection from a client
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);

    // Convert client IP from binary to text form
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);

    // Receive message from the client
    int bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
    buffer[bytes_received] = '\0';  // Null-terminate the received string

    // Display client's IP, port, and the received message
    printf("Received from Client IP: %s, Port: %d, Message: \"%s\"\n", client_ip, ntohs(client_addr.sin_port), buffer);

    // Reverse the received message
    reverse_string(buffer);

    // Send the reversed message back to the client
    send(client_fd, buffer, strlen(buffer), 0);
    printf("Server IP: %s, Sent: \"%s\"\n", argv[1], buffer);

    // Close client and server sockets
    close(client_fd);
    close(server_fd);

    return 0;
}
