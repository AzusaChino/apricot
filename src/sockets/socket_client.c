#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9394
#define BUFFER_SIZE 1024

int main(int argc, char **argv)
{
    // Create a socket (ipv4)
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("failed to create socket");
        exit(1);
    }

    // connect to the server
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) <= 0)
    {
        perror("failed to convert localhost");
        exit(1);
    }

    int connected_fd;
    if ((connected_fd = connect(sock, (struct sockaddr *)&addr, sizeof(addr))) < 0)
    {
        perror("failed to connect to server");
        exit(1);
    }

    // send hello
    const char *msg = "hello world";
    if (send(sock, msg, strlen(msg), 0) < 0)
    {
        perror("failed to send msg");
        exit(1);
    }
    printf("Hello world sent\n");

    char buffer[BUFFER_SIZE] = {0};
    read(sock, buffer, BUFFER_SIZE);
    printf("Received from server: %s\n", buffer);

    close(connected_fd);
    return 0;
}