// clear ; gcc .\build.c -o build; if ($?) {.\build}
#include "build_system/COLL.h"

config {

    libc;

    link ".\\libadd\\add.dll";

    in "main.c";

    out "run";

    // build ".\\build";

    run;

}
