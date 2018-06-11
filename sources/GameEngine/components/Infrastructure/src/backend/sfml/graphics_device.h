#ifndef GAME_ENGINE_SFML_GRAPHICS_DEVICE_H
#define GAME_ENGINE_SFML_GRAPHICS_DEVICE_H

#include "SFML/OpenGL.hpp"
#include "SFML/Graphics.hpp"

#include "GameEngine/Infrastructure/graphics_device.h"


namespace GE {

namespace IO {

class TSFMLGraphicsDevice : public TGraphicsDevice
{
public:
    TSFMLGraphicsDevice(sf::RenderTarget* target = nullptr);
    ~TSFMLGraphicsDevice() = default;

    const sf::RenderTarget* get() const;
    sf::RenderTarget* get();
    const sf::RenderTarget& operator*() const;
    sf::RenderTarget& operator*();
    const sf::RenderTarget* operator->() const;
    sf::RenderTarget* operator->();

private:
    typedef sf::RenderTarget* TargetRef;
    TargetRef target;
};

} // namespace IO

} // namespace GE

#endif // GAME_ENGINE_SFML_GRAPHICS_DEVICE_H