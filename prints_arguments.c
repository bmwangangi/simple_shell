#include <stdio.h>

int main(int argc, char *argv[])
{
    int a = 1;

    while (argv[a]) {
        printf("%s\n", argv[a]);
        a++;
    }

    return 0;
}

