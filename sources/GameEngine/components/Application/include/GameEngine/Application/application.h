#ifndef APPLICATION_H
#define APPLICATION_H

#include "GameEngine/Utility/core.h"

#if defined(WINDOWS)
    #include "windows.h"
#elif defined(SFML)
    #include "SFML/Window.hpp"
    #include "SFML/Graphics.hpp"
#endif // SFML



struct TApplicationInfo
{
#if defined(WINDOWS)
    HINSTANCE hInst;
    HINSTANCE hParent;
    LPSTR lpCmdLine;
    int nShowCmd;

#if defined(UNICODE)
    LPWSTR appTitle;
#else // UNICODE
    LPSTR appTitle;
#endif // UNICODE

    DWORD style;

#elif defined(SFML)
    TextString appTitle;

    int style;
    sf::ContextSettings context;
#endif // SFML

    uint windowWidth;
    uint windowHeight;

    int* argc;
    char*** argv;
};


class TDebugTools;

#if !defined(NO_GUI_APPLICATION)
    class TApplicationUI;
#endif //NO_GUI_APPLICATION


class TApplication
{
public:
    static TApplication& Create(
        const TApplicationInfo& info = TApplicationInfo());
    static TApplication* GetInstance();


    virtual ~TApplication();

    /*
    Incapsulates application lifecycle.
    Performs an updating and control of the application state.
    Includes main application cycle.
    */
    virtual int run();

    float getWindowWidth() const;
    float getWindowHeight() const;

#if !defined(NO_GUI_APPLICATION)
    const TApplicationUI& getUI() const;
    TApplicationUI& getUI();
#endif // NO_GUI_APPLICATION

    void setTitle(const TextString& value);

    const IO::TDeviceController& getDeviceController() const;
    IO::TDeviceController& getDeviceController();

    const TDebugTools& getDebugTools() const;
    TDebugTools& getDebugTools();

    typedef uint Time;
    Time getTime() const; // TODO: move to device controller

    /*
    Exit from the application.
    */
    void exit(int exitCode = EXIT_SUCCESS);

#if defined(WINDOWS)
    typedef MSG Event;
#endif // WINDOWS

#if defined(SFML)
    typedef sf::Event Event;
#endif // SFML


protected:
    static std::unique_ptr<TApplication> _instance;

#if !defined(NO_GUI_APPLICATION)
    using UI = std::unique_ptr<TApplicationUI>;
    UI ui;
#endif // NO_GUI_APPLICATION

#if defined(WINDOWS)
    HINSTANCE hInst;
    typedef HWND Window;
#endif // WINDOWS

#if defined(SFML)
    typedef sf::RenderWindow TWindow;
    typedef std::unique_ptr<TWindow> Window;
    typedef sf::Clock Timer;
#endif // SFML

    Window window;

    std::unique_ptr<TDebugTools> debugTools;
    Timer timer;

    typedef int ExitCode;
    ExitCode exitCode;

    bool isRun;


    TApplication(const TApplicationInfo& info);

    /*
    Initialize the application data.
    Called in the constructor to initialize the low-level data structures.
    Includes I/O subsystems and window initialization.
    */
    virtual void initialize(const TApplicationInfo& info);

    /*
    Update current application state.
    Called in every iteration of the main message cycle
    in the run() method after handling of all the new events.
    */
    virtual void update();

    /*
    Release the resources allocated by the application.
    Called before exiting from the application.
    */
    virtual void release();

    /*
    Restore the resources after suspending of the window.
    Called during window restoring.
    */
    virtual void renew();

    /*
    Save the critical data before suspending the window.
    Called before window suspending.
    */
    virtual void suspend();

    /*
    Handle a window event.
    Called for every event passed to the window in every
    iteration of the main cycle in run() method.
    */
    virtual void handleEvent(const Event& evt);


    using DeviceController = std::unique_ptr<IO::TDeviceController>;
    DeviceController controller;


#if defined(WINDOWS)
    bool initApplication(const TApplicationInfo& info);
#endif // WINDOWS

    bool initWindow(const TApplicationInfo& info);
};

TApplication* app(); // TODO: change pointer to reference

#endif // APPLICATION_H
