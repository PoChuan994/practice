#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    /* invalid write */
    char *str = malloc(4);
    strcpy(str, "Curry");
    free(str);

    /* invalid read */
    int *arr = malloc(3);
    printf("%d", arr[4]);
    free(arr);

    /* invalid read */
    printf("%d", arr[0]);

    /* invalud free */
    free(arr);

    return 0;
}
