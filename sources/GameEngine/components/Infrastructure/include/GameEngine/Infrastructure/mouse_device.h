#ifndef GAME_ENGINE_MOUSE_DEVICE_H
#define GAME_ENGINE_MOUSE_DEVICE_H

#include "GameEngine/Infrastructure/window.h"
#include "GameEngine/Infrastructure/key_defs.h"


namespace GE {

namespace IO {

class TMouseDevice
{
public:
    TMouseDevice() = default;
    ~TMouseDevice() = default;

    void handleEvent(const TWindowEvent& evt);
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

#endif // GAME_ENGINE_MOUSE_DEVICE_H