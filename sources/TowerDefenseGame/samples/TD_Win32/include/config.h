#ifndef CONFIG_H
#define CONFIG_H

#if defined(WINDOWS)
    #if defined(SFML)
        #error Multiple target OS selected.
    #endif

    #if defined(WINDOWS_DIRECTINPUT) && defined(WINDOWS_SYSINPUT)
        #error Multiple input methods selected.
    #endif

#elif defined(SFML)
    #if defined(WINDOWS)
        #error Multiple target OS selected.
    #endif
#else
    #error Unsupported target OS selected or target OS was not specified.
#endif

#if !defined(SFML)
    #error Only SFML supported.
#endif

#endif // CONFIG_H
