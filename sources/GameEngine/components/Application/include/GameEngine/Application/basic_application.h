#ifndef GAME_ENGINE_BASIC_APPLICATION_H
#define GAME_ENGINE_BASIC_APPLICATION_H

#include "GameEngine/Utility/debug.h"
#include "GameEngine/Utility/string.h"
#include "GameEngine/Infrastructure/window.h"
#include "GameEngine/Infrastructure/device_controller.h"


namespace GE {

class TBasicApplication : public AApplication {
public:
    static TBasicApplication* GetInstance();

    struct TParameters {
        struct TWindowParameters {
            TextString title = "Basic window";

            uint width = 200;
            uint height = 200;

            int style = sf::Style::Default;
        };

        TWindowParameters window;

        int* argc = nullptr;
        char*** argv = nullptr;
    };

    TBasicApplication(const TParameters& parameters);
    ~TBasicApplication();

    virtual TExitCode run() override;

    const IO::TDeviceController& getDeviceController() const;
    IO::TDeviceController& getDeviceController();

    const TDebugTools& getDebugTools() const;
    TDebugTools& getDebugTools();

    enum class EExitCode : TExitCode {
        Success = 0,
        Failure = 1
    };

    /*
     * Request application exit.
     */
    void exit(EExitCode exitCode = EExitCode::Success);

protected:
    IO::TDeviceController deviceController;

    using PWindow = std::unique_ptr<TWindow>;
    PWindow window;

    TDebugTools debugTools;

    EExitCode exitCode;
    bool isRunning;


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

} // namespace GE

#endif // GAME_ENGINE_BASIC_APPLICATION_H