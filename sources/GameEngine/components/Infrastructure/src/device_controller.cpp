#include "GameEngine/Infrastructure/device_controller.h"


namespace GE {

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

void TDeviceController::update() {
    if (keyboardDevice != nullptr) {
        keyboardDevice->update();
    }
    if (mouseDevice != nullptr) {
        mouseDevice->update();
    }
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

} // namespace IO

} // namespace GE