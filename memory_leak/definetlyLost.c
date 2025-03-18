#include <stdlib.h>

void func()
{
    char *buff = malloc(10);
    /* 
     * without free allocated memory of buff 
     * leads to definetly lost
     */
    // free(buff);
}

int main()
{
    func();
    return 0;
}
