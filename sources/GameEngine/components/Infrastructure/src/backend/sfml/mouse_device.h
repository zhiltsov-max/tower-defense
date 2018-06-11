#ifndef GAME_ENGINE_SFML_MOUSE_DEVICE_H
#define GAME_ENGINE_SFML_MOUSE_DEVICE_H

#include "SFML/Window.hpp"

#include "GameEngine/Infrastructure/mouse_device.h"


namespace GE {

namespace IO {

class TSFMLMouse : public TMouseDevice
{
public:
    TSFMLMouse() = default;
    ~TSFMLMouse() = default;

    void update();
    void handleEvent(const sf::Event& evt);
    const TMouseInfo& getInfo() const;
    TMouseInfo& getInfo();
private:
    TMouseInfo info;

    typedef unsigned char KeyCode;
    bool isPressed(KeyCode code) const;
    void releaseKey(KeyCode code);
    void pressKey(KeyCode code, int x, int y);
};

} // namespace IO

} // namespace GE

#endif // GAME_ENGINE_SFML_MOUSE_DEVICE_H