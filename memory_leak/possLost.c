#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *s = "string"
    char *p = strdup(s);

    p += 1;
    abort();

    /* the statements below will not be executed*/
    p -= 1;
    free(p);
    
    return 0;
}
