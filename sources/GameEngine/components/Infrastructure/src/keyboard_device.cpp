#include "GameEngine/Infrastructure/window.h"
#include "GameEngine/Infrastructure/key_defs.h"
#include "GameEngine/Infrastructure/keyboard_device.h"


GE_BEGIN_ENGINE_NAMESPACE

namespace IO {

void TKeyboardDevice::handleEvent(const TWindowEvent& evt) {
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

    default: { /* none */ }
    };
}

const TKeyboardInfo& TKeyboardDevice::getInfo() const {
    return info;
}

TKeyboardInfo& TKeyboardDevice::getInfo() {
    return info;
}

bool TKeyboardDevice::isPressed(KeyCode code) const {
    return info.keyState[code] == KeyState::Pressed;
}

void TKeyboardDevice::releaseKey(KeyCode code) {
    info.keyState[code] = KeyState::Released;
    info.events.emplace(EventId::KeyUp, code);
}

void TKeyboardDevice::pressKey(KeyCode code) {
    info.keyState[code] = KeyState::Hit;
    info.events.emplace(EventId::KeyDown, code);
}

} // namespace IO

GE_END_ENGINE_NAMESPACE