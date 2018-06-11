#ifndef GAME_ENGINE_WINDOWS_MOUSE_H
#define GAME_ENGINE_WINDOWS_MOUSE_H

#include <windows.h>

#include "GameEngine/Infrastructure/mouse.h"


namespace GE {

namespace IO {

class TWinMessageMouse : public TMouseDevice
{
public:
    TWinMessageMouse() = default;
    ~TWinMessageMouse() = default;

    void attach(HWND hwnd);
    void detach();

    void update();
    const TMouseInfo& getInfo() const;
    TMouseInfo& getInfo();

private:
    TMouseInfo info;
    HWND wndHandle;

    typedef unsigned char KeyCode;
    bool isPressed(KeyCode code) const;
    void releaseKey(KeyCode code);
    void pressKey(KeyCode code);
};

} // namspace IO

} // namespace GE

#endif // GAME_ENGINE_WINDOWS_MOUSE_H