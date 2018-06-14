#ifndef GAME_ENGINE_WINDOW_H
#define GAME_ENGINE_WINDOW_H

#include "SFML/Window.hpp"


namespace GE {

namespace IO {

using TWindowEvent = sf::Event;
using EWindowEvent = sf::Event::EventType;
using TWindow = sf::Window;

} // namespace IO

} // namespace GE

#endif // GAME_ENGINE_WINDOW_H