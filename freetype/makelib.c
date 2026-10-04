/*
OpenGL has no internal support for font rendering, therefore, FreeType is used.
FreeType is an industry-standard open-source C library.
Many popular implementations like Mac, Linux, PlayStation rely on FreeType.

I am doing all of the development in windows, and, there is a problem.
The FreeType library for windows is compiled using MSVC (cl.exe), therefore,
the ABI of FreeType library is incompatible with GCC compiled code.

To use FreeType, I will have to manually re-compile the C source files of 
FreeType into a library.

Luckily, when I was developing my own build system (COLL.h) I also developed
my own library maker (libs.c) which compiles into a command like utility
allowing me to convert any C file(s) into a complete ready-to-use library.

This C source file 'makelib.c' must be run in the folder containing the 'freetype' folder (folder containing this file).
*/

// gcc build_system\libs.c -o libs; if ($?) { gcc .\freetype\makelib.c -o run ; if ($?) {clear ; .\run.exe } }

#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#define sep "\\"
#define ext ".exe"
#else
#define sep "/"
#define ext 
#endif

#define DIRNAME "." sep "library" sep "ft"
#define LIBNAME "libft"

int main (void) {

    char cmd[] = ""
    "." sep "libs" ext " "
    "freetype" sep "src" sep "base" sep "ftmm.c "
    "freetype" sep "src" sep "gzip" sep "ftgzip.c "
    "freetype" sep "src" sep "base" sep "ftsystem.c "
    "freetype" sep "src" sep "base" sep "ftinit.c "
    "freetype" sep "src" sep "base" sep "ftdebug.c "
    "freetype" sep "src" sep "base" sep "ftbase.c "
    "freetype" sep "src" sep "base" sep "ftbbox.c "
    "freetype" sep "src" sep "base" sep "ftglyph.c "
    "freetype" sep "src" sep "base" sep "ftbitmap.c "
    "freetype" sep "src" sep "sfnt" sep "sfnt.c "
    "freetype" sep "src" sep "psnames" sep "psnames.c "
    "freetype" sep "src" sep "truetype" sep "truetype.c "
    "freetype" sep "src" sep "smooth" sep "smooth.c "
    "-w -f "
    "-o " DIRNAME sep LIBNAME " "
    ": -Ifreetype" sep "include -DFT2_BUILD_LIBRARY"
    ;

    system(cmd);

    return 0;
}