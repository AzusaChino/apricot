/**
 * Linux 内核提供了一组宏，用于实现系统调用接口函数；实现系统调用后应用程序就可以使用该系统调用。
 */
#include <stdio.h>

// the `syscall` wrapper function
#include <unistd.h>

// syscall definition list
#include <sys/syscall.h>
#include <errno.h>

#ifndef __NR_test
// refers unistd_64.h
#define __NR_test 450
#endif

// FIXME setup custom syscall (test)

static inline int test(void)
{
    long __res;
    __asm__ volatile("int $0x80"
                     : "=a"(__res)
                     : "0"(__NR_test));
    if (__res >= 0)
        return (int)__res;
    errno = -__res;
    return -1;
}

// _syscall0(int, test);

int main()
{
    int rc = test();
    if (rc == -1)
        perror("test fail\n");
    else
        printf("test succeed\n");
    return 0;
}
