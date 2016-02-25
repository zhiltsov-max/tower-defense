#include "application.h"
#include "debug.h"

#if !defined(NO_GUI_APPLICATION)
    #include "application_ui.h"
    #include "GUI/gui_core.h"
#endif //NO_GUI_APPLICATION



std::unique_ptr<TApplication> TApplication::_instance = nullptr;

TApplication& TApplication::Create(const TApplicationInfo& info) {
    new TApplication(info); // _instance set in constructor
    return *_instance;
}

TApplication* TApplication::GetInstance() {
    return _instance.get();
}

TApplication::TApplication(const TApplicationInfo& info) :
#if !defined(NO_GUI_APPLICATION)
    ui(nullptr),
#endif //NO_GUI_APPLICATION
    window(nullptr),
    debugTools(nullptr),
    exitCode(EXIT_SUCCESS),
    isRun(false)
{
    ASSERT(_instance == nullptr, "Can not create multiple instances of Application.")
    _instance.reset(this);

    initialize(info);

#if !defined(NO_GUI_APPLICATION)
    ui.reset(new TApplicationUI(info));
#endif //NO_GUI_APPLICATION

    debugTools.reset(new TDebugTools());
}

TApplication::~TApplication() {
    release();
    window->close();
}


int TApplication::run() {
#if defined(WINDOWS)
    isRun = true;
    Event evt;
    while (window && isRun) {
        while (GetMessage(&evt, NULL, 0, 0)) {
            TranslateMessage(&evt);
            handleEvent(evt);
            DispatchMessage(&evt);
        }

        update();
    }
    return (int)evt.wParam;

#endif //WINDOWS

#if defined(SFML)
    isRun = true;

    while (window->isOpen() && isRun) {
        Event evt;
        while (window->pollEvent(evt)) {
            handleEvent(evt);
        }

        update();
    }

    return exitCode;
#endif //SFML
}

void TApplication::handleEvent(const Event& evt) {
#if defined(SFML)
    if (evt.type == sf::Event::Closed) {
        exit(EXIT_SUCCESS);
    }

    auto keyboard = dynamic_cast<IO::TSFMLKeyboard*>(controller->getKeyboardDevice());
    keyboard->handleEvent(evt);

    auto mouse = dynamic_cast<IO::TSFMLMouse*>(controller->getMouseDevice());
    mouse->handleEvent(evt);
#endif //SFML
}

void TApplication::exit(int exitCode_) {
    isRun = false;
    exitCode = exitCode_;
}

#if defined(WINDOWS)
//TO DO: winapi calls for determining window size
float TApplication::getWindowWidth() const { return windowWidth; }
float TApplication::getWindowHeight() const { return windowHeight; }
#endif //WINDOWS

#if defined(SFML)
float TApplication::getWindowWidth() const { return window->getSize().x; }
float TApplication::getWindowHeight() const { return window->getSize().y; }
#endif //SFML

#if !defined(NO_GUI_APPLICATION)
const TApplicationUI& TApplication::getUI() const { return *ui; }
TApplicationUI& TApplication::getUI() { return *ui; }
#endif //NO_GUI_APPLICATION

void TApplication::setTitle(const TextString& value) {
#if defined(WINDOWS)
    SetWindowText(window, value.c_str());
#endif //WINDOWS

#if defined(SFML)
    window->setTitle(value);
#endif //SFML
}

const IO::TDeviceController& TApplication::getDeviceController() const {
    return *controller;
}

IO::TDeviceController& TApplication::getDeviceController() {
    return *controller;
}

#if defined(WINDOWS)

#if defined(WINDOWS_DIRECTINPUT)
void TApplication::initialize(const TApplicationInfo& info) {
    HRESULT res = InitApplication(info);
    if (FAILED(res)) {
        throw exception("Failed to create application. Error code: " + std::to_string(res));
    }
    res = InitWindow(info);
    if (FAILED(res)) {
        throw exception("Failed to create window. Error code: " + std::to_string(res));
    }

    auto mouse = new IO::TDIMouse();
    mouse->attach(window);

    auto keyboard = new IO::TDIKeyboard();
    keyboard->attach(window);

    controller.reset(new IO::TDeviceController());
    controller->setMouseDevice(mouse);
    controller->setKeyboardDevice(keyboard);
}

void TApplication::release() {
    controller.release();
}

void TApplication::renew() {
    auto mouse = dynamic_cast<IO::TDIMouse*>(controller->getMouseDevice());
    mouse->acquire();

    auto keyboard = dynamic_cast<IO::TDIKeyboard*>(controller->getKeyboardDevice());
    keyboard->acquire();
}

