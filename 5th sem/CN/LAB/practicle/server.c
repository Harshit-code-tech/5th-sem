#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int choice;

    recv(client_socket, buffer, BUFFER_SIZE, 0);
    if (strlen(buffer) < 5) {
        printf("Received string is too short.\n");
        close(client_socket);
        return;
    }
    
    printf("Received from client: %s\n", buffer);

    char menu[] = "Choose an option:\n"
                  "1) Upper case all characters\n"
                  "2) Lower case all characters\n"
                  "3) Count total number of characters\n"
                  "4) Reverse the characters\n";
    send(client_socket, menu, strlen(menu), 0);

    recv(client_socket, &choice, sizeof(int), 0);
    choice = ntohl(choice);

    switch (choice) {
        case 1:  
            for (int i = 0; i < strlen(buffer); i++) {
                buffer[i] = toupper(buffer[i]);
            }
            printf("Converted to upper case: %s\n", buffer);

            break;
        case 2:  
            for (int i = 0; i < strlen(buffer); i++) {
                buffer[i] = tolower(buffer[i]);

            }
            printf("Converted to lower case: %s\n", buffer);
            break;
        case 3:  
            sprintf(buffer, "Total characters: %ld\n", strlen(buffer));

            break;
        case 4:  
            for (int i = 0; i < strlen(buffer) / 2; i++) {
                char temp = buffer[i];
                buffer[i] = buffer[strlen(buffer) - i - 1];
                buffer[strlen(buffer) - i - 1] = temp;
            }
            printf("Reversed string: %s\n", buffer);
            break;
        default:
            strcpy(buffer, "Invalid choice.");
            break;
    }
    send(client_socket, buffer, strlen(buffer), 0);
    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 3) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        if (fork() == 0) {
            close(server_socket);
            handle_client(client_socket);
            exit(0);
        }
        close(client_socket);
    }

    close(server_socket);
    return 0;
}
