#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_CLIENTS 10
#define PORT 9394

int main(int argc, char *argv[])
{

    // 1. create the server socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("failed to create server socket");
        exit(EXIT_FAILURE);
    }

    // 2. bind the socket to an addr:port
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    // TCPv4/IP
    server_addr.sin_family = AF_INET;
    // 0.0.0.0
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = ntohs(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("failed to bind socker to sockaddr");
        exit(EXIT_FAILURE);
    }

    // 3. start to listen
    if (listen(server_fd, MAX_CLIENTS) < 0)
    {
        perror("failed to listen");
        exit(EXIT_FAILURE);
    }

    // 4. setup the fd sets for the select() call
    fd_set read_fds;
    fd_set write_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&write_fds);

    // add the server socket to the read set

    FD_SET(server_fd, &read_fds);

    // track the maximum fd number
    int max_fd = server_fd;

    // setup an array to hold the client (connection) sockets
    int client_fds[MAX_CLIENTS];
    // set to -1 to indicate non-active fd
    memset(&client_fds, -1, sizeof(client_fds));

    // setup an array to hold the messages for each client
    char messages[MAX_CLIENTS][256];
    memset(&messages, 0, sizeof(messages));

    // loop to select active connections
    while (1)
    {
        // use select() to wait for activity on any of the fds
        int ready_fds = select(max_fd + 1, &read_fds, &write_fds, NULL, NULL);
        if (ready_fds < 0)
        {
            perror("failed to select");
            exit(EXIT_FAILURE);
        }

        // if the server socket is readable, that means a new client is trying to connect
        if (FD_ISSET(server_fd, &read_fds))
        {
            // accept the new connection
            struct sockaddr_in client_addr;
            socklen_t client_len = sizeof(client_addr);
            int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);

            if (client_fd < 0)
            {
                perror("failed to accept conenction");
                exit(EXIT_FAILURE);
            }

            // add the new client socket to the client array
            for (int i = 0; i < MAX_CLIENTS; i++)
            {
                if (client_fds[i] == -1)
                {
                    client_fds[i] = client_fd;
                    break;
                }
            }

            // add the new client socket to the read and write sets
            FD_SET(client_fd, &read_fds);
            FD_SET(client_fd, &write_fds);

            // update the maximum file descriptor number
            if (client_fd > max_fd)
            {
                max_fd = client_fd;
            }
            // decrement the number of ready file descriptors, since we just handled one
            ready_fds--;
        }

        // loop through the client sockets and check which ones are readable
        for (int i = 0; i < MAX_CLIENTS && ready_fds > 0; i++)
        {
            int client_fd = client_fds[i];
            if (client_fd == -1)
            {
                continue;
            }

            if (FD_ISSET(client_fd, &read_fds))
            {
                // read data from the client socket
                char buffer[256];
                int bytes_read = read(client_fd, buffer, sizeof(buffer));
                if (bytes_read == 0)
                {
                    // the client closed the connection, so remove it from the client array
                    FD_CLR(client_fd, &read_fds);
                    FD_CLR(client_fd, &write_fds);
                    close(client_fd);
                    client_fds[i] = -1;
                }
                else
                {
                    // append the data to the message buffer for the client
                    strncat(messages[i], buffer, bytes_read);
                }
                // decrement the number of ready file descriptors, since we just handled one
                ready_fds--;
            }

            // loop through the client sockets and check which ones are writable
            for (int i = 0; i < MAX_CLIENTS && ready_fds > 0; i++)
            {
                int client_fd = client_fds[i];
                if (client_fd == -1)
                {
                    continue;
                }

                if (FD_ISSET(client_fd, &write_fds))
                {
                    // write the message buffer to the client socket
                    write(client_fd, messages[i], strlen(messages[i]));
                    memset(messages[i], 0, sizeof(messages[i]));

                    // decrement the number of ready file descriptors, since we just handled one
                    ready_fds--;
                }
            }
        }
    }

    // n. shutdown server
    shutdown(server_fd, SHUT_RDWR);

    return 0;
}