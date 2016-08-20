#ifndef CORE_IO_H
#define CORE_IO_H

#include "checkdef.h"
#include "key_defs.h"


namespace IO {

class TKeyboardDevice
{
public:
    virtual ~TKeyboardDevice() = default;
    virtual void update() = 0;
    virtual const TKeyboardInfo& getInfo() const = 0;
    virtual TKeyboardInfo& getInfo() = 0;
};

class TMouseDevice
{
public:
    virtual ~TMouseDevice() = default;
    virtual void update() = 0;
    virtual const TMouseInfo& getInfo() const = 0;
    virtual TMouseInfo& getInfo() = 0;
};

} // namespace IO


#if defined(WINDOWS)
    #include <windows.h>


    #if defined(WINDOWS_SYSINPUT)
        namespace IO {

        class TWinMessageKeyboard : public TKeyboardDevice
        {
        public:
            TWinMessageKeyboard();
            ~TWinMessageKeyboard() = default;

            void attach(HWND hwnd);
            void detach();

            void update();
            const TKeyboardInfo& getInfo() const;
            TKeyboardInfo& getInfo();
        private:
            TKeyboardInfo info;

            HWND wndHandle;
            char keyCode[(short)KeyboardKey::_count];   //remapping VirtualCode -> ScanCode

            typedef unsigned char KeyCode;
            inline KeyCode convert(KeyCode code) const {
                return keyCode[code];
            }
            bool isPressed(KeyCode code) const;
            void releaseKey(KeyCode code);
            void pressKey(KeyCode code);
        };

        class TWinMessageMouse : public TMouseDevice
        {
        public:
            TWinMessageMouse() = default;
            ~TWinMessageMouse() = default;

            void attach(HWND hwnd);
            void detach();

            void update();
            const TMouseInfo& getInfo() const;
            TMouseInfo& getInfo();
        private:
            TMouseInfo info;
            HWND wndHandle;

            typedef unsigned char KeyCode;
            bool isPressed(KeyCode code) const;
            void releaseKey(KeyCode code);
            void pressKey(KeyCode code);
        };

        } //namspace IO

    #endif //WINDOWS_SYSINPUT

    #if defined(WINDOWS_DIRECTINPUT)
        #include <dinput.h>


        namespace IO {

        class TDIKeyboard : public TKeyboardDevice
        {
        public:
            TDIKeyboard();
            ~TDIKeyboard();

            void attach(HWND hwnd);
            void detach();
            void acquire();
            void unacquire();

            void update();
            const TKeyboardInfo& getInfo() const;
            TKeyboardInfo& getInfo();

            void flush();
        private:
            TKeyboardInfo info;

            char bufferSize;
            DIDEVICEOBJECTDATA* buffer;

            typedef char KeyCode;

            LPDIRECTINPUT8       dxInput;
            LPDIRECTINPUTDEVICE8 dxDevice;

            typedef unsigned char KeyCode;
            bool isPressed(KeyCode code) const;
            void releaseKey(KeyCode code);
            void pressKey(KeyCode code);
        };

        class TDIMouse : public TMouseDevice
        {
        public:
            TDIMouse();
            ~TDIMouse();

            void attach(HWND hwnd);
            void detach();
            void acquire();
            void unacquire();

            void update();
            const TMouseInfo& getInfo() const;
            TMouseInfo& getInfo();

            void flush();
        private:
            TMouseInfo info;

            char bufferSize;
            DIDEVICEOBJECTDATA* buffer;

            LPDIRECTINPUT8        dxInput;
            LPDIRECTINPUTDEVICE8  dxDevice;
            HANDLE                event;

            typedef unsigned char KeyCode;
            bool isPressed(KeyCode code) const;
            void releaseKey(KeyCode code);
            void pressKey(KeyCode code);
        };

        } // namespace IO
    #endif //WINDOWS_DIRECTINPUT
#endif //WINDOWS

#if defined(SFML)
    #include "SFML/Window.hpp"


    namespace IO {

    class TSFMLKeyboard : public TKeyboardDevice
    {
    public:
        TSFMLKeyboard() = default;
        ~TSFMLKeyboard() = default;

        void update();
        void handleEvent(const sf::Event& evt);

        const TKeyboardInfo& getInfo() const;
        TKeyboardInfo& getInfo();
    private:
        TKeyboardInfo info;

        typedef unsigned char KeyCode;
        bool isPressed(KeyCode code) const;
        void releaseKey(KeyCode code);
        void pressKey(KeyCode code);
    };

    class TSFMLMouse : public TMouseDevice
    {
    public:
        TSFMLMouse() = default;
        ~TSFMLMouse() = default;

        void update();
        void handleEvent(const sf::Event& evt);
        const TMouseInfo& getInfo() const;
        TMouseInfo& getInfo();
    private:
        TMouseInfo info;

        typedef unsigned char KeyCode;
        bool isPressed(KeyCode code) const;
        void releaseKey(KeyCode code);
        void pressKey(KeyCode code, int x, int y);
    };

    } // namespace IO
#endif //SFML

#endif //CORE_IO_H
