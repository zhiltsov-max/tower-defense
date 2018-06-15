#include "GameEngine/Application/basic_application.h"


namespace GE {

static TBasicApplication* GetInstance() {
    return dynamic_cast<TBasicApplication*>(AApplication::GetInstance());
}

TBasicApplication::TBasicApplication(const TParameters& info) :
    AApplication(),
    deviceController(),
    window(nullptr),
    debugTools(),
    exitCode(EExitCode::Success),
    isRunning(false)
{
    window = std::make_unique<TWindow>(
        sf::VideoMode(info.window.width, info.window.height),
        info.window.title, info.window.style);
    window->setActive(); // TODO: maybe extract to render() function?

    auto* mouseDevice = new IO::TMouseDevice();
    auto* keyboardDevice = new IO::TKeyboardDevice();
    auto* graphicsDevice = &window;

    deviceController.setMouseDevice(mouseDevice);
    deviceController.setKeyboardDevice(keyboardDevice);
    deviceController.setGraphicsDevice(graphicsDevice);
}

TBasicApplication::~TBasicApplication() {
    if (window != nullptr) {
        window->close();
    }
}

TBasicApplication::TExitCode TBasicApplication::run() {
    isRunning = true;

    while (window->isOpen() && isRunning) {
        TWindowEvent event;
        while (window->pollEvent(event)) {
            handleEvent(event);
        }

        update();
    }

    onExit();

    return static_cast<TExitCode>(exitCode);
}

void TBasicApplication::handleEvent(const TWindowEvent& event) {
    switch (event.type) {
        case EWindowEvent::Closed:
            exit(EExitCode::Success);
            return;

        case EWindowEvent::LostFocus:
            onSuspend();
            break;

        case EWindowEvent::GainedFocus:
            onResume();
            break;

        default:
            deviceController.handleEvent(event);
    }
}

void TBasicApplication::exit(EExitCode exitCode_) {
    exitCode = exitCode_;
    isRunning = false;
}

void TBasicApplication::onSuspend() { /* none */ }

void TBasicApplication::onResume() { /* none */ }

void TBasicApplication::onExit() { /* none */ }

void TBasicApplication::update() {
    /* Example code:
     *
     *  window->clear();
     *  draw();
     *  window->display();
     */
}

const IO::TDeviceController& TBasicApplication::getDeviceController() const {
    return deviceController;
}

IO::TDeviceController& TBasicApplication::getDeviceController() {
    return deviceController;
}

const TDebugTools& TBasicApplication::getDebugTools() const {
    return debugTools;
}

TDebugTools& TBasicApplication::getDebugTools() {
    return debugTools;
}

} // namespace GE