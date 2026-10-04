#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define cmd_length 4096

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

    char shared_lib_input[cmd_length];
    unsigned int shared_lib_input_i = 0;
    char shared_static_lib_input[cmd_length];
    unsigned int shared_static_lib_input_i = 0;

    

    int overwrite = 0;

    int multi = 0;

    int gcc = 0;
    char gcc_string[cmd_length] = ""; 
    unsigned int gcc_string_i = 0; 

    int shared_only = 0;
    char temp_output_path[cmd_length];

    switch (argc)
    {
    case 1:
        printf("\033[1;31mNo Input File \033[0m");
        break;
    default:

        // Flag Pass
        for (int i = 1; i < argc; i++) {

            if (gcc) {
                gcc_string_i += sprintf(gcc_string + gcc_string_i, "%s ", argv[i]);
            }

            switch (argv[i][0]) {
                case ':':
                gcc = i;
                break;

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

                    else if (!strcmp(argv[i] + 1, "w")) {
                        overwrite = 1;
                    }

                    else if (!strcmp(argv[i] + 1, "f")) {
                        shared_only = 1;
                    }

                    break;

                default:
                    multi++;
            }

        }
        
        multi = multi > 1;

        // Library Creation
        for (int i = 1; i < argc; i++) {
            if (i == gcc) break;

            for (int j = 0; j < flags; j++) if (flag_i[j] == i) goto CONTINUE;

            output_path = output_defined ? output_name : (char *)argv[i];

            printf("\033[35m '%s'\033[0m", argv[i]);

            shared_static_lib_input_i += sprintf(shared_static_lib_input + shared_static_lib_input_i, "%.*s%s ",
            (size_t)(strrchr(output_path + 2, multi ? LIBS__os_path_sep : 0)) - (size_t)(output_path) + 1,
            output_path,
            multi ? strrchr(argv[i], LIBS__os_path_sep) + 1 : ".o");
            *(shared_static_lib_input + shared_static_lib_input_i - 2) = 'o';

            shared_lib_input_i += sprintf(shared_lib_input + shared_lib_input_i, "%s ", argv[i]);



            // Static Library
            if (!shared_only) {
                    sprintf(
                    sys_cmd, " \033[45m \033[49;1;33m gcc \033[1;32m%s\033[3;34m \033[0m\033[3m-c -o \033[1;33m%.*s%.*s.o%c"
                    "   \033[22;3;36m%s\033[0m",
                    argv[i],

                    (size_t)(strrchr(output_path + 2, multi ? LIBS__os_path_sep : '.')) - (size_t)(output_path) + 1,
                    output_path,
                    
                    strrchr(strrchr(argv[i], LIBS__os_path_sep) + 1, '.') - (strrchr(argv[i], LIBS__os_path_sep) + 1),
                    multi ? strrchr(argv[i], LIBS__os_path_sep) + 1 : "",
                    
                    gcc ? '\n' : ' ',
                    gcc_string
                );
                
                printf(sys_cmd);
                putchar('\n');
            }
            
            sprintf(
                sys_cmd, "gcc %s -c -o %.*s%.*s.o %s",
                argv[i],
                (size_t)(strrchr(output_path + 2, multi ? LIBS__os_path_sep : '.')) - (size_t)(output_path) + 1,
                output_path,

                strrchr(strrchr(argv[i], LIBS__os_path_sep) + 1, '.') - (strrchr(argv[i], LIBS__os_path_sep) + 1),
                multi ? strrchr(argv[i], LIBS__os_path_sep) + 1 : "",

                gcc_string
            );
            system(sys_cmd);


            // Archiving Static Library
            if (!shared_only) {
                    sprintf(
                    sys_cmd, " \033[45m \033[49;1;33m ar \033[3;34mrcs \033[0m\033[1;33m%.*s%.*s.a \033[32m%.*s%.*s.o\033[0m",
                    (size_t)(strrchr(output_path + 2, multi ? LIBS__os_path_sep : '.')) - (size_t)(output_path) + 1,
                    output_path,

                    strrchr(strrchr(argv[i], LIBS__os_path_sep) + 1, '.') - (strrchr(argv[i], LIBS__os_path_sep) + 1),
                    multi ? strrchr(argv[i], LIBS__os_path_sep) + 1 : "",

                    (size_t)(strrchr(output_path + 2, multi ? LIBS__os_path_sep : '.')) - (size_t)(output_path) + 1,
                    output_path,

                    strrchr(strrchr(argv[i], LIBS__os_path_sep) + 1, '.') - (strrchr(argv[i], LIBS__os_path_sep) + 1),
                    multi ? strrchr(argv[i], LIBS__os_path_sep) + 1 : ""

                );
                printf(sys_cmd);
                putchar('\n');
            }
            
            sprintf(
                sys_cmd, "ar rcs %.*s%.*s.a %.*s%.*s.o",
                (size_t)(strrchr(output_path + 2, multi ? LIBS__os_path_sep : '.')) - (size_t)(output_path) + 1,
                output_path,

                strrchr(strrchr(argv[i], LIBS__os_path_sep) + 1, '.') - (strrchr(argv[i], LIBS__os_path_sep) + 1),
                multi ? strrchr(argv[i], LIBS__os_path_sep) + 1 : "",

                (size_t)(strrchr(output_path + 2, multi ? LIBS__os_path_sep : '.')) - (size_t)(output_path) + 1,
                output_path,

                strrchr(strrchr(argv[i], LIBS__os_path_sep) + 1, '.') - (strrchr(argv[i], LIBS__os_path_sep) + 1),
                multi ? strrchr(argv[i], LIBS__os_path_sep) + 1 : ""

            );
            system(sys_cmd);

            if (!shared_only || !(i % 3)) putchar('\n'); else putchar('\t');

            CONTINUE:
        }
        
        if (shared_only) putchar('\n');
        
        printf("\033[35m Shared Static Library\033[0m\n");
        
        // Shared Static Library
        sprintf(
            sys_cmd, " \033[45m \033[49;1;33m ar \033[3;34mrcs \033[0m\033[1;33m%.*s.a \033[32m%s\033[0m",
            (size_t)(strrchr(output_path + 2, '.')) - (size_t)(output_path),
            output_path,
            shared_static_lib_input
        );
        printf(sys_cmd);
        putchar('\n');

        sprintf(
            sys_cmd, "ar rcs %.*s.a %s",
            (size_t)(strrchr(output_path + 2, '.')) - (size_t)(output_path),
            output_path,
            shared_static_lib_input
        );
        system(sys_cmd);

        
        // Shared Dynamic Library
        
        printf("\033[35m Shared Dynamic Library\033[0m\n");
        sprintf(
            sys_cmd, " \033[45m \033[49;1;33m gcc \033[1;32m%s\n  \033[3;34m" LIBS__os_shared_object_flag "\033[0m\033[3m-o \033[0m\033[1;33m%.*s" LIBS__os_shared_object_filetype "%c  \033[22;3;36m%s\033[0m",
            shared_static_lib_input,
            #ifdef _WIN32
            (size_t)(strrchr(output_path + 2, '.')) - (size_t)(output_path),
            output_path,
            #endif
            (size_t)(strrchr(output_path + 2, '.')) - (size_t)(output_path),
            output_path,
            gcc ? '\n' : ' ',
            gcc_string
        );
        printf(sys_cmd);
        putchar('\n');
        
        sprintf(
            sys_cmd, "gcc %s" LIBS__os_shared_object_flag "-o %.*s" LIBS__os_shared_object_filetype " %s",
            shared_lib_input,
            #ifdef _WIN32
            (size_t)(strrchr(output_path + 2, '.')) - (size_t)(output_path),
            output_path,
            #endif
            (size_t)(strrchr(output_path + 2, '.')) - (size_t)(output_path),
            output_path,
            gcc_string
        );
        system(sys_cmd);

    }

    return 0;
}