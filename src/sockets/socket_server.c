#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 9394
#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("failed to create socket");
        exit(1);
    }

    // forcefully attaching socket to the port
    int opt = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("failed to set sock opt");
        exit(1);
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    // 0.0.0.0
    addr.sin_addr.s_addr = INADDR_ANY;
    // tranlate port
    addr.sin_port = htons(PORT);

    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("failed to bind socket");
        exit(1);
    }

    if (listen(sock, 3) < 0)
    {
        perror("failed to listen socket");
        exit(1);
    }

    // dispatch new socket to accept client msg
    int new_sock;
    int addr_len = sizeof(addr);
    if ((new_sock = accept(sock, (struct sockaddr *)&addr, (socklen_t *)&addr_len)) < 0)
    {
        perror("failed to accept connection");
        exit(1);
    }

    char buffer[BUFFER_SIZE] = {0};
    char *hello = "Hello from Server";
    read(new_sock, buffer, BUFFER_SIZE);

    printf("Received from client: %s\n", buffer);
    send(new_sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    close(new_sock);

    shutdown(sock, SHUT_RDWR);
    return 0;
}