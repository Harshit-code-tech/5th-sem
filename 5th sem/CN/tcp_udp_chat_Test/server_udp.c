#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    len = sizeof(cliaddr);

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        recvfrom(sockfd, buffer, 1024, MSG_WAITALL, (struct sockaddr *) &cliaddr, &len);
        printf("Client: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0 || strcmp(buffer, "bye") == 0) {
            printf("Connection closed by client.\n");
            break;
        }

        printf("Server: ");
        fgets(buffer, 1024, stdin);
        sendto(sockfd, buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);

        if (strcmp(buffer, "exit\n") == 0 || strcmp(buffer, "bye\n") == 0) {
            printf("Closing connection.\n");
            break;
        }
    }

    close(sockfd);
    return 0;
}
