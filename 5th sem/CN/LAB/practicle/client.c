#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    int choice;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    printf("Enter a string (minimum 5 characters): ");
    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    send(client_socket, buffer, strlen(buffer), 0);

    recv(client_socket, buffer, BUFFER_SIZE, 0);
    printf("%s\n", buffer);

    printf("Enter your choice: ");
    scanf("%d", &choice);
    choice = htonl(choice);
    send(client_socket, &choice, sizeof(int), 0);

    recv(client_socket, buffer, BUFFER_SIZE, 0);
    printf("Result from server: \n%s\n", buffer);

    close(client_socket);
    return 0;
}
