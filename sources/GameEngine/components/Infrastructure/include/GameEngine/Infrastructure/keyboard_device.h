#ifndef GAME_ENGINE_KEYBOARD_DEVICE_H
#define GAME_ENGINE_KEYBOARD_DEVICE_H

#include "GameEngine/Infrastructure/window.h"
#include "GameEngine/Infrastructure/key_defs.h"


namespace GE {

namespace IO {

class TKeyboardDevice
{
public:
    TKeyboardDevice() = default;
    ~TKeyboardDevice() = default;

    void handleEvent(const TWindowEvent& evt);

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

#endif // GAME_ENGINE_KEYBOARD_DEVICE_H