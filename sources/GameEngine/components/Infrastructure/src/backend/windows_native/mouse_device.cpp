#include "backend/windows_native/mouse_device.h"


namespace GE {

namespace IO {

void TWinMessageMouse::attach(HWND hwnd) {
    wndHandle = hwnd;
}

void TWinMessageMouse::detach() { /*none*/ }

void TWinMessageMouse::update() {
    MSG message; /* wParam == flags, lParam == position[y, x] */

    while (PeekMessage(&message, wndHandle, WM_MOUSEFIRST, WM_MOUSELAST, PM_REMOVE) && info.events.size() < info.MAX_QUEUE_SIZE) {
        TranslateMessage(&message);

        switch (message.message) {
        case WM_LBUTTONDOWN:
            const KeyCode key = (KeyCode)MouseKey::Left;
            if (isPressed(key) == false) {
                pressKey(key);
            }
            break;

        case WM_LBUTTONUP:
            const KeyCode key = (KeyCode)MouseKey::Left;
            if (isPressed(key) == true) {
                releaseKey(key);
            }
            break;

        case WM_RBUTTONDOWN:
            const KeyCode key = (KeyCode)MouseKey::Right;
            if (isPressed(key) == false) {
                pressKey(key);
            }
            break;

        case WM_RBUTTONUP:
            const KeyCode key = (KeyCode)MouseKey::Right;
            if (isPressed(key) == true) {
                releaseKey(key);
            }
            break;

        case WM_MBUTTONDOWN:
            const KeyCode key = (KeyCode)MouseKey::Middle;
            if (isPressed(key) == false) {
                pressKey(key);
            }
            break;

        case WM_MBUTTONUP:
            const KeyCode key = (KeyCode)MouseKey::Middle;
            if (isPressed(key) == true) {
                releaseKey(key);
            }
            break;

        case WM_MOUSEMOVE:
            const auto xPos = GET_X_LPARAM(message.lParam);
            const auto yPos = GET_Y_LPARAM(message.lParam);
            info.speed[0] = xPos - info.axis[0];
            info.speed[1] = yPos - info.axis[1];
            info.axis[0] = xPos;
            info.axis[1] = yPos;
            if (info.speed[0]) { info.events.emplace(EventId::MouseXmove, info.speed[0]); }
            if (info.speed[1]) { info.events.emplace(EventId::MouseYmove, info.speed[1]); }
            break;

        case WM_MOUSEWHEEL:
            info.speed[2] = GET_WHEEL_DELTA_WPARAM(message.wParam);
            if (info.speed[2]) {
                info.axis[2] += info.speed[2];
                info.events.emplace(EventId::MouseZmove, info.speed[2]);
            }
            break;

        default: {/*none*/}
        };

        DispatchMessage(&message);
    }
}

const TMouseInfo& TWinMessageMouse::getInfo() const {
    return info;
}

TMouseInfo& TWinMessageMouse::getInfo() {
    return info;
}

bool TWinMessageMouse::isPressed(KeyCode code) const {
    return info.keyState[code] == KeyState::Pressed;
}
void TWinMessageMouse::releaseKey(KeyCode code) {
    info.keyState[code] = KeyState::Released;
    info.events.emplace(EventId::MouseUp, code);
}
void TWinMessageMouse::pressKey(KeyCode code) {
    info.keyState[code] = KeyState::Hit;
    info.events.emplace(EventId::MouseDown, code);
}

} // namespace IO

} // namespace GE