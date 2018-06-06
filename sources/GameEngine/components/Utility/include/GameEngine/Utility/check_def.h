#ifndef CHECKDEF_H
#define CHECKDEF_H

#if defined(WINDOWS) && defined(SFML)
    #error Multiple target OS selected.
#endif

#if defined(WINDOWS)
    #if defined(WINDOWS_DIRECTINPUT) && defined(WINDOWS_SYSINPUT)
        #error Multiple input methods selected.
    #endif

#elif defined(SFML)
    //none

#else
    #error Unsupported target OS selected or target OS was not specified.
#endif

#endif // CHECKDEF_H
