#ifndef CORE_IMAGE_H
#define CORE_IMAGE_H

#include "checkdef.h"
#if defined(WINDOWS)
    #error Not implemented yet.
#endif //WINDOWS

#if defined(SFML)
    #include "SFML/Graphics.hpp"
    #include "SFML/OpenGL.hpp"
#endif //SFML

#include "point.h"


namespace Graphics {

using TImage = sf::Image;
using TTexture = sf::Texture;
using TSprite = sf::Sprite;

} // namespace Graphics

#endif // CORE_IMAGE_H
