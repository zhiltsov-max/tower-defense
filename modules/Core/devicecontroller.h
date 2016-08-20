#ifndef CORE_DEVICECONTROLLER_H
#define CORE_DEVICECONTROLLER_H

#include <memory>
#include "io.h"
#include "graphicsdevice.h"


namespace IO {

class TDeviceController
{
public:
    TDeviceController() = default;
    TDeviceController(const TDeviceController& other) = delete;
    TDeviceController& operator=(const TDeviceController& other) = delete;
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

    void update();

private:
    typedef std::unique_ptr<TMouseDevice> Mouse;
    Mouse mouseDevice;

    typedef std::unique_ptr<TKeyboardDevice> Keyboard;
    Keyboard keyboardDevice;

    typedef std::unique_ptr<TGraphicsDevice> Graphics;
    Graphics graphicsDevice;
};

} // namespace IO

#endif // CORE_DEVICECONTROLLER_H
