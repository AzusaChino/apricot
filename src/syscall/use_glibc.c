#include <stdio.h>

int main()
{
    int c = chmod("./obj", 0666);
    if (c == -1)
        perror("chmod failed\n");
    else
        printf("chmod succeed\n");
    return 0;
}
