#include "game_engine.h"
#include "GameEngine/engine_message.h"


namespace GE {

TGameEngine::TGameEngine() :
    componentSystems(this)
{}

void TGameEngine::Update(const TTime& step, Context& context) {
    componentSystems.Update(step, context);
}

void TGameEngine::SendMessage(const Message& message, Context& context) {
    componentSystems.SendMessage(message, context);
}

const TGameEngine::ScriptEngine&
TGameEngine::GetScriptEngine() const {
    return scriptEngine;
}

TGameEngine::ScriptEngine&
TGameEngine::GetScriptEngine() {
    return scriptEngine;
}

const TGameEngine::ComponentRegistry&
TGameEngine::GetComponentRegistry() const {
    return componentRegistry;
}

TGameEngine::ComponentRegistry&
TGameEngine::GetComponentRegistry() {
    return componentRegistry;
}

const TGameEngine::ComponentSystems&
TGameEngine::GetComponentSystems() const {
    return componentSystems;
}

TGameEngine::ComponentSystems&
TGameEngine::GetComponentSystems() {
    return componentSystems;
}

} //namespace GE
