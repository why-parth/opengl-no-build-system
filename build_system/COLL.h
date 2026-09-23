// Date of Creation : 9th Sept, 2025
// Time of Creation : 6:32 AM
/*
"""
This standalone header is being made to replace the use of any external build system.
"""
*/
#ifndef __included__COLL
#define __included__COLL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define COLL__os_path_sep '\\'
#define COLL__os_empty_dir(_path) system("cmd /c if exist \"" _path "\" (rmdir /s /q \"" _path  "\") & mkdir \"" _path "\"")
#define COLL__os_empty_dir_fstr "cmd /c if exist \"%s\" (rmdir /s /q \"%s\") & mkdir \"%s\""
#define COLL__os_copy_file_fstr " copy \"%s\" \"%s\" >nul "
#else
#define COLL__os_path_sep '/'
#define COLL__os_empty_dir(_path) system("rm -rf \"" _path "\"; mkdir \"" _path "\"")
#define COLL__os_empty_dir_fstr "rm -rf \"%s\"; mkdir \"%s\""
#define COLL__os_copy_file_fstr " \\cp -f \"%s\" \"%s\" > /dev/null 2>&1 "
#endif

#define COLL__os_empty_dir_printf_str(_path) COLL__os_empty_dir_fstr, _path, _path, _path
#define COLL__os_copy_file_printf_str(_dest, _source) COLL__os_copy_file_fstr, _source, _dest

#define COLL__merge_tokens_2(a, b) a##b
#define COLL_merge(a, b) COLL__merge_tokens_2(a, b)
#define COLL_name(name, ...) COLL_merge(COLL_, COLL_merge(name, __VA_OPT__(__VA_ARGS__)) )

// Name, Length
#define COLL_NEW_LIST(name, length)         \
char COLL_name(name)[32] = #name;           \
unsigned int COLL_name(name, len) = length; \
unsigned int COLL_name(name, count) = 0;    \
char * COLL_name(name, values)[length]      \

// Push
#define COLL_PUSH_LIST(name) COLL_name(name, values)[COLL_name(name, count)++] = 

// Printing
#define COLL_PRINT_LIST(name)                                                       \
printf( COLL_indent "%s\033[0m\n", COLL_name(name));                                \
for (int i = 0; i < COLL_name(name, count); i++)                                    \
printf(" \033[33m%4d\033[0m '%s'\n", i + 1, COLL_name(name, values)[i])

// Convert List to String
#define COLL_STRING(dest, name, buffer, flag)                                           \
for (                                   \
        char COLL_temp[buffer],         \
        COLL_cmd[buffer] = "",          \
        * first = COLL_cmd,             \
        * COLL_i = 0,                   \
        * COLL_j,                       \
        COLL_cmd_i,                     \
        *COLL_cmd_null                  \
        ;;                              \
    )                                   \
    {                                                                                   \
        COLL_cmd_i = 0;                                                                 \
        COLL_cmd_null = strchr(COLL_cmd, 0);                                            \
        COLL_j = 0;                                                                     \
        \
        for (char _flag[] = flag "%s " ; _flag[(size_t)COLL_j]; COLL_j++)               \
            *((char *)(COLL_cmd_null + (COLL_cmd_i++))) = _flag[(size_t)COLL_j];        \
        *((char *)(COLL_cmd_null + COLL_cmd_i)) = 0;                                    \
        \
        memcpy(COLL_temp, COLL_cmd, buffer);                                            \
        sprintf(COLL_cmd, COLL_temp, COLL_name(name, values)[(size_t)COLL_i]);          \
        \
        if (((size_t)++COLL_i) < COLL_name(name, count)) continue;                      \
        else {                                                                          \
            if (dest) memcpy(dest, COLL_cmd, buffer);                                   \
            else printf("%s", COLL_cmd);                                                \
            break;                                                                      \
        }                                                                               \
    }

/* Iterate over each element in the COLL List and apply any command per each. */
#define COLL_FOREACH(name, ...)                     \
for (                                               \
        char * elem,                                \
        * COLL_i = 0 ;                              \
        ((size_t)COLL_i) < COLL_name(name, count) ; \
        COLL_i++                                    \
    )                                               \
    {                                               \
    size_t index = (size_t) COLL_i;                 \
    elem = COLL_name(name, values)[index];          \
    __VA_ARGS__;                                    \
}

#ifndef COLL_no_implementation

#ifndef static_links
#define static_links    10
#endif

#ifndef dynamic_links
#define dynamic_links   10
#endif

#ifndef linker_searches
#define linker_searches 10
#endif

#ifndef input_files
#define input_files     10
#endif

#ifndef copy_files_count
#define copy_files_count     10
#endif

#ifndef output_name_length
#define output_name_length  128
#endif

#ifndef cmd_length
#define cmd_length      1024
#endif

#if defined(_WIN32)
#define COLL_rpath_handle   " "

#elif defined(__APPLE__)
#define COLL_rpath_handle   " -Wl,-rpath,@executable_path "

#elif defined(__linux__)
#define COLL_rpath_handle   " -Wl,-rpath,'$ORIGIN' "

#endif

#define merge           COLL_merge
#define get(name, ...)  COLL_name(name __VA_OPT__(, __VA_ARGS__))

#define static_linking  COLL_NEW_LIST(Static, static_links)
#define dynamic_linking COLL_NEW_LIST(Dynamic, dynamic_links)
#define linker_search   COLL_NEW_LIST(Searching, linker_searches)
#define compiler_inputs COLL_NEW_LIST(In, input_files)
#define copying_files   COLL_NEW_LIST(Copy, copy_files_count)

#define libc _stdlib = 1

#define link            COLL_PUSH_LIST(Dynamic)
#define static_link     COLL_PUSH_LIST(Static)
#define search          COLL_PUSH_LIST(Searching)
#define in              COLL_PUSH_LIST(In)

#define copy            COLL_PUSH_LIST(Copy)
#define none            "none"
#define paste           COLL_PUSH_LIST(Copy) ":"

#define build            _build_dir = 

#define out _output_name = 

#define run _run_output = 1

#define COLL_indent " \033[45m \033[49;35m "

#define show            COLL_PRINT_LIST(Dynamic)
#define show_static     COLL_PRINT_LIST(Static)
#define show_searches   COLL_PRINT_LIST(Searching)
#define show_in         COLL_PRINT_LIST(In)
#define show_copying    COLL_FOREACH(Copy,                                                          \
    if (elem[0] == ':' && printf(COLL_indent "Copying to '\033[0m%s\033[35m'\033[0m\n", elem + 1))  \
    for (int curr = index; curr != -1; curr--) {                                                    \
        char * curr_str = COLL_name(Copy, values)[curr];                                            \
        if (curr_str[0] == ':' ) { index = curr; continue; }                                        \
        else if (!strcmp(curr_str, "none")) break;                                                  \
        else printf(" \033[33m%4d\033[0m '%s'\n", index - curr, COLL_name(Copy, values)[curr]);     \
    }                                                                                               \
)

#define link_string(...)            COLL_STRING(__VA_OPT__(__VA_ARGS__ +) 0, Dynamic, cmd_length, "-l:")
#define static_link_string(...)     COLL_STRING(__VA_OPT__(__VA_ARGS__ +) 0, Static, cmd_length, "-l:")
#define linker_search_string(...)   COLL_STRING(__VA_OPT__(__VA_ARGS__ +) 0, Searching, cmd_length, "-L")
#define compiler_search_string(...) COLL_STRING(__VA_OPT__(__VA_ARGS__ +) 0, Searching, cmd_length, "-I")
#define input_files_string(...)     COLL_STRING(__VA_OPT__(__VA_ARGS__ +) 0, In, cmd_length, "")
// copy -> sprintf(cmd, COLL__os_copy_file_fstr, elem, _copy_dest); system(cmd)
#define paste_files                 COLL_FOREACH(Copy,                              \
    if (elem[0] == ':' && (_copy_dest = elem + 1))                                  \
    for (int curr = index; curr != -1; curr--) {                                    \
        char * curr_str = COLL_name(Copy, values)[curr];                            \
        if (curr_str[0] == ':') continue;                                           \
        else if (!strcmp(curr_str, "none")) break;                                  \
        else {                                                                      \
            sprintf(cmd, COLL__os_copy_file_fstr, curr_str, _copy_dest);            \
            system(cmd);                                                            \
        }                                                                           \
    }                                                                               \
)

