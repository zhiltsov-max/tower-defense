#ifndef GAME_ENGINE_GRAPHICS_DEVICE_H
#define GAME_ENGINE_GRAPHICS_DEVICE_H

#include "GameEngine/Infrastructure/check_def.h"


namespace GE {

namespace IO {

class TGraphicsDevice
{
public:
    virtual ~TGraphicsDevice() = default;
};

} // namespace IO

} // namespace GE

#endif // GAME_ENGINE_GRAPHICS_DEVICE_H
