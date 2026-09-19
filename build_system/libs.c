#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define cmd_length 1024

#ifdef _WIN32 
#define LIBS__os_shared_object_flag " -shared \"-Wl,--out-implib,%.*s.dll.a\" "
#define LIBS__os_shared_object_filetype ".dll"

#elif defined(__APPLE__)
#define LIBS__os_shared_object_flag " -dynamiclib "
#define LIBS__os_shared_object_filetype ".dylib"

#else
#define LIBS__os_shared_object_flag " -shared fPIC "
#define LIBS__os_shared_object_filetype ".so"

#endif

#ifdef _WIN32
#define LIBS__os_path_sep '\\'
#define LIBS__os_empty_dir(_path) system("cmd /c if exist \"" _path "\" (rmdir /s /q \"" _path  "\") & mkdir \"" _path "\"")
#define LIBS__os_empty_dir_fstr "cmd /c if exist \"%s\" (rmdir /s /q \"%s\") & mkdir \"%s\""
#define LIBS__os_empty_dir_fstr_n "cmd /c if exist \"%.*s\" (rmdir /s /q \"%.*s\") & mkdir \"%.*s\""
#define LIBS__os_prep_dir_fstr "cmd /c mkdir \"%s\""
#define LIBS__os_prep_dir_fstr_n "cmd /c mkdir \"%.*s\""
#else
#define LIBS__os_path_sep '/'
#define LIBS__os_empty_dir(_path) system("rm -rf \"" _path "\"; mkdir \"" _path "\"")
#define LIBS__os_empty_dir_fstr "rm -rf \"%s\"; mkdir \"%s\""
#define LIBS__os_empty_dir_fstr_n "rm -rf \"%.*s\"; mkdir \"%.*s\""
#define LIBS__os_prep_dir_fstr "mkdir -p \"%s\""
#define LIBS__os_prep_dir_fstr_n "mkdir -p \"%.*s\""
#endif

#define LIBS__os_empty_dir_printf_str(_path) LIBS__os_empty_dir_fstr, _path, _path, _path
#define LIBS__os_empty_dir_printf_str_n(_path, _n) LIBS__os_empty_dir_fstr_n, _n, _path, _n, _path, _n, _path
#define LIBS__os_prep_dir_printf_str(_path) LIBS__os_prep_dir_fstr, _path
#define LIBS__os_prep_dir_printf_str_n(_path, _n) LIBS__os_prep_dir_fstr_n, _n, _path


