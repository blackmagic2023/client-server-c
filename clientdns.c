#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 8080
#define SERVER_HOSTNAME "example.com" // Change this to your server's DNS name

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char *hello = "Hello from client";
    char buffer[1024] = {0};

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    // Get server information using DNS
    if ((server = gethostbyname(SERVER_HOSTNAME)) == NULL) {
        fprintf(stderr,"gethostbyname failed\n");
        exit(EXIT_FAILURE);
    }

    // Set server address information
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Send data to server
    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    // Read response from server
    read(sock, buffer, 1024);
    printf("Server: %s\n", buffer);

    return 0;
}
