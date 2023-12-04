#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av) {
    /* Start from av[1] as av[0] usually contains the program name */
    int a = 1;
    int sum = 0;

    /* Use av[a] directly in the loop condition */
    while (av[a]) {
        printf("%s\n", av[a]);

        /* Convert the argument to an integer and add to the sum */
        int current_num = atoi(av[a]);
        sum += current_num;

        a++;
    }

    /* Print the sum */
    printf("Sum of the numbers: %d\n", sum);

    return 0;
}

