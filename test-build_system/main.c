#include <stdio.h>
#include <stdarg.h>

/*
This function is in the library print.o .
*/
size_t print(const char * _format, ...);

int main (const int argc, const char * argv[]) {

    print("formatted char : '?'", 'A');

    return 0;
}