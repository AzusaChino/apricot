#include <stdio.h>

void printp(void *pp)
{
    printf("%p \r\n", pp);
    printf("%p \r\n", &pp);
}

int main(void)
{
    int i = 0;
    int *ip = &i;

    printf("%p\n", (void *)&i);
    printf("%p\n", (void *)&ip);
    printp(ip);
}
