#include <stdio.h>
#include <errno.h>
#include <sys/syscall.h>
#include <sys/types.h>

// FIXME not successful yet

int main()
{
    long rc;
    unsigned short mode = 0777;
    const char *file = "obj";
    // inline assembly
    asm(
        "int $0x80"
        : "=a"(rc)
        : "0"(SYS_chmod), "b"((long)file), "c"((long)mode));
    if (rc == -1)
        perror("SYS_chmod failed\n");
    else
        printf("SYS_chmod succeed\n");
    return 0;
}
