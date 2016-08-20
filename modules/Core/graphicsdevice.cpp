#include "graphicsdevice.h"
#include "exception.h"

namespace IO {

#if defined(WINDOWS)
#include <iostream>


TD3D9GraphicsDevice::TD3D9GraphicsDevice() :
    d3d9_object(nullptr),
    device(nullptr),
    vertexBuffer(nullptr),
    indexBuffer(nullptr)
{}

TD3D9GraphicsDevice::~TD3D9GraphicsDevice()
{}

HRESULT TD3D9GraphicsDevice::initialize(HWND hwnd) {
    d3d9_object = Direct3DCreate9(D3D_SDK_VERSION);
    ASSERT(d3d9_object != nullptr,
        "Failed to create Direct3d environment. "
            "Check your DirectX 9 installation.");

    D3DPRESENT_PARAMETERS parameters;
    parameters.Windowed = TRUE;
    parameters.BackBufferFormat = D3DFMT_UNKNOWN;
    parameters.BackBufferCount = 0;
    parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;  //debugging purposes
    parameters.MultiSampleType = D3DMULTISAMPLE_NONE; // because of swapEffect = discard
    parameters.EnableAutoDepthStencil = 0;
    parameters.BackBufferHeight = 0;
    parameters.BackBufferWidth = 0;
    parameters.Flags = 0;
    parameters.FullScreen_RefreshRateInHz = 0; // bocause of windowed mode
    parameters.hDeviceWindow = 0;
    parameters.MultiSampleQuality = 0;
    parameters.PresentationInterval = 0;

    HRESULT res = d3d9_object->CreateDevice(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        hwnd,
        D3DCREATE_HARDWARE_VERTEXPROCESSING,
        &parameters,
        &device);

    if (FAILED(res)) {
        std::cerr << "Failed to create d3ddevice: ";

        switch (res) {
        case D3DERR_DEVICELOST:
            std::cerr << "device was lost.";
            break;

        case D3DERR_INVALIDCALL:
            std::cerr << "wrong parameters.";
            break;

        case D3DERR_NOTAVAILABLE:
            std::cerr << "device was not available.";
            break;

        case D3DERR_OUTOFVIDEOMEMORY:
            std::cerr << "not enough video memory.";
            break;

        default: {/*none*/}
        }
        return res;
    }

    return res;
}

HRESULT TD3D9GraphicsDevice::render() {
    device->Clear(0, NULL, D3DCLEAR_TARGET,
                       D3DCOLOR_XRGB(0, 0, 100),
                       1.0f, 0);


    if (FAILED(device->BeginScene())) {
        std::cerr << "Failed to draw scene." << std::endl;
        return;
    }

    device->EndScene();
    return device->Present(NULL, NULL, NULL, NULL);
}

void TD3D9GraphicsDevice::release() {
    if (indexBuffer) {
        indexBuffer->Release();
        indexBuffer = nullptr;
    }
    if (vertexBuffer) {
        vertexBuffer->Release();
        vertexBuffer = nullptr;
    }
    if (device) {
        device->Release();
        device = nullptr;
    }
    if (d3d9_object) {
        d3d9_object->Release();
        d3d9_object = nullptr;
    }
}

#endif //WINDOWS


#if defined(SFML)

TSFMLGraphicsDevice::TSFMLGraphicsDevice(
    sf::RenderTarget* target
) :
    target(target)
{}

const sf::RenderTarget* TSFMLGraphicsDevice::get() const {
    return target;
}
sf::RenderTarget* TSFMLGraphicsDevice::get() {
    return target;
}
const sf::RenderTarget& TSFMLGraphicsDevice::operator*() const {
    return *target;
}
sf::RenderTarget& TSFMLGraphicsDevice::operator*() {
    return *target;
}
const sf::RenderTarget* TSFMLGraphicsDevice::operator->() const {
    return target;
}
sf::RenderTarget* TSFMLGraphicsDevice::operator->() {
    return target;
}

#endif //SFML

} // namespace IO
