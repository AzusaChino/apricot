#include <stdio.h>
#include <string.h>

int main()
{

    int arr[10];

    // set every memory block to 0
    memset(&arr, 0, sizeof(arr));

    for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
    {
        printf("check this %d\n", arr[i]);
    }

    return 0;
}