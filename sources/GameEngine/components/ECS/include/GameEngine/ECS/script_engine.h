#ifndef SCRIPT_ENGINE_H
#define SCRIPT_ENGINE_H

#include "GameEngine/Utility/luawrapper.h"


GE_BEGIN_ENGINE_NAMESPACE

class TScriptEngine {
public:
    TScriptEngine();

    using Raw = lua::State;
    const Raw& Get() const;
    Raw& Get();
private:
    Raw raw;

    void initialize();
};

GE_END_ENGINE_NAMESPACE

#endif // SCRIPT_ENGINE_H
