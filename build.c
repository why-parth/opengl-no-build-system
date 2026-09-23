// clear ; gcc .\build.c -o build; if ($?) {.\build}
#include "build_system/COLL.h"

config {

    libc;

    link "add.dll.a";

    copy "add.dll";
    paste "BUILD\\new";

    in "main.c";

    out "run";

    build "BUILD\\new";

    run;

}
