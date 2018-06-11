#ifndef GAME_ENGINE_WINDOWS_KEYBOARD_H
#define GAME_ENGINE_WINDOWS_KEYBOARD_H

#include <windows.h>

#include "GameEngine/Infrastructure/keyboard.h"


namespace GE {

namespace IO {

class TWinMessageKeyboard : public TKeyboardDevice
{
public:
    TWinMessageKeyboard();
    ~TWinMessageKeyboard() = default;

    void attach(HWND hwnd);
    void detach();

    void update();
    const TKeyboardInfo& getInfo() const;
    TKeyboardInfo& getInfo();

private:
    TKeyboardInfo info;

    HWND wndHandle;
    char keyCode[(short)KeyboardKey::_count];   //remapping VirtualCode -> ScanCode

    typedef unsigned char KeyCode;
    inline KeyCode convert(KeyCode code) const {
        return keyCode[code];
    }
    bool isPressed(KeyCode code) const;
    void releaseKey(KeyCode code);
    void pressKey(KeyCode code);
};

} // namspace IO

} // namespace GE

#endif // GAME_ENGINE_WINDOWS_KEYBOARD_H