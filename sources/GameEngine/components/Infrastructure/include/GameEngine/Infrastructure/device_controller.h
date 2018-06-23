#ifndef GAME_ENGINE_DEVICE_CONTROLLER_H
#define GAME_ENGINE_DEVICE_CONTROLLER_H

#include <memory>

#include "GameEngine/Utility/common.h"
#include "GameEngine/Infrastructure/graphics_device.h"
#include "GameEngine/Infrastructure/mouse_device.h"
#include "GameEngine/Infrastructure/keyboard_device.h"


GE_BEGIN_ENGINE_NAMESPACE

namespace IO {

class TDeviceController
{
public:
    TDeviceController() = default;
    TDeviceController(const TDeviceController& other) = delete;
    TDeviceController(TDeviceController&& other) = default;
    TDeviceController& operator=(const TDeviceController& other) = delete;
    TDeviceController& operator=(TDeviceController&& other) = default;
    ~TDeviceController() = default;

    void setMouseDevice(TMouseDevice* device);
    void setKeyboardDevice(TKeyboardDevice* device);
    void setGraphicsDevice(TGraphicsDevice* device);

    TMouseDevice const* getMouseDevice() const;
    TMouseDevice* getMouseDevice();

    TKeyboardDevice const* getKeyboardDevice() const;
    TKeyboardDevice* getKeyboardDevice();

    TGraphicsDevice const* getGraphicsDevice() const;
    TGraphicsDevice* getGraphicsDevice();

    using TTime = uint;
    TTime getTime() const;

private:
    using PMouseDevice = std::unique_ptr<TMouseDevice> ;
    PMouseDevice mouseDevice;

    using PKeyboardDevice = std::unique_ptr<TKeyboardDevice>;
    PKeyboardDevice keyboardDevice;

    using PGraphicsDevice = std::unique_ptr<TGraphicsDevice>;
    PGraphicsDevice graphicsDevice;

    using TTimer = sf::Clock;
    TTimer timer;
};

} // namespace IO

GE_END_ENGINE_NAMESPACE

#endif // GAME_ENGINE_DEVICE_CONTROLLER_H
