#include <stdio.h>
#include <stdlib.h>

#define SQR(x) x *x
// use brackets to avoid unexpected results
#define SQR_2(x) ((x) * (x))

#define MAX(a, b) ((a) > (b) ? (a) : (b))

// macros with multiple arguments
#define TRIANGLE_AREA(w, h) (0.5 * (w) * (h))

// macros with variable number of arguments
#define SUM(...) sum(__VA_ARGS__)

int main(void)
{
    printf("Hello, world!\n");
    printf("%d\n", SQR(12));       // 144
    printf("%d\n", SQR(4 + 3));    // 19
    printf("%d\n", 4 + 3 * 4 + 3); // 19
    printf("%d\n", SQR_2(4 + 3));  // 49

    printf("%d\n", SUM(1, 2, 3, 4, 5));
}

#define ASSERT_ENABLED 1

#if ASSERT_ENABLED
#define ASSERT(c, m)                                                   \
    do                                                                 \
    {                                                                  \
        if (!(c))                                                      \
        {                                                              \
            fprintf(stderr, __FILE__ ":%d: assertion %s failed: %s\n", \
                    __LINE__, #c, m);                                  \
            exit(1);                                                   \
        }                                                              \
    } while (0)
#else
#define ASSERT(c, m) // Empty macro if not enabled
#endif

int main2(void)
{
    int x = 30;

    ASSERT(x < 20, "x must be under 20");
}