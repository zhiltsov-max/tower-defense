#ifndef GAME_ENGINE_STRING_H
#define GAME_ENGINE_STRING_H

#include <string>

#include "SFML/System/Utf.hpp"


/*
 * The standard string and char* buffers
 * are considered to be in utf-8 encoding.
 *
 * - For Linux platforms this is the default. No additional actions needed.
 *
 * - For Windows platform additional conversions are performed near API calls.
 *     The UNICODE and _UNICODE defines are expected to prevent wrong ANSI API
 *     calls with UTF-8 strings. Every OS call is preceeded by a conversion
 *     to UTF-16 ("wide" in Windows-world) encoding.
 *
 * See https://utf8everywhere.org for additional
 * recommendations and information.
 */

#if !defined(UNICODE) || ! defined(_UNICODE)
    #error Unicode defines have to be set for the project.
#endif

namespace GE {

using TString = std::string;

} // namespace GE

#endif // GAME_ENGINE_STRING_H