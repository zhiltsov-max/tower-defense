#ifndef GAME_ENGINE_MOUSE_DEVICE_H
#define GAME_ENGINE_MOUSE_DEVICE_H

#include "GameEngine/Utility/common.h"
#include "GameEngine/Infrastructure/window.h"
#include "GameEngine/Infrastructure/key_defs.h"


GE_BEGIN_ENGINE_NAMESPACE

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

GE_END_ENGINE_NAMESPACE

#endif // GAME_ENGINE_MOUSE_DEVICE_H