#include <stdio.h>

// the `syscall` wrapper function
#include <unistd.h>

// syscall definition list
#include <sys/syscall.h>

int main()
{
    int c = syscall(SYS_chmod, "./obj", 0777);
    if (c == -1)
        perror("SYS_chmod failed\n");
    else
        printf("SYS_chmod succeed\n");
    return 0;
}
