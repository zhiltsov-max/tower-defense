#ifndef GAME_ENGINE_MOUSE_DEVICE_H
#define GAME_ENGINE_MOUSE_DEVICE_H

#include "GameEngine/Infrastructure/key_defs.h"


namespace GE {

namespace IO {

class TMouseDevice
{
public:
    virtual ~TMouseDevice() = default;
    virtual void update() = 0;
    virtual const TMouseInfo& getInfo() const = 0;
    virtual TMouseInfo& getInfo() = 0;
};

} // namespace IO

} // namespace GE

#endif // GAME_ENGINE_MOUSE_DEVICE_H