#include "script_engine.h"
#include "GameEngine/Utility/core.h"
#include "GameEngine/ECS/engine_lua_binding.h"


namespace GE {

TScriptEngine::TScriptEngine() :
    raw()
{
    initialize();
}

const TScriptEngine::Raw& TScriptEngine::Get() const {
    return raw;
}

TScriptEngine::Raw& TScriptEngine::Get() {
    return raw;
}

void TScriptEngine::initialize() {
    try {
        //raw.call(lua::mkcf<GameEngine::lua_binding::bind>);
    } catch (const exception& e) {
        THROW(string("Failed to initialize script engine. The error is: ") + e.what());
    }
}

} // namespace GE
