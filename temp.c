#include "build_system/COLL.h"


int main (void) {

    copying_files;


    copy "temp.c";

    char * dest = ".\\libadd";

    char c_cmd[cmd_length];

    COLL_FOREACH(Copy, sprintf(c_cmd, "copy %s %s >nul", elem, dest); system(c_cmd));

    COLL_FOREACH(Copy, sprintf(c_cmd, "\\cp -f %s %s > dev/null 2>&1", elem, dest); system(c_cmd));


    return 0;
}