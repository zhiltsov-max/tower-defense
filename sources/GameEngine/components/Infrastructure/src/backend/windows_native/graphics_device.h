#ifndef GAME_ENGINE_WINDOWS_GRAPHICS_DEVICE_H
#define GAME_ENGINE_WINDOWS_GRAPHICS_DEVICE_H

#include <d3d9.h>

#include "GameEngine/Infrastructure/graphics_device.h"


namespace GE {

namespace IO {

class TD3D9GraphicsDevice : public TGraphicsDevice
{
private:
    IDirect3D9* d3d9_object;
    IDirect3DDevice9* device;
    IDirect3DVertexBuffer9* vertexBuffer;
    IDirect3DIndexBuffer9* indexBuffer;

public:
    TD3D9GraphicsDevice();
    ~TD3D9GraphicsDevice();

    HRESULT initialize(HWND hwnd);
    HRESULT render();
    void release();
};

} // namespace IO

} // namespace GE

#endif // GAME_ENGINE_WINDOWS_GRAPHICS_DEVICE_H