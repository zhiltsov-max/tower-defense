#ifndef GAME_ENGINE_APPLICATION_H
#define GAME_ENGINE_APPLICATION_H

#include <memory>

#include "GameEngine/Utility/common.h"


GE_BEGIN_ENGINE_NAMESPACE

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

GE_END_ENGINE_NAMESPACE

#endif // GAME_ENGINE_APPLICATION_H
