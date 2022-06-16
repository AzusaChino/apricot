#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

#include "helper_tool.h"

int main(int argc, char *argv[])
{

    size_t len;
    off_t offset;
    int fd, ap, j;
    unsigned char *buf;
    ssize_t num_read, num_written;

    if (argc < 3 || strcmp(argv[1], "--help") == 0)
    {
        usageErr("%s file {r<length>|R<length>|w<string>|s<offset>}...\n", argv[0]);
    }

    fd = open(argv[1], O_RDWR | O_CREAT,
              S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWGRP);
    if (fd == -1)
        errExit("fail to open");

    for (ap = 2; ap < argc; ap++)
    {
        switch (argv[ap][0])
        {
        case 'r': /* Display bytes at current offset, as text */
        case 'R': /* Display bytes at current offset, in hex */
            len = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);

            buf = malloc(len);
            if (buf == NULL)
                errExit("malloc");

            num_read = read(fd, buf, len);
            if (num_read == -1)
                errExit("read");

            if (num_read == 0)
            {
                printf("%s: end-of-file\n", argv[ap]);
            }
            else
            {
                printf("%s: ", argv[ap]);
                for (j = 0; j < num_read; j++)
                {
                    if (argv[ap][0] == 'r')
                        printf("%c", isprint(buf[j]) ? buf[j] : '?');
                    else
                        printf("%02x ", buf[j]);
                }
                printf("\n");
            }

            free(buf);
            break;

        case 'w': /* Write string at current offset */
            num_written = write(fd, &argv[ap][1], strlen(&argv[ap][1]));
            if (num_written == -1)
                errExit("write");
            printf("%s: wrote %ld bytes\n", argv[ap], (long)num_written);
            break;

        case 's': /* Change file offset */
            offset = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);
            if (lseek(fd, offset, SEEK_SET) == -1)
                errExit("lseek");
            printf("%s: seek succeeded\n", argv[ap]);
            break;

        default:
            cmdLineErr("Argument must start with [rRws]: %s\n", argv[ap]);
        }
    }

    if (close(fd) == -1)
        errExit("close");

    exit(EXIT_SUCCESS);
}
