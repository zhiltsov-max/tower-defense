#ifndef GAME_ENGINE_APPLICATION_H
#define GAME_ENGINE_APPLICATION_H

#include <memory>


namespace GE {

class AApplication {
public:
    static AApplication* GetInstance();

    virtual ~AApplication();

    using TExitCode = int;

    /*
     * Incapsulates application lifecycle.
     * Implements main application event-handling loop.
     */
    virtual TExitCode run();

protected:
    using PApplication = std::unique_ptr<AApplication>;
    static PApplication instance;

    AApplication();
};


AApplication* app();

} // namespace GE

#endif // GAME_ENGINE_APPLICATION_H
