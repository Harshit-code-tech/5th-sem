#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 8000
#define MAX_CLIENTS 10

int clients[MAX_CLIENTS], client_count = 0;
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void *handle_client(void *arg) {
    int client_sock = *(int *)arg, bytes_received;
    char buffer[1024];

    while ((bytes_received = recv(client_sock, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytes_received] = '\0';
        printf("Received: %s\n", buffer);

        pthread_mutex_lock(&clients_mutex);
        for (int i = 0; i < client_count; i++)
            if (clients[i] != client_sock) send(clients[i], buffer, bytes_received, 0);
        pthread_mutex_unlock(&clients_mutex);
    }

    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < client_count; i++)
        if (clients[i] == client_sock) clients[i] = clients[--client_count];
    pthread_mutex_unlock(&clients_mutex);

    close(client_sock);
    free(arg);
    return NULL;
}

int main() {
    int server_sock = socket(AF_INET, SOCK_STREAM, 0), *client_sock;
    struct sockaddr_in serveraddr = { .sin_family = AF_INET, .sin_port = htons(PORT), .sin_addr.s_addr = INADDR_ANY };
    socklen_t client_len = sizeof(struct sockaddr_in);

    bind(server_sock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(server_sock, MAX_CLIENTS);

    printf("Server listening on port %d\n", PORT);

    while (1) {
        client_sock = malloc(sizeof(int));
        *client_sock = accept(server_sock, (struct sockaddr *)&serveraddr, &client_len);

        pthread_mutex_lock(&clients_mutex);
        clients[client_count++] = *client_sock;
        pthread_mutex_unlock(&clients_mutex);

        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, client_sock);
    }

    close(server_sock);
    return 0;
}
