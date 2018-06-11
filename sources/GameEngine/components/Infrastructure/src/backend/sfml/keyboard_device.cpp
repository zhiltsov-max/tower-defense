#include "backend/sfml/keyboard_device.h"


namespace GE {

namespace IO {

void TSFMLKeyboard::update() {
    /*none*/
}

void TSFMLKeyboard::handleEvent(const sf::Event& evt) {
    switch (evt.type) {
    case sf::Event::KeyPressed:
        {
            const KeyCode key = static_cast<KeyCode>(evt.key.code);
            if (isPressed(key) == false) {
                pressKey(key);
            }
            break;
        }

    case sf::Event::KeyReleased:
        {
            const KeyCode key = static_cast<KeyCode>(evt.key.code);
            if (isPressed(key) == true) {
                releaseKey(key);
            }
            break;
        }

    default: {/*none*/}
    };
}

const TKeyboardInfo& TSFMLKeyboard::getInfo() const {
    return info;
}

TKeyboardInfo& TSFMLKeyboard::getInfo() {
    return info;
}

bool TSFMLKeyboard::isPressed(KeyCode code) const {
    return info.keyState[code] == KeyState::Pressed;
}
void TSFMLKeyboard::releaseKey(KeyCode code) {
    info.keyState[code] = KeyState::Released;
    info.events.emplace(EventId::KeyUp, code);
}
void TSFMLKeyboard::pressKey(KeyCode code) {
    info.keyState[code] = KeyState::Hit;
    info.events.emplace(EventId::KeyDown, code);
}

} // namespace IO

} // namespace GE