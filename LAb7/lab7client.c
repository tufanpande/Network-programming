//WRITE A PROGRAM TO BROADCCAST DATA FROM SERVER TO MULTIPLE CLIENTS  FOR SOCKET PROGRAMMING

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define LISTEN_PORT 12345 //The port on which the client listens for broadcast messages.
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in listen_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(listen_addr);

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up the listening address structure
    memset(&listen_addr, 0, sizeof(listen_addr));//clears the buffer to ensure no residual data is present.
    listen_addr.sin_family = AF_INET;
    listen_addr.sin_port = htons(LISTEN_PORT);
    listen_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind the socket to the address and port
    if (bind(sockfd, (struct sockaddr *)&listen_addr, sizeof(listen_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Listening for broadcast messages on port %d...\n", LISTEN_PORT);

    while (1) {
        // Receive broadcast messages
        memset(buffer, 0, BUFFER_SIZE);
        if (recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&listen_addr, &addr_len) < 0) {
            perror("Receive failed");
        } else {
            printf("Received broadcast: %s\n", buffer);
        }
    }

    close(sockfd);
    return 0;
}