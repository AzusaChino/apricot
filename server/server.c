#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define MAX_CONNECTIONS 10
#define BUFFER_SIZE 1024

int main(void)
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr;

    // Create socket file descriptor (IPv4, TCP)
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_family = AF_INET;

    // Bind socket to address
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, MAX_CONNECTIONS) < 0)
    {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    // Accept connections
    while (1)
    {
        if ((client_fd = accept(server_fd, (struct sockaddr *)NULL, NULL)) < 0)
        {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        // Read from client
        char buffer[BUFFER_SIZE];
        int valread = read(client_fd, buffer, BUFFER_SIZE);
        printf("%s\n", buffer);

        // Write to client
        char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 20\n\nHello from server";
        ssize_t bytes_sent = send(client_fd, hello, strlen(hello), 0);
        if (bytes_sent == -1)
        {
            perror("Send failed");
            close(client_fd);
            exit(EXIT_FAILURE);
        }
        printf("Hello message sent\n");

        if (close(client_fd) == -1)
        {
            perror("Close failed");
        }
    }

    return 0;
}
