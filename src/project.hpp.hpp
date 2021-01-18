/*
This header contains info used in all parts of the program about the build
*/

#cmakedefine USE_ANSI
#cmakedefine DEBUG
#cmakedefine POSIX

#define VERSION_MAJOR @VERSION_MAJOR@
#define VERSION_MINOR @VERSION_MINOR@
#define VERSION "@VERSION_MAJOR@.@VERSION_MINOR@"

#include "ansi.hpp"
#include <iostream> // printf

#define NAME Color_Yellow "markdown-table:" Color_Reset

#ifdef DEBUG
    #define printf_debug(...) std::fprintf(stderr, Color_Green "DEBUG:" Color_Reset __VA_ARGS__)
#else
    #define printf_debug(...)
#endif // DEBUG


#define printf_error(...) std::fprintf(stderr, NAME Color_Red " error" Color_Reset " - " __VA_ARGS__)
#define printf_warn(...) std::fprintf(stderr, NAME Color_Purple " warning" Color_Reset " - " __VA_ARGS__)