int main(int argc, const char * argv[]) {

    char sys_cmd[cmd_length];

    unsigned int flag_i[32];
    unsigned int flags = 0;
    char flag[cmd_length];

    int output_defined = 0;
    char output_name[cmd_length];
    char * output_path;

    int overwrite = 0;

    switch (argc)
    {
    case 1:
        printf("\033[1;31mNo Input File \033[0m");
        break;
    default:

        // Flag Pass
        for (int i = 1; i < argc; i++) {

            switch (argv[i][0]) {
                case '-':
                    flag_i[flags++] = i;
                    if (!strcmp(argv[i] + 1, "o")) {
                        flag_i[flags++] = ++i;
                        output_defined = 1;
                        if (((size_t)(strrchr(argv[i], LIBS__os_path_sep)) - (size_t)(argv[i])) == 1)
                        sprintf(output_name, "%s", argv[i] + 2);
                        else {
                            sprintf(output_name, "%s", argv[i]);
                            if (strrchr(argv[i], LIBS__os_path_sep)) {
                                if (overwrite)
                                sprintf(sys_cmd, LIBS__os_empty_dir_printf_str_n(
                                        output_name,
                                        ((size_t)strrchr(output_name, LIBS__os_path_sep) - (size_t)output_name)
                                    )
                                );
                                else
                                sprintf(sys_cmd, LIBS__os_prep_dir_printf_str_n(
                                        output_name,
                                        ((size_t)strrchr(output_name, LIBS__os_path_sep) - (size_t)output_name)
                                    )
                                );
                                system(sys_cmd);
                            }
                        }
                    }

                    if (!strcmp(argv[i] + 1, "w")) {
                        overwrite = 1;
                    }
            }

        }

        // Library Creation
        for (int i = 1; i < argc; i++) {

            for (int j = 0; j < flags; j++) if (flag_i[j] == i) goto CONTINUE;

            output_path = output_defined ? output_name : (char *)argv[i];

            // Static Library
            sprintf(
                sys_cmd, " \033[45m \033[49;1;33m gcc \033[1;32m%s\033[3;34m \033[0m\033[3m-c -o \033[1;33m%.*s.o\033[0m",
                argv[i],
                (size_t)(strrchr(output_path + 2, '.')) - (size_t)(output_path),
                output_path
            );
            printf(sys_cmd);
            putchar('\n');

            
            sprintf(
                sys_cmd, "gcc %s -c -o %.*s.o",
                argv[i],
                (size_t)(strrchr(output_path + 2, '.')) - (size_t)(output_path),
                output_path
            );
            system(sys_cmd);


            // Archiving Static Library
            sprintf(
                sys_cmd, "   \033[1;33mar \033[3;34mrcs \033[0m\033[1;33m%.*s.a \033[32m%.*s.o\033[0m",
                (size_t)(strrchr(output_path + 2, '.')) - (size_t)(output_path),
                output_path,
                (size_t)(strrchr(output_path + 2, '.')) - (size_t)(output_path),
                output_path
            );
            printf(sys_cmd);
            putchar('\n');
            
            sprintf(
                sys_cmd, "ar rcs %.*s.a %.*s.o",
                (size_t)(strrchr(output_path + 2, '.')) - (size_t)(output_path),
                output_path,
                (size_t)(strrchr(output_path + 2, '.')) - (size_t)(output_path),
                output_path
            );
            system(sys_cmd);


            // Dynamic Library
            sprintf(
                sys_cmd, " \033[45m \033[49;1;33m gcc \033[1;32m%s\033[3;34m" LIBS__os_shared_object_flag "\033[0m\033[3m-o \033[0m\033[1;33m%.*s" LIBS__os_shared_object_filetype "\033[0m",
                argv[i],
                #ifdef _WIN32
                (size_t)(strrchr(output_path + 2, '.')) - (size_t)(output_path),
                output_path,
                #endif
                (size_t)(strrchr(output_path + 2, '.')) - (size_t)(output_path),
                output_path
            );
            printf(sys_cmd);
            putchar('\n');
            
            sprintf(
                sys_cmd, "gcc %s" LIBS__os_shared_object_flag "-o %.*s" LIBS__os_shared_object_filetype,
                argv[i],
                #ifdef _WIN32
                (size_t)(strrchr(output_path + 2, '.')) - (size_t)(output_path),
                output_path,
                #endif
                (size_t)(strrchr(output_path + 2, '.')) - (size_t)(output_path),
                output_path
            );
            system(sys_cmd);


            /*
            NOT using this, the dlltool is not able to resolve the GCC exported symbols.
            Solution:
                Instead of exporting the symbols out of GCC, we will make GCC out a .dll.a ,
                this will take much efforts compared to dlltool but what can I do, the dlltool does not work.
            */
            // Import Static Library 
            // sprintf(
            //     sys_cmd, "   \033[1;33mdlltool \033[0m\033[3m-D\033[0m \033[1;32m%.*s.dll\033[0m \033[3m-l\033[0m \033[1;33m%.*s.dll.a\033[0m \033[3m2>$null\033[0m",
            //     (size_t)(strrchr(output_path + 2, '.')) - (size_t)(output_path),
            //     output_path,
            //     (size_t)(strrchr(output_path + 2, '.')) - (size_t)(output_path),
            //     output_path
            // );
            // printf(sys_cmd);
            // putchar('\n');

            // sprintf(
            //     sys_cmd, "dlltool -D %.*s.dll -l %.*s.dll.a 2>$null",
            //     (size_t)(strrchr(output_path + 2, '.')) - (size_t)(output_path),
            //     output_path,
            //     (size_t)(strrchr(output_path + 2, '.')) - (size_t)(output_path),
            //     output_path
            // );
            // system(sys_cmd);

            CONTINUE:
        }
    }

    return 0;
}