#ifndef GAME_ENGINE_GRAPHICS_DEVICE_H
#define GAME_ENGINE_GRAPHICS_DEVICE_H

#include "SFML/OpenGL.hpp"
#include "SFML/Graphics.hpp"

#include "GameEngine/Utility/common.h"


GE_BEGIN_ENGINE_NAMESPACE

namespace IO {

using TGraphicsDevice = sf::RenderTarget;

} // namespace IO

GE_END_ENGINE_NAMESPACE

#endif // GAME_ENGINE_GRAPHICS_DEVICE_H
