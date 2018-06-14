#include "GameEngine/Application/application.h"


namespace GE {

TApplication::PApplication TApplication::instance{};

TApplication& TApplication::GetInstance() {
    ASSERT(instance != nullptr, "Application does not exist.")

    return *instance;
}

TApplication::TApplication(const TApplicationInfo& info) :
    window(nullptr),
    debugTools(),
    exitCode(EExitCode::Success),
    isRunning(false)
{
    ASSERT(instance == nullptr, "Can not create multiple instances of Application.")

    initialize(info);
}

TApplication::~TApplication() {
    if (window != nullptr) {
        window->close();
    }
}


int TApplication::run() {
    isRunning = true;

    while (window->isOpen() && isRunning) {
        TWindowEvent event;
        while (window->pollEvent(event)) {
            handleEvent(event);
        }

        update();
    }

    onExit();

    return exitCode;
}

void TApplication::handleEvent(const TWindowEvent& event) {
    switch (event.type) {
        case EWindowEvent::Closed:
            isRunning = false;
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

void TApplication::exit(EExitCode exitCode_) {
    // TODO: implementation
    exitCode = exitCode_;
}


const IO::TDeviceController& TApplication::getDeviceController() const {
    return deviceController;
}

IO::TDeviceController& TApplication::getDeviceController() {
    return deviceController;
}

void TApplication::initialize(const TApplicationInfo& info) {
    window = std::make_unique<TWindow>(
        sf::VideoMode(info.windowWidth, info.windowHeight),
        info.appTitle, info.style, info.context);
    window->setActive();

    auto* mouseDevice = new IO::TMouseDevice();
    auto* keyboardDevice = new IO::TKeyboardDevice();
    auto* graphicsDevice = &window;

    deviceController.setMouseDevice(mouseDevice);
    deviceController.setKeyboardDevice(keyboardDevice);
    deviceController.setGraphicsDevice(graphicsDevice);

    GUI::IO::SetGraphicsDevice(graphics);
}

void TApplication::onSuspend() { /* none */ }

void TApplication::onResume() { /* none */ }

void TApplication::update() {
    /* Example code:
     *
     *  window->clear();
     *  draw();
     *  window->display();
     */
}

const TDebugTools& TApplication::getDebugTools() const {
    return debugTools;
}

TDebugTools& TApplication::getDebugTools() {
    return debugTools;
}


TApplication& app() {
    return TApplication::GetInstance();
}

} // namespace GE