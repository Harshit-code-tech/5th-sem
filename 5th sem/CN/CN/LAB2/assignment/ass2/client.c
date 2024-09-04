#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in client_addr = { .sin_family = AF_INET, .sin_port = htons(atoi(argv[2])), .sin_addr.s_addr = inet_addr(argv[1]) };
    struct sockaddr_in server_addr = { .sin_family = AF_INET, .sin_port = htons(atoi(argv[4])), .sin_addr.s_addr = inet_addr(argv[3]) };
    char buffer[BUFFER_SIZE];

    bind(client_socket, (struct sockaddr*)&client_addr, sizeof(client_addr));
    connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    send(client_socket, buffer, strlen(buffer), 0);

    recv(client_socket, buffer, BUFFER_SIZE, 0);
    printf("Received: \"%s\"\n", buffer);

    close(client_socket);

    return 0;
}
