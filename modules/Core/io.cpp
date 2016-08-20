#include "io.h"


namespace IO {

#if defined(WINDOWS)
#if defined(WINDOWS_SYSINPUT)

TWinMessageKeyboard::TWinMessageKeyboard() {
    for (size_t i = 0; i != (short)KeyboardKey::_count; ++i) {
        keyCode[i] = MapVirtualKey(i, 0);
    }
}

void TWinMessageKeyboard::attach(HWND hwnd) {
    wndHandle = hwnd;
}

void TWinMessageKeyboard::detach() { /*none*/ }

void TWinMessageKeyboard::update() {
    MSG message; /* wParam == virtualCode */

    while (PeekMessage(&message, wndHandle, WM_KEYFIRST, WM_KEYLAST, PM_REMOVE) && info.events.size() < info.MAX_QUEUE_SIZE) {
        TranslateMessage(&message);
        const auto key = convert(message.wParam);

        switch (message.message) {
        case WM_KEYDOWN:
            if (isPressed(key) == false) {
                pressKey(key);
            }
            break;

        case WM_KEYUP:
            if (isPressed(key) == true) {
                releaseKey(key);
            }
            break;

        default: {/*none*/}
        };

        DispatchMessage(&message);
    }
}

const TKeyboardInfo& TWinMessageKeyboard::getInfo() const {
    return info;
}

TKeyboardInfo& TWinMessageKeyboard::getInfo() {
    return info;
}

bool TWinMessageKeyboard::isPressed(KeyCode code) const {
    return info.keyState[code] == KeyState::Pressed;
}
void TWinMessageKeyboard::releaseKey(KeyCode code) {
    info.keyState[code] = KeyState::Released;
    info.events.emplace(EventId::KeyUp, code);
}
void TWinMessageKeyboard::pressKey(KeyCode code) {
    info.keyState[code] = KeyState::Hit;
    info.events.emplace(EventId::KeyDown, code);
}



void TWinMessageMouse::attach(HWND hwnd) {
    wndHandle = hwnd;
}

void TWinMessageMouse::detach() { /*none*/ }

void TWinMessageMouse::update() {
    MSG message; /* wParam == flags, lParam == position[y, x] */

    while (PeekMessage(&message, wndHandle, WM_MOUSEFIRST, WM_MOUSELAST, PM_REMOVE) && info.events.size() < info.MAX_QUEUE_SIZE) {
        TranslateMessage(&message);

        switch (message.message) {
        case WM_LBUTTONDOWN:
            const KeyCode key = (KeyCode)MouseKey::Left;
            if (isPressed(key) == false) {
                pressKey(key);
            }
            break;

        case WM_LBUTTONUP:
            const KeyCode key = (KeyCode)MouseKey::Left;
            if (isPressed(key) == true) {
                releaseKey(key);
            }
            break;

        case WM_RBUTTONDOWN:
            const KeyCode key = (KeyCode)MouseKey::Right;
            if (isPressed(key) == false) {
                pressKey(key);
            }
            break;

        case WM_RBUTTONUP:
            const KeyCode key = (KeyCode)MouseKey::Right;
            if (isPressed(key) == true) {
                releaseKey(key);
            }
            break;

        case WM_MBUTTONDOWN:
            const KeyCode key = (KeyCode)MouseKey::Middle;
            if (isPressed(key) == false) {
                pressKey(key);
            }
            break;

        case WM_MBUTTONUP:
            const KeyCode key = (KeyCode)MouseKey::Middle;
            if (isPressed(key) == true) {
                releaseKey(key);
            }
            break;

        case WM_MOUSEMOVE:
            const auto xPos = GET_X_LPARAM(message.lParam);
            const auto yPos = GET_Y_LPARAM(message.lParam);
            info.speed[0] = xPos - info.axis[0];
            info.speed[1] = yPos - info.axis[1];
            info.axis[0] = xPos;
            info.axis[1] = yPos;
            if (info.speed[0]) { info.events.emplace(EventId::MouseXmove, info.speed[0]); }
            if (info.speed[1]) { info.events.emplace(EventId::MouseYmove, info.speed[1]); }
            break;

        case WM_MOUSEWHEEL:
            info.speed[2] = GET_WHEEL_DELTA_WPARAM(message.wParam);
            if (info.speed[2]) {
                info.axis[2] += info.speed[2];
                info.events.emplace(EventId::MouseZmove, info.speed[2]);
            }
            break;

        default: {/*none*/}
        };

        DispatchMessage(&message);
    }
}

const TMouseInfo& TWinMessageMouse::getInfo() const {
    return info;
}

TMouseInfo& TWinMessageMouse::getInfo() {
    return info;
}

bool TWinMessageMouse::isPressed(KeyCode code) const {
    return info.keyState[code] == KeyState::Pressed;
}
void TWinMessageMouse::releaseKey(KeyCode code) {
    info.keyState[code] = KeyState::Released;
    info.events.emplace(EventId::MouseUp, code);
}
void TWinMessageMouse::pressKey(KeyCode code) {
    info.keyState[code] = KeyState::Hit;
    info.events.emplace(EventId::MouseDown, code);
}
#endif //WINDOWS_SYSINPUT

#if defined(WINDOWS_DIRECTINPUT)

TDIKeyboard::TDIKeyboard() :
    bufferSize(10)
{
    buffer = new DIDEVICEOBJECTDATA[bufferSize];
}

TDIKeyboard::~TDIKeyboard() {
    detach();
    if (buffer != nullptr) {
        delete buffer;
    }
}

void TDIKeyboard::attach(HWND hwnd) {
    DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION,
                       IID_IDirectInput8, (void**)&dxInput, NULL);

    DIPROPDWORD dipdw;
    dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwObj        = 0;
    dipdw.diph.dwHow        = DIPH_DEVICE;
    dipdw.dwData            = TKeyboardInfo::MAX_QUEUE_SIZE;

    dxInput->CreateDevice(GUID_SysKeyboard, &dxDevice, NULL);
    dxDevice->SetDataFormat(&c_dfDIKeyboard);
    dxDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    dxDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
    HRESULT res = dxDevice->Acquire();
    if (FAILED(res)) {
        std::cerr << "Failed to acquire system keyboard: " <<std::endl
                  << "\tcode:" << res << std::endl;
        switch (res) {
        case DIERR_INVALIDPARAM:
            std::cerr << "\tWrong data format." << std::endl;
            break;

        case DIERR_NOTINITIALIZED:
            std::cerr << "\tNot initialized." << std::endl;
            break;

        case DIERR_OTHERAPPHASPRIO:
            std::cerr << "\tOther application has higher proirity." << std::endl;
            break;
        default: {/*none*/}
        }
    }
}

void TDIKeyboard::detach() {
    if (dxDevice != nullptr) {
        dxDevice->Unacquire();
        dxDevice->Release();
        dxDevice = nullptr;
    }

    if (dxInput != nullptr) {
       dxInput->Release();
       dxInput = nullptr;
    }
}

void TDIKeyboard::update() {
    DWORD range = bufferSize; // want recieve, changed to recieved count
    if (buffer == nullptr) {
        buffer = new DIDEVICEOBJECTDATA[bufferSize];
    }
    DWORD done = 0;
    HRESULT res = dxDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), buffer, &range, 0);
    if (FAILED(res)) {
        if (res == DIERR_NOTACQUIRED) {
            dxDevice->Acquire();
            std::cerr << "DI keyboard had not been acquired." << std::endl;
        }
        return;
    }
    if (range == done) { /* no messages recieved */
        return;
    }

    while ((info.events.size() < info.MAX_QUEUE_SIZE) && (done < range)) {
        const auto& data = buffer[done];
        /* pressed == 128, released == 0 */
        if (data.dwData) {
            pressKey(data.dwOfs);
        } else {
            releaseKey(data.dwOfs);
        };
        ++done;
    }
}

const TKeyboardInfo& TDIKeyboard::getInfo() const {
    return info;
}

TKeyboardInfo& TDIKeyboard::getInfo() {
    return info;
}

void TDIKeyboard::acquire() {
    if (dxDevice != nullptr) {
        dxDevice->Acquire();
    }
}

void TDIKeyboard::unacquire() {
    if (dxDevice != nullptr) {
        dxDevice->Unacquire();
    }
}

void TDIKeyboard::flush() {
    DWORD range = INFINITE;
    dxDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), NULL, &range, 0);
}

bool TDIKeyboard::isPressed(KeyCode code) const {
    return info.keyState[code] == KeyState::Pressed;
}
void TDIKeyboard::releaseKey(KeyCode code) {
    info.keyState[code] = KeyState::Released;
    info.events.emplace(EventId::KeyUp, code);
}
void TDIKeyboard::pressKey(KeyCode code) {
    info.keyState[code] = KeyState::Hit;
    info.events.emplace(EventId::KeyDown, code);
}



TDIMouse::TDIMouse() :
    bufferSize(10)
{
    buffer = new DIDEVICEOBJECTDATA[bufferSize];
}

TDIMouse::~TDIMouse() {
    detach();
    if (buffer != nullptr) {
        delete buffer;
    }
}

void TDIMouse::attach(HWND hwnd) {
    DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION,
                       IID_IDirectInput8, (void**)&dxInput, NULL);
    dxInput->CreateDevice(GUID_SysMouse, &dxDevice, NULL);

    event = CreateEvent(NULL, FALSE, FALSE, NULL);

    DIPROPDWORD dipdw;
    dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwObj        = 0;
    dipdw.diph.dwHow        = DIPH_DEVICE;
    dipdw.dwData            = TMouseInfo::MAX_QUEUE_SIZE;

    dxDevice->SetDataFormat(&c_dfDIMouse);
    dxDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    dxDevice->SetEventNotification(event);
    dxDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
    HRESULT res = dxDevice->Acquire();
    if (FAILED(res)) {
        std::cerr << "Failed to acquire system mouse: " <<std::endl
                  << "\tcode:" << res << std::endl;
        switch (res) {
        case DIERR_INVALIDPARAM:
            std::cerr << "\tWrong data format." << std::endl;
            break;

        case DIERR_NOTINITIALIZED:
            std::cerr << "\tNot initialized." << std::endl;
            break;

        case DIERR_OTHERAPPHASPRIO:
            std::cerr << "\tOther application has higher proirity." << std::endl;
            break;
        default: {/*none*/}
        }
    }

}

void TDIMouse::detach() {
    if (dxDevice != nullptr) {
        dxDevice->Unacquire();
        dxDevice->Release();
        dxDevice=nullptr;
    }

    if (event != nullptr) {
        CloseHandle(event);
    }

    if (dxInput != nullptr) {
        dxInput->Release();
        dxInput = nullptr;
    }
}

void TDIMouse::acquire() {
    if (dxDevice != nullptr) {
        dxDevice->Acquire();
    }
}

void TDIMouse::unacquire() {
    if (dxDevice != nullptr) {
        dxDevice->Unacquire();
    }
}

void TDIMouse::update() {
    DWORD range = bufferSize; // want recieve, changed to recieved count
    if (buffer == nullptr) {
        buffer = new DIDEVICEOBJECTDATA[bufferSize];
    }
    DWORD done = 0;
    HRESULT res = dxDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), buffer, &range, 0);
    if (FAILED(res)) {
        if (res == DIERR_NOTACQUIRED) {
            dxDevice->Acquire();
            std::cerr << "DI mouse had not been acquired." << std::endl;
        }
        return;
    }
    if (range == done) { /* no messages recieved */
        return;
    }

    while ((info.events.size() < info.MAX_QUEUE_SIZE) && (done < range)) {
        const auto& data = buffer[done];
        switch (data.dwOfs) {
        case DIMOFS_X:
            if (data.dwData) {
                info.events.emplace(EventId::MouseXmove, data.dwData);
                info.axis[0] += data.dwData;
                info.speed[0] = data.dwData;
            }
            break;

        case DIMOFS_Y:
            if (data.dwData) {
                info.events.emplace(EventId::MouseYmove, data.dwData);
                info.axis[1] += data.dwData;
                info.speed[1] = data.dwData;
            }
            break;

        case DIMOFS_Z:
            if (data.dwData) {
                info.events.emplace(EventId::MouseZmove, data.dwData);
                info.axis[2] += data.dwData;
                info.speed[2] = data.dwData;
            }
            break;

        case DIMOFS_BUTTON0:
            const auto key = (KeyCode)MouseKey::Left;
            if (data.dwData) {
                pressKey(key);
            } else {
                releaseKey(key);
            }
            break;

        case DIMOFS_BUTTON1:
            const auto key = (KeyCode)MouseKey::Right;
            if (data.dwData) {
                pressKey(key);
            } else {
                releaseKey(key);
            }
            break;

        case DIMOFS_BUTTON2:
            const auto key = (KeyCode)MouseKey::Middle;
            if (data.dwData) {
                pressKey(key);
            } else {
                releaseKey(key);
            }
            break;

        default: {/*none*/}
        };

        ++done;
    };
}

const TMouseInfo& TDIMouse::getInfo() const {
    return info;
}

TMouseInfo& TDIMouse::getInfo() {
    return info;
}

void TDIMouse::flush() {
    DWORD range = INFINITE;
    dxDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), NULL, &range, 0);
}

bool TDIMouse::isPressed(KeyCode code) const {
    return info.keyState[code] == KeyState::Pressed;
}
void TDIMouse::releaseKey(KeyCode code) {
    info.keyState[code] = KeyState::Released;
    info.events.emplace(EventId::MouseUp, code);
}
void TDIMouse::pressKey(KeyCode code) {
    info.keyState[code] = KeyState::Hit;
    info.events.emplace(EventId::MouseDown, code);
}

#endif //WINDOWS_DIRECTINPUT
#endif //WINDOWS

#if defined(SFML)
void TSFMLKeyboard::update() {
    /*none*/
}

void TSFMLKeyboard::handleEvent(const sf::Event& evt) {
    switch (evt.type) {
    case sf::Event::KeyPressed:
        {
            const KeyCode key = static_cast<KeyCode>(evt.key.code);
            if (isPressed(key) == false) {
                pressKey(key);
            }
            break;
        }

    case sf::Event::KeyReleased:
        {
            const KeyCode key = static_cast<KeyCode>(evt.key.code);
            if (isPressed(key) == true) {
                releaseKey(key);
            }
            break;
        }

    default: {/*none*/}
    };
}

const TKeyboardInfo& TSFMLKeyboard::getInfo() const {
    return info;
}

TKeyboardInfo& TSFMLKeyboard::getInfo() {
    return info;
}

bool TSFMLKeyboard::isPressed(KeyCode code) const {
    return info.keyState[code] == KeyState::Pressed;
}
void TSFMLKeyboard::releaseKey(KeyCode code) {
    info.keyState[code] = KeyState::Released;
    info.events.emplace(EventId::KeyUp, code);
}
void TSFMLKeyboard::pressKey(KeyCode code) {
    info.keyState[code] = KeyState::Hit;
    info.events.emplace(EventId::KeyDown, code);
}



void TSFMLMouse::update() {
    /*none*/
}

const TMouseInfo& TSFMLMouse::getInfo() const {
    return info;
}

TMouseInfo& TSFMLMouse::getInfo() {
    return info;
}

void TSFMLMouse::handleEvent(const sf::Event& evt) {
    switch (evt.type) {
    case sf::Event::MouseButtonPressed:
        {
            const auto key = (KeyCode)evt.mouseButton.button;
            if (isPressed(key) == false) {
                pressKey(key, evt.mouseButton.x, evt.mouseButton.y);
            }
            break;
        }

    case sf::Event::MouseButtonReleased:
        {
            const auto key = (KeyCode)evt.mouseButton.button;
            if (isPressed(key) == true) {
                releaseKey(key);
            }
            break;
        }

    case sf::Event::MouseMoved:
        {
            const auto xPos = evt.mouseMove.x;
            const auto yPos = evt.mouseMove.y;
            info.speed[0] = xPos - info.axis[0];
            info.speed[1] = yPos - info.axis[1];
            info.axis[0] = xPos;
            info.axis[1] = yPos;
            if (info.speed[0]) { info.events.emplace(EventId::MouseXmove, info.speed[0]); }
            if (info.speed[1]) { info.events.emplace(EventId::MouseYmove, info.speed[1]); }
            break;
        }

    case sf::Event::MouseWheelMoved:
        {
            info.speed[2] = evt.mouseWheel.delta;
            if (info.speed[2]) {
                info.axis[2] += info.speed[2];
                info.events.emplace(EventId::MouseZmove, info.speed[2]);
            }
            break;
        }

    default: {/*none*/}
    }
}

bool TSFMLMouse::isPressed(KeyCode code) const {
    return info.keyState[code] == KeyState::Pressed;
}
void TSFMLMouse::releaseKey(KeyCode code) {
    info.keyState[code] = KeyState::Released;
    info.events.emplace(EventId::MouseUp, code);
}
void TSFMLMouse::pressKey(KeyCode code, int x, int y) {
    info.keyState[code] = KeyState::Hit;
    info.events.emplace(EventId::MouseDown, code);
    info.events.back().mouseDown.x = x;
    info.events.back().mouseDown.y = y;
}

#endif //SFML


} // namespace IO
