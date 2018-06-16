#ifndef GAME_ENGINE_STRING_H
#define GAME_ENGINE_STRING_H

#include "SFML/System/String.hpp"


namespace GE {

using TString = std::string; // simple string for internal use
using TTextString = sf::String; // Unicode string for text and user interaction

} // namespace GE

#endif // GAME_ENGINE_STRING_H