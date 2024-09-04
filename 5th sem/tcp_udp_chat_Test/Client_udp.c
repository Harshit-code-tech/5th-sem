#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in servaddr;
    socklen_t len;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    len = sizeof(servaddr);

    while (1) {
        printf("Client: ");
        fgets(buffer, 1024, stdin);
        sendto(sockfd, buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *) &servaddr, len);

        if (strcmp(buffer, "exit\n") == 0 || strcmp(buffer, "bye\n") == 0) {
            printf("Closing connection.\n");
            break;
        }

        memset(buffer, 0, sizeof(buffer));
        recvfrom(sockfd, buffer, 1024, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
        printf("Server: %s\n", buffer);

        if (strcmp(buffer, "exit\n") == 0 || strcmp(buffer, "bye\n") == 0) {
            printf("Connection closed by server.\n");
            break;
        }
    }

    close(sockfd);
    return 0;
}
