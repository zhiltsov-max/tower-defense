#include "backend/sfml/mouse_device.h"


namespace GE {

namespace IO {

void TSFMLMouse::update() {
    /*none*/
}

const TMouseInfo& TSFMLMouse::getInfo() const {
    return info;
}

TMouseInfo& TSFMLMouse::getInfo() {
    return info;
}

void TSFMLMouse::handleEvent(const sf::Event& evt) {
    switch (evt.type) {
    case sf::Event::MouseButtonPressed:
        {
            const auto key = (KeyCode)evt.mouseButton.button;
            if (isPressed(key) == false) {
                pressKey(key, evt.mouseButton.x, evt.mouseButton.y);
            }
            break;
        }

    case sf::Event::MouseButtonReleased:
        {
            const auto key = (KeyCode)evt.mouseButton.button;
            if (isPressed(key) == true) {
                releaseKey(key);
            }
            break;
        }

    case sf::Event::MouseMoved:
        {
            const auto xPos = evt.mouseMove.x;
            const auto yPos = evt.mouseMove.y;
            info.speed[0] = xPos - info.axis[0];
            info.speed[1] = yPos - info.axis[1];
            info.axis[0] = xPos;
            info.axis[1] = yPos;
            if (info.speed[0]) { info.events.emplace(EventId::MouseXmove, info.speed[0]); }
            if (info.speed[1]) { info.events.emplace(EventId::MouseYmove, info.speed[1]); }
            break;
        }

    case sf::Event::MouseWheelMoved:
        {
            info.speed[2] = evt.mouseWheel.delta;
            if (info.speed[2]) {
                info.axis[2] += info.speed[2];
                info.events.emplace(EventId::MouseZmove, info.speed[2]);
            }
            break;
        }

    default: {/*none*/}
    }
}

bool TSFMLMouse::isPressed(KeyCode code) const {
    return info.keyState[code] == KeyState::Pressed;
}
void TSFMLMouse::releaseKey(KeyCode code) {
    info.keyState[code] = KeyState::Released;
    info.events.emplace(EventId::MouseUp, code);
}
void TSFMLMouse::pressKey(KeyCode code, int x, int y) {
    info.keyState[code] = KeyState::Hit;
    info.events.emplace(EventId::MouseDown, code);
    info.events.back().mouseDown.x = x;
    info.events.back().mouseDown.y = y;
}

} // namespace IO

} // namespace GE