#include "GameEngine/game_engine.h"
#include "GameEngine/engine_message.h"


namespace GE {

void TGameEngine::Update(const TTime& step, Context& context) {
    componentSystems.Update(step, context);
}

void TGameEngine::SendMessage(const Message& message, Context& context,
    const ComponentHandle& handle)
{
    componentSystems.SendMessage(message, context, handle);
}

const TGameEngine::ScriptEngine&
TGameEngine::GetScriptEngine() const {
    return scriptEngine;
}

TGameEngine::ScriptEngine&
TGameEngine::GetScriptEngine() {
    return scriptEngine;
}

const TGameEngine::ComponentSystemsManager&
TGameEngine::GetComponentSystemsManager() const {
    return componentSystems;
}

TGameEngine::ComponentSystemsManager&
TGameEngine::GetComponentSystemsManager() {
    return componentSystems;
}

} //namespace GE
