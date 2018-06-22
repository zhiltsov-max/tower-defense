#ifndef GAME_ENGINE_STRING_H
#define GAME_ENGINE_STRING_H

#include <string>

#include "SFML/System/Utf.hpp"


/*
 * The standard string and char* buffers
 * are considered to be in UTF-8 encoding.
 *
 * - For Linux platforms this is the default. No additional actions needed.
 *
 * - For Windows platform additional conversions are performed near API calls.
 *     The UNICODE and _UNICODE defines are expected to prevent wrong ANSI API
 *     calls with UTF-8 strings. Every OS call is preceeded by a conversion
 *     to UTF-16 ("wide" in Windows-world) encoding.
 *
 * References:
 * - http://www.unicode.org/versions/Unicode5.0.0/ - Unicode 5.0 standard
 * - https://utf8everywhere.org - Unicode usage in C++ applications
 * - http://www.cl.cam.ac.uk/~mgk25/unicode.html - Unicode usage in UNIX
 */

#if !defined(UNICODE) || ! defined(_UNICODE)
    #error Unicode defines have to be set for the project.
#endif

namespace GE {

using TUtf8String = std::string;
using TString = TUtf8String;

} // namespace GE

#endif // GAME_ENGINE_STRING_H