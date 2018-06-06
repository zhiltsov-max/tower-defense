#ifndef GRAPHICSDEVICE_H
#define GRAPHICSDEVICE_H

#include "checkdef.h"


namespace IO {

class TGraphicsDevice
{
public:
    virtual ~TGraphicsDevice() = default;
};

} // namespace IO


#if defined(WINDOWS)
    #include <d3d9.h>


    namespace IO {

    class TD3D9GraphicsDevice : public TGraphicsDevice
    {
    public:
        IDirect3D9* d3d9_object;
        IDirect3DDevice9* device;
        IDirect3DVertexBuffer9* vertexBuffer;
        IDirect3DIndexBuffer9* indexBuffer;


        TD3D9GraphicsDevice();
        ~TD3D9GraphicsDevice();

        HRESULT initialize(HWND hwnd);
        HRESULT render();
        void release();
    };

    } // namespace IO
#endif //WINDOWS


#if defined(SFML)
    #include "SFML/OpenGL.hpp"
    #include "SFML/Graphics.hpp"


    namespace IO {

    class TSFMLGraphicsDevice : public TGraphicsDevice
    {
    public:
        TSFMLGraphicsDevice(sf::RenderTarget* target = nullptr);
        ~TSFMLGraphicsDevice() = default;

        const sf::RenderTarget* get() const;
        sf::RenderTarget* get();
        const sf::RenderTarget& operator*() const;
        sf::RenderTarget& operator*();
        const sf::RenderTarget* operator->() const;
        sf::RenderTarget* operator->();

    private:
        typedef sf::RenderTarget* TargetRef;
        TargetRef target;
    };

    } // namespace IO
#endif //SFML

#endif // GRAPHICSDEVICE_H
