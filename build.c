// clear ; gcc .\build.c -o build; if ($?) {.\build}

#include "build_system/COLL.h"

config {

    C++;
    libc;
    build ".\\build";

    /* Linking GLFW */
    static_link ".\\library\\glfw\\libglfw3dll.a";
    static_link ".\\library\\ft\\libft.dll.a";

    /* Search Directories */
    search ".\\include\\ft";
    
    /* Copy and Paste */
    copy ".\\library\\glfw\\glfw3.dll";
    copy ".\\library\\ft\\libft.dll";
    copy ".\\source\\shader.vertex.glsl";
    copy ".\\source\\shader.fragment.glsl";
    copy ".\\source\\text.vertex.glsl";
    copy ".\\source\\text.fragment.glsl";
    copy ".\\textures\\Bricks\\Bricks_Color.jpg";
    copy ".\\textures\\Wood\\Wood_Color.jpg";
    copy ".\\fonts\\Arial.ttf";
    copy ".\\fonts\\EBGaramond.ttf";
    copy ".\\fonts\\Montserrat.ttf";
    paste ".\\build";
    
    /* Input Files */
    in ".\\source\\main.cpp";
    in ".\\source\\gl.c";
    in ".\\source\\window.cpp";
    in ".\\source\\shader.cpp";
    in ".\\source\\buffer.cpp";

    /* Output Name */
    out "run";

    /* Run */
    run;

}

