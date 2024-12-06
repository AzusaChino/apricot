#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Read a line of arbitrary size from a file
//
// Returns a pointer to the line.
// Returns NULL on EOF or error.
//
// It's up to the caller to free() this pointer when done with it.
//
// Note that this strips the newline from the result. If you need
// it in there, probably best to switch this to a do-while.
char *readline(FILE *fp);

int main(void)
{
    FILE *fp; // Variable to represent open file

    fp = fopen("hello.txt", "r"); // Open file for reading

    // int c = fgetc(fp);             // Read a single character
    // printf("%c\n", c);             // Print char to stdout
    int c;

    while ((c = fgetc(fp)) != EOF)
    {
        printf("%c", c);
    }

    fclose(fp); // Close the file when done

    printf("%d\n", LLONG_MAX);
}

char *readline(FILE *fp)
{
    int offset = 0;
    int buf_size = 4;
    char *buf = malloc(buf_size);

    if (buf == NULL)
    {
        return NULL;
    }

    int c;

    while (c = fgetc(fp), c != '\n' && c != EOF)
    {
        // -1 for the NUL terminator
        if (offset == buf_size - 1)
        {
            buf_size *= 2;
            char *new_buf = realloc(buf, buf_size);
            // if realloc fails, free the original buffer and return NULL
            if (new_buf == NULL)
            {
                free(buf);
                return NULL;
            }
            buf = new_buf;
        }
        buf[offset++] = c;
    }

    // nothing in the file
    if (c == EOF && offset == 0)
    {
        free(buf);
        return NULL;
    }

    // shrink to fit
    if (offset < buf_size - 1)
    {
        char *new_buf = realloc(buf, offset + 1); // +1 for NUL terminator
        if (new_buf != NULL)
        {
            buf = new_buf;
        }
    }
    // add the NUL terminator
    buf[offset] = '\0';
    return buf;
}