void TApplication::suspend() {
    auto mouse = dynamic_cast<IO::TDIMouse*>(controller->getMouseDevice());
    mouse->unacquire();

    auto keyboard = dynamic_cast<IO::TDIKeyboard*>(controller->getKeyboardDevice());
    keyboard->unacquire();
}

void TApplication::update() {
    controller->update();

    auto& keyboardInfo = controller->getKeyboardDevice()->getInfo();
    while (keyboardInfo.events.empty() == false) {
        if ((keyboardInfo.events.back().id == IO::EventId::KeyUp) &&
            (keyboardInfo.events.back().value == (int)IO::KeyboardKey::Key_ESCAPE))
        {
            DestroyWindow(window);
            window = 0;
        }
        keyboardInfo.events.pop();
    }
}
#endif //WINDOWS_DIRECTINPUT

#if defined(WINDOWS_SYSINPUT)
#error Not implemented yet.

void TApplication::update() {
    controller->update();
}


#endif //WINDOWS_SYSINPUT

LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
bool TApplication::initApplication(const TApplicationInfo& info) {
    WNDCLASSEX wcx;

    // Fill in the window class structure with parameters
    // that describe the main window.

    wcx.cbSize = sizeof(wcx);          // size of structure
    wcx.style = CS_HREDRAW |
        CS_VREDRAW;                    // redraw if size changes
    wcx.lpfnWndProc = MainWndProc;     // points to window procedure
    wcx.cbClsExtra = 0;                // no extra class memory
    wcx.cbWndExtra = 0;                // no extra window memory
    wcx.hInstance = info.hInst;        // handle to instance
    wcx.hIcon = LoadIcon(NULL,
        IDI_APPLICATION);              // predefined app. icon
    wcx.hCursor = LoadCursor(NULL,
        IDC_ARROW);                    // predefined arrow
    wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // white background brush
    wcx.lpszMenuName =  L"MainMenu";   // name of menu resource
    wcx.lpszClassName = L"MainWClass"; // name of window class
    wcx.hIconSm = (HICON)LoadImage(
        info.hInst,                    // small class icon
        MAKEINTRESOURCE(5),
        IMAGE_ICON,
        GetSystemMetrics(SM_CXSMICON),
        GetSystemMetrics(SM_CYSMICON),
        LR_DEFAULTCOLOR);

    // Register the window class.
    return RegisterClassEx(&wcx);
}

bool TApplication::initWindow(const TApplicationInfo& info) {
    window = CreateWindow(
        L"MainWClass",       // name of window class
        info.appTitle,       // title-bar string
        info.style,
        CW_USEDEFAULT,       // default horizontal position
        CW_USEDEFAULT,       // default vertical position
        info.windowWidth,
        info.windowHeight,
        (HWND) NULL,         // no owner window
        (HMENU) NULL,        // use class menu
        info.hInst,          // handle to application instance
        (LPVOID) NULL);      // no window-creation data

    if (!window) {
        return false;
    }

    ShowWindow(window, info.nShowCmd);
    UpdateWindow(window);
    return true;
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return FALSE; // Message not handled
}

#endif //WINDOWS

#if defined(SFML)
void TApplication::initialize(const TApplicationInfo& info) {
    bool res = initWindow(info);
    if (res == false) {
        throw exception("Failed to create window.");
    }
    window->setActive();

    auto mouse = new IO::TSFMLMouse();
    auto keyboard = new IO::TSFMLKeyboard();
    auto graphics = new IO::TSFMLGraphicsDevice(window.get());

#if !defined(NO_GUI_APPLICATION)
    GUI::IO::SetGraphicsDevice(graphics);
#endif //NO_GUI_APPLICATION

    controller.reset(new IO::TDeviceController());
    controller->setMouseDevice(mouse);
    controller->setKeyboardDevice(keyboard);
    controller->setGraphicsDevice(graphics);
}

void TApplication::release() { /*none*/ }
void TApplication::renew() { /*none*/ }
void TApplication::suspend() { /*none*/ }
void TApplication::update() {
    controller->update();

#if !defined(NO_GUI_APPLICATION)
    ui->update();
#endif //NO_GUI_APPLICATION

/*  example code:
 *
    window->clear();
    ui->draw();
    window->display();
*/
}

bool TApplication::initWindow(const TApplicationInfo& info) {
    window.reset(new Window_t(
        sf::VideoMode(info.windowWidth, info.windowHeight),
        info.appTitle, info.style, info.context));
    return (window != nullptr);
}
#endif //SFML

const TDebugTools& TApplication::getDebugTools() const { return *debugTools; }
TDebugTools& TApplication::getDebugTools() { return *debugTools; }

TApplication::Time TApplication::getTime() const {
    return timer.getElapsedTime().asMilliseconds();
}

TApplication* app() {
    return TApplication::GetInstance();
}
