#include <stdlib.h>

static int *ptr;

void func()
{
    ptr = malloc(sizeof(int));
    *ptr = 100;
}

int main()
{
    func();
    return 0;
]