#define config                                          \
compiler_inputs;                                        \
linker_search;                                          \
static_linking;                                         \
dynamic_linking;                                        \
copying_files;                                          \
char * _output_name = NULL;                             \
char _output_fullname[cmd_length];                      \
int _run_output = 0;                                    \
int _stdlib = 0;                                        \
char * _build_dir = NULL;                               \
char * _copy_dest = NULL;                               \
char cmd[cmd_length];                                   \
void __config__(void);                                  \
int main (void) {                                       \
    __config__();                                       \
    \
    char c_cmd[] = "gcc %s %s -o %s "                   \
    "-L. -I. %s %s %s %s";                              \
    char c_cmdf[10 + 7 * cmd_length];                   \
    char c_cmdf_colored[10 + 3 * cmd_length];           \
    unsigned int c_cmdf_colored_i = 0;                  \
    unsigned int c_cmdf_color = 0;                      \
    \
    int _inputs = COLL_name(In, count);                 \
    int _search = COLL_name(Searching, count);          \
    int _static = COLL_name(Static, count);             \
    int _dynamic = COLL_name(Dynamic, count);           \
    \
    char _inputs_string[cmd_length];                    \
    char _search_string[cmd_length];                    \
    char _compiler_string[cmd_length];                  \
    char _static_string[cmd_length];                    \
    char _dynamic_string[cmd_length];                   \
    char _build_dir_cmd[cmd_length];                    \
    \
    printf("\033[33mConfiguration \n\033[0m");          \
    \
    if (_inputs) {                                                                                                                      \
    show_in;                                                                                                                            \
    input_files_string(_inputs_string);                                                                                                 \
    c_cmdf_colored_i += sprintf(c_cmdf_colored + c_cmdf_colored_i, "\033[1;32m%s", _inputs_string);                                     \
    }                                                                                                                                   \
    else { printf("\033[1;31m\nError : No Input Files!\n\033[0m"); return -1; }                                                         \
    \
    c_cmdf_colored_i += sprintf(c_cmdf_colored + c_cmdf_colored_i, "\n   \033[1;3;31m%s\033[0m ", _stdlib ? "" : "-nostdlib");         \
    \
    sprintf(_output_fullname, "%s%c%s", _build_dir ? _build_dir : ".", COLL__os_path_sep, _output_name);\
    \
    c_cmdf_colored_i += sprintf(                                                                                                        \
        c_cmdf_colored + c_cmdf_colored_i, "\033[22;3;39m-o\033[0m \033[1;33m'%s'\033[0m", _output_fullname                             \
    );                                                                                                                                  \
    \
    c_cmdf_colored_i += sprintf(c_cmdf_colored + c_cmdf_colored_i, "\033[22;3;39m%s\033[0m", COLL_rpath_handle);                        \
    \
    c_cmdf_colored_i += sprintf(c_cmdf_colored + c_cmdf_colored_i, "\033[1;34m-L. \033[1;36m-I.\033[0m ");                             \
    if (_search) {                                                                                                                      \
    show_searches;                                                                                                                      \
    linker_search_string(_search_string);                                                                                               \
    c_cmdf_colored_i += sprintf(c_cmdf_colored + c_cmdf_colored_i, "\n   \033[3%dm%s", 4 + 2 * ((c_cmdf_color++)%2), _search_string);   \
    compiler_search_string(_compiler_string);                                                                                           \
    c_cmdf_colored_i += sprintf(c_cmdf_colored + c_cmdf_colored_i, "\n   \033[3%dm%s", 4 + 2 * ((c_cmdf_color++)%2), _compiler_string); \
    }                                                                                                                                   \
    \
    if (_static) {                                                                                                                      \
    show_static;                                                                                                                        \
    static_link_string(_static_string);                                                                                                 \
    c_cmdf_colored_i += sprintf(c_cmdf_colored + c_cmdf_colored_i, "\n   \033[3%dm%s", 4 + 2 * ((c_cmdf_color++)%2), _static_string);   \
    }                                                                                                                                   \
    \
    if (_dynamic) {                                                                                                                     \
    /* For Log */                                                                                                                       \
    show;                                                                                                                               \
    /* For system() */                                                                                                                  \
    link_string(_dynamic_string);                                                                                                       \
    /* For Debugging */                                                                                                                 \
    c_cmdf_colored_i += sprintf(c_cmdf_colored + c_cmdf_colored_i, "\n   \033[3%dm%s", 4 + 2 * ((c_cmdf_color++)%2), _dynamic_string);  \
    }                                                                                                                                   \
    \
    if (_output_name) { printf( COLL_indent "Out\033[0m\n    \033[33m:\033[0m '%s'\n", _output_name); }                                 \
    else { printf("\033[1;31m\nError : No Out Defined!\n\033[0m"); return -1; }                                                         \
    \
    if (_build_dir) {                                                                                                                   \
        printf( COLL_indent "Build At\n");                                                                                              \
        printf("\033[33m    :\033[0m '%s'\n", _build_dir);                                                                              \
        sprintf(_build_dir_cmd, COLL__os_empty_dir_printf_str(_build_dir));                                                             \
        system(_build_dir_cmd);                                                                                                         \
    }                                                                                                                                   \
    \
    show_copying;                                   \
    paste_files;                                    \
    \
    sprintf(c_cmdf, c_cmd,                          \
        _inputs ? _inputs_string : "",              \
        _stdlib ? "" : "-nostdlib ",                \
        _output_fullname,                           \
        _search ? _compiler_string : "",            \
        _search ? _search_string : "",              \
        _static ? _static_string : "",              \
        _dynamic ? _dynamic_string : ""             \
    );                                              \
    \
    printf("\033[33m\nCompilation %s\033[0m\n", _run_output ? "&& Run" : "");   \
    printf(COLL_indent);                                                        \
    printf("%s\033[0m", c_cmdf_colored);                                        \
    putchar('\n');                                                              \
    \
    if ((!system(c_cmdf)) && _run_output) {                                     \
        sprintf(c_cmdf, "%s",  _output_fullname);                               \
        printf( COLL_indent "\033[1;33m%s\033[0m\n", c_cmdf);                   \
        system(c_cmdf);                                                         \
    };                                                                          \
    return 0;                                                                   \
};                                                                              \
void __config__(void)  

#endif
#endif


/*
The goal of this header is to make an interface that makes it possible to keep track of what libraries to link statically and dynmaically.
6:56 AM of 9/13/2026, the build system is fully completed, I just have to standardise it. Before that, I have to add the -rpath flag for POSIX, use a buffer flushing system to draw the final command, and then link stdlib and set that as the smoke test of this build system.
*/