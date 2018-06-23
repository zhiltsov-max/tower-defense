#include "GameEngine/Infrastructure/device_controller.h"


GE_BEGIN_ENGINE_NAMESPACE

namespace IO {

void TDeviceController::setKeyboardDevice(TKeyboardDevice* device) {
    keyboardDevice.reset(device);
}

void TDeviceController::setMouseDevice(TMouseDevice* device) {
    mouseDevice.reset(device);
}

void TDeviceController::setGraphicsDevice(TGraphicsDevice* device) {
    graphicsDevice.reset(device);
}

TMouseDevice const* TDeviceController::getMouseDevice() const {
    return mouseDevice.get();
}
TMouseDevice* TDeviceController::getMouseDevice() {
    return mouseDevice.get();
}

TKeyboardDevice const* TDeviceController::getKeyboardDevice() const {
     return keyboardDevice.get();
}
TKeyboardDevice* TDeviceController::getKeyboardDevice() {
    return keyboardDevice.get();
}

TGraphicsDevice const* TDeviceController::getGraphicsDevice() const {
     return graphicsDevice.get();
}
TGraphicsDevice* TDeviceController::getGraphicsDevice() {
    return graphicsDevice.get();
}

TDeviceController::Time TDeviceController::getTime() const {
    return timer.getElapsedTime().asMilliseconds();
}

} // namespace IO

GE_END_ENGINE_NAMESPACE