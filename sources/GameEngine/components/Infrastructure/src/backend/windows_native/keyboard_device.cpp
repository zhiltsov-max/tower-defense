#include "backend/windows_native/keyboard_device.h"


namespace GE {

namespace IO {

TWinMessageKeyboard::TWinMessageKeyboard() {
    for (size_t i = 0; i != (short)KeyboardKey::_count; ++i) {
        keyCode[i] = MapVirtualKey(i, 0);
    }
}

void TWinMessageKeyboard::attach(HWND hwnd) {
    wndHandle = hwnd;
}

void TWinMessageKeyboard::detach() { /*none*/ }

void TWinMessageKeyboard::update() {
    MSG message; /* wParam == virtualCode */

    while (PeekMessage(&message, wndHandle, WM_KEYFIRST, WM_KEYLAST, PM_REMOVE) && info.events.size() < info.MAX_QUEUE_SIZE) {
        TranslateMessage(&message);
        const auto key = convert(message.wParam);

        switch (message.message) {
        case WM_KEYDOWN:
            if (isPressed(key) == false) {
                pressKey(key);
            }
            break;

        case WM_KEYUP:
            if (isPressed(key) == true) {
                releaseKey(key);
            }
            break;

        default: {/*none*/}
        };

        DispatchMessage(&message);
    }
}

const TKeyboardInfo& TWinMessageKeyboard::getInfo() const {
    return info;
}

TKeyboardInfo& TWinMessageKeyboard::getInfo() {
    return info;
}

bool TWinMessageKeyboard::isPressed(KeyCode code) const {
    return info.keyState[code] == KeyState::Pressed;
}
void TWinMessageKeyboard::releaseKey(KeyCode code) {
    info.keyState[code] = KeyState::Released;
    info.events.emplace(EventId::KeyUp, code);
}
void TWinMessageKeyboard::pressKey(KeyCode code) {
    info.keyState[code] = KeyState::Hit;
    info.events.emplace(EventId::KeyDown, code);
}

} // namespace IO

} // namespace GE