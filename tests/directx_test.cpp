#if !defined(WINDOWS)
#error WINDOWS define is required
#endif //WINDOWS

#if defined(SFML)
#error WINDOWS define is required instead of SFML
#endif //SFML

#if !defined(UNICODE)
#error UNICODE only supported now
#endif //UNICODE


#include <windows.h>

#include "Core/core.h"


//Defines
HINSTANCE hinst;
IO::TDeviceController* controller = nullptr;
IO::TD3D9GraphicsDevice* d3ddevice = nullptr;
HWND hWnd;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
BOOL InitApplication(HINSTANCE);
BOOL InitWindow(HINSTANCE, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);


#if defined(WINDOWS_DIRECTINPUT)
    void InitializeDirectInput(HWND);
    void UpdateDirectInput();
    void ReleaseDirectInput();
    void RenewDirectInput();
    void PauseDirectInput();

    void InitializeD3d(HWND hwnd);
    void UpdateD3d();
    void PauseD3d();
    void RenewD3d();
    void ReleaseD3d();
#endif //WINDOWS_DIRECTINPUT

void OnIdle();


BOOL InitApplication(HINSTANCE hinstance) {
    WNDCLASSEX wcx;

    // Fill in the window class structure with parameters
    // that describe the main window.

    wcx.cbSize = sizeof(wcx);          // size of structure
    wcx.style = CS_HREDRAW |
        CS_VREDRAW;                    // redraw if size changes
    wcx.lpfnWndProc = MainWndProc;     // points to window procedure
    wcx.cbClsExtra = 0;                // no extra class memory
    wcx.cbWndExtra = 0;                // no extra window memory
    wcx.hInstance = hinstance;         // handle to instance
    wcx.hIcon = LoadIcon(NULL,
        IDI_APPLICATION);              // predefined app. icon
    wcx.hCursor = LoadCursor(NULL,
        IDC_ARROW);                    // predefined arrow
    wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // white background brush
    wcx.lpszMenuName =  L"MainMenu";    // name of menu resource
    wcx.lpszClassName = L"MainWClass";  // name of window class
    wcx.hIconSm = (HICON)LoadImage(hinstance, // small class icon
        MAKEINTRESOURCE(5),
        IMAGE_ICON,
        GetSystemMetrics(SM_CXSMICON),
        GetSystemMetrics(SM_CYSMICON),
        LR_DEFAULTCOLOR);

    // Register the window class.

    return RegisterClassEx(&wcx);
}

BOOL InitWindow(HINSTANCE hInst, int nCmdShow) {
    UNUSED(hInst)
    HWND hwnd = CreateWindow(
        L"MainWClass",       // name of window class
        L"Core test",        // title-bar string
        WS_OVERLAPPEDWINDOW, // top-level window
        CW_USEDEFAULT,       // default horizontal position
        CW_USEDEFAULT,       // default vertical position
        CW_USEDEFAULT,       // default width
        CW_USEDEFAULT,       // default height
        (HWND) NULL,         // no owner window
        (HMENU) NULL,        // use class menu
        hinst,               // handle to application instance
        (LPVOID) NULL);      // no window-creation data

    if (!hwnd) {
        return FALSE;
    }

    hWnd = hwnd;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    InitializeDirectInput(hwnd);
    InitializeD3d(hwnd);

    return TRUE;
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
    case WM_CREATE:
        return true;

    case WM_SETFOCUS:
        RenewDirectInput();
        return true;

    case WM_KILLFOCUS:
        PauseDirectInput();
        return true;

    case WM_DESTROY:
        ReleaseDirectInput();
        ReleaseD3d();
        PostQuitMessage(0);
        return TRUE;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return FALSE; // Message not handled
}


void InitializeDirectInput(HWND hwnd) {
    auto mouse = new IO::TDIMouse();
    mouse->attach(hwnd);

    auto keyboard = new IO::TDIKeyboard();
    keyboard->attach(hwnd);

    controller = new IO::TDeviceController();
    controller->setMouseDevice(mouse);
    controller->setKeyboardDevice(keyboard);
}

void UpdateDirectInput() {
    controller->update();
    /*
    auto& mouseInfo = controller->getMouseInfo();
    while (mouseInfo.events.empty() == false) {
        std::cout << "<M>" << (int)(mouseInfo.events.front().id) << "=" << mouseInfo.events.front().value << std::endl;
        mouseInfo.events.pop();
    }

    auto& keyboardInfo = controller->getKeyboardInfo();
    while (keyboardInfo.events.empty() == false) {
        std::cout << "<K>" << (int)(keyboardInfo.events.front().id) << "=" << (int)keyboardInfo.events.front().value << std::endl;
        if ((keyboardInfo.events.back().id == IO::EventId::KeyUp) && (keyboardInfo.events.back().value == (int)IO::KeyboardKey::Key_ESCAPE)) {
            DestroyWindow(hwnd);
        }
        keyboardInfo.events.pop();
    }
    */
}

void PauseDirectInput() {
    auto mouse = dynamic_cast<IO::TDIMouse*>(controller->getMouseDevice());
    mouse->unacquire();

    auto keyboard = dynamic_cast<IO::TDIKeyboard*>(controller->getKeyboardDevice());
    keyboard->unacquire();
}

void RenewDirectInput() {
    auto mouse = dynamic_cast<IO::TDIMouse*>(controller->getMouseDevice());
    mouse->acquire();

    auto keyboard = dynamic_cast<IO::TDIKeyboard*>(controller->getKeyboardDevice());
    keyboard->acquire();
}

void ReleaseDirectInput() {
    std::cout << "DI released." << std::endl;
    delete controller;
}

void InitializeD3d(HWND hwnd) {
    d3ddevice = new IO::TD3D9GraphicsDevice();
    d3ddevice->initialize(hwnd);
}
void UpdateD3d() {
    if (d3ddevice) {
        d3ddevice->render();
    }
}
void PauseD3d() {}
void RenewD3d() {}
void ReleaseD3d() {
    if (d3ddevice) {
        d3ddevice->release();
    }
}

void OnIdle() {
    if (GetFocus() == hWnd) {
        UpdateDirectInput();
        UpdateD3d();
    }
}



int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hparent, LPSTR lpCmdLine, int nShowCmd) {
    hinst = hInst;
    UNUSED(hparent)
    UNUSED(lpCmdLine)

    if (!InitApplication(hInst)) {
        return 1;
    }

    if (!InitWindow(hInst, nShowCmd)) {
        return 2;
    }

    d3ddevice->createObjects();

    MSG msg;
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
            if (GetMessage(&msg, NULL, 0, 0)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        } else {
            OnIdle();
        }
    }

    return (int) msg.wParam;
}
