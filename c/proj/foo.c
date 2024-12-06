#include <stdio.h>
#include <stdlib.h>

#include "bar.h"

int main(void)
{
    printf("%d\n", add(2, 3));
}

// add all input up
int main2(int argc, char **argv)
{
    int total = 0;

    // trick to get the complier to stop warning about the unused variable
    (void)argc;

    for (char **p = argv + 1; *p != NULL; p++)
    {
        int value = strtol(*p, NULL, 10);
        total += value;
    }
    printf("%d\n", total);
    return 0;
}
