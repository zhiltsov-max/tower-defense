#ifndef SCRIPT_ENGINE_H
#define SCRIPT_ENGINE_H

#include "GameEngine/Utility/luawrapper.h"


namespace GE {

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

} // namespace GE

#endif // SCRIPT_ENGINE_H
