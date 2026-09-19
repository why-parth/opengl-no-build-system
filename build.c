// clear ; gcc .\build.c -o build; if ($?) {.\build}
#include "build_system/COLL.h"

config {

    libc;

    in ".\\main.c";

    static_link "add.dll.a";

    search "libadd";

    out "run";

    build ".\\Build";

    copy ".\\libadd\\add.dll";
    paste ".\\Build";

    run;

}
