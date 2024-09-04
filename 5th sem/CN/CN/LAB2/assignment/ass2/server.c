#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

void reverse_string(char *str) {
    for (int i = 0, n = strlen(str); i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

int main(int argc, char *argv[]) {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0), client_socket;
    struct sockaddr_in server_addr = { .sin_family = AF_INET, .sin_port = htons(atoi(argv[2])), .sin_addr.s_addr = inet_addr(argv[1]) };
    char buffer[BUFFER_SIZE];

    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_socket, 5);

    client_socket = accept(server_socket, NULL, NULL);
    recv(client_socket, buffer, BUFFER_SIZE, 0);

    reverse_string(buffer);

    send(client_socket, buffer, strlen(buffer), 0);

    close(client_socket);
    close(server_socket);

    return 0;
}
