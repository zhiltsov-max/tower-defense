#ifndef GAME_ENGINE_SFML_KEYBOARD_DEVICE_H
#define GAME_ENGINE_SFML_KEYBOARD_DEVICE_H

#include "SFML/Window.hpp"

#include "GameEngine/Infrastructure/keyboard_device.h"


namespace GE {

namespace IO {

class TSFMLKeyboard : public TKeyboardDevice
{
public:
    TSFMLKeyboard() = default;
    ~TSFMLKeyboard() = default;

    void update();
    void handleEvent(const sf::Event& evt);

    const TKeyboardInfo& getInfo() const;
    TKeyboardInfo& getInfo();
private:
    TKeyboardInfo info;

    typedef unsigned char KeyCode;
    bool isPressed(KeyCode code) const;
    void releaseKey(KeyCode code);
    void pressKey(KeyCode code);
};

} // namespace IO

} // namespace GE

#endif // GAME_ENGINE_SFML_KEYBOARD_DEVICE_H