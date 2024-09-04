#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8000

int main() {
    int sockfd, bytes_sent, byte_received;
    char buffer[1024], *msg = "hi server";
    struct sockaddr_in serveraddr = {0};

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 || 
        (bytes_sent = sendto(sockfd, msg, strlen(msg), 0, 
        (struct sockaddr *)&serveraddr, sizeof(serveraddr))) < 0 || 
        (byte_received = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL)) < 0) {
        perror("Error");
        close(sockfd);
        return EXIT_FAILURE;
    }

    buffer[byte_received] = '\0';
    printf("Server: %s\n", buffer);
    close(sockfd);
    return 0;
}
