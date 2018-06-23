#ifndef GAME_ENGINE_WINDOW_H
#define GAME_ENGINE_WINDOW_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include "GameEngine/Utility/common.h"


GE_BEGIN_ENGINE_NAMESPACE

namespace IO {

using TWindowEvent = sf::Event;
using EWindowEvent = sf::Event::EventType;
using TWindow = sf::RenderWindow;

} // namespace IO

GE_END_ENGINE_NAMESPACE

#endif // GAME_ENGINE_WINDOW_H