#include "game_engine.h"
#include "GameEngine/engine_message.h"


namespace GE {

TGameEngine::TGameEngine() :
    componentSystems(this)
{}

void TGameEngine::Update(const TTime& step, Context& context) {
    /*
    The concrete order of system updates is specified by adjusting index
    in ComponentSystems enumeration.
    */
    for (auto& system : componentSystems.systems) {
        system->Update(step, context);
    }
}

void TGameEngine::Draw(Graphics::TRenderTarget& target) {
    componentSystems.graphics.Render(target);
    componentSystems.ui.Draw(target);
}

void TGameEngine::SendMessage(const Message& message, Context& context) {
    for (auto& system : componentSystems.systems) {
        system->HandleMessage(message, context);
    }
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
