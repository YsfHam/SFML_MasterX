#pragma once
#if defined(__APPLE__)
    #ifndef MASTER_MACOSX
        #define MASTER_MACOSX
    #endif
#elif defined(_WIN32)
    #ifndef MASTER_WINDOWS
        #define MASTER_WINDOWS
    #endif
    #ifdef _MCS_VER
        #ifndef MASTER_VS_COMPILER
            #define MASTER_VS_COMPILER
        #endif
    #endif
#elif defined(__linux__)
    #ifndef MASTER_LINUX
        #define MASTER_LINUX
    #endif
#else
    #error "Unsuported platform"
#endif