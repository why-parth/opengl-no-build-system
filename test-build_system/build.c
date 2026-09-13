#include "../build_system/COLL.h"

config {

    libc;

    static_link "print.o";

    in "main.c";
    
    out "app";

    run;

}