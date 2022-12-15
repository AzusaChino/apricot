#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <string.h>

#define BUFFER_SIZE 1024

int main()
{
    int fd;
    char *path = "./foo.txt";
    char buffer[BUFFER_SIZE];

    memset(&buffer, 0, sizeof(buffer));

    fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        perror("failed to open file");
        exit(EXIT_FAILURE);
    }

    if (read(fd, buffer, 1024) < 0)
    {

        perror("failed to read from fd");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", buffer);

    close(fd);

    return 0;
}
