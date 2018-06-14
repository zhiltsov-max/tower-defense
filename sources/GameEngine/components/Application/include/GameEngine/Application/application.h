#ifndef GAME_ENGINE_APPLICATION_H
#define GAME_ENGINE_APPLICATION_H

#include "GameEngine/Utility/debug.h"
#include "GameEngine/Utility/string.h"
#include "GameEngine/Infrastructure/window.h"
#include "GameEngine/Infrastructure/device_controller.h"


namespace GE {

struct TApplicationInfo
{
    TextString appTitle;

    int style;
    sf::ContextSettings context;

    uint windowWidth;
    uint windowHeight;

    int* argc;
    char*** argv;
};


class TApplication
{
public:
    static TApplication* GetInstance();

    virtual ~TApplication();

    /*
     * Incapsulates application lifecycle.
     * Implements main application event-handling loop.
     */
    virtual int run();

    const IO::TDeviceController& getDeviceController() const;
    IO::TDeviceController& getDeviceController();

    const TDebugTools& getDebugTools() const;
    TDebugTools& getDebugTools();

    using TExitCode = int;
    enum class EExitCode : TExitCode {
        Success = 0,
        Failure = 1
    };
    /*
     * Exit from the application.
     */
    void exit(EExitCode exitCode = EExitCode::Success);

protected:
    using PApplication = std::unique_ptr<TApplication>;
    static PApplication instance;

    IO::TDeviceController deviceController;

    using PWindow = std::unique_ptr<TWindow>;
    PWindow window;

    TDebugTools debugTools;

    EExitCode exitCode;
    bool isRunning;


    TApplication(const TApplicationInfo& info);

    /*
     * Initialize the application data.
     * Called in the constructor to initialize the low-level data structures.
     * Includes I/O subsystems and window initialization.
     */
    virtual void initialize(const TApplicationInfo& info);

    /*
     * Update current application state.
     * Called in every iteration of the main message cycle
     * in the run() method after handling of all the new events.
     */
    virtual void update();

    /*
     * Restore the resources after window suspension.
     */
    virtual void onResume();

    /*
     * Save the critical data before window suspension.
     */
    virtual void onSuspend();

    /*
     * Called before application exit.
     */
    virtual void onExit();

    /*
     * Handle a window event.
     * Called for every event passed to the window in every
     * iteration of the main cycle in run() method.
     */
    virtual void handleEvent(const TWindowEvent& evt);
};


TApplication& app();

} // namespace GE

#endif // GAME_ENGINE_APPLICATION_H
