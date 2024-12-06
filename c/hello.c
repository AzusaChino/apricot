#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    bool x = true;
    if (x)
    {
        printf("x is true!\n");
    }
    int a = 999;

    // %zu is the format specifier for type size_t

    printf("%zu\n", sizeof a);      // Prints 4 on my system
    printf("%zu\n", sizeof(2 + 7)); // Prints 4 on my system
    printf("%zu\n", sizeof 3.14);   // Prints 8 on my system

    int i = 10;

    printf("The value of i is %d\n", i);
    printf("And its address is %p\n", (void *)&i);
}
