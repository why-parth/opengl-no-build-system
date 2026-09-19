#include <stdio.h>

#include "libadd\add.h"

int main (void) {

    printf("program starts!\n");

    int inp;
    printf("Enter the int : \033[1;33m");
    scanf("%d", &inp);
    printf("\033[0m");

    printf("\033[3;35mYou typed %d!\033[0m\n", inp);
    printf("\033[33m%d\033[0m + \033[33m10\033[0m = \033[36m%d\033[0m\n", inp, add(inp, 10));

    printf("program ends!\n\n");

    return 0;
}