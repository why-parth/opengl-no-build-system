#include <stdio.h>
#include <stdarg.h>

/*
This print function is very primitive.
This takes in a format string and replaces ALL
    the '?' char(s) with the given corresponding input.
*/
size_t print(const char * _format, ...) {
    size_t ret = 0;
    va_list args;
    va_start(args, _format);
    for (char c, inp; c = _format[ret++];) switch (c) {
        case '?': putchar(va_arg(args, int)); break;
        default: putchar(c);
    }
    return ret;
}