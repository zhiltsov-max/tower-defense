#ifndef GAME_ENGINE_KEYBOARD_DEVICE_H
#define GAME_ENGINE_KEYBOARD_DEVICE_H

#include "GameEngine/Infrastructure/key_defs.h"


namespace GE {

namespace IO {

class TKeyboardDevice
{
public:
    virtual ~TKeyboardDevice() = default;
    virtual void update() = 0;
    virtual const TKeyboardInfo& getInfo() const = 0;
    virtual TKeyboardInfo& getInfo() = 0;
};

} // namespace IO

} // namespace GE

#endif // GAME_ENGINE_KEYBOARD_DEVICE_H