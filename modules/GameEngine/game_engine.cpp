#include "game_engine.h"
#include "GameEngine/engine_message.h"


namespace GE {

TGameEngine::TGameEngine() :
    componentSystems(this)
{}

void TGameEngine::Update(const TTime& step) {
    componentSystems.input.Update(step);
    componentSystems.logics.Update(step);
    componentSystems.movement.Update(step);
    componentSystems.ui.Update(step);
    componentSystems.graphics.Update(step);
    componentSystems.sound.Update(step);

    componentSystems.sound.Play(step);
}

void TGameEngine::Draw(Graphics::TRenderTarget& target) {
    componentSystems.graphics.Draw(target);
    componentSystems.ui.Draw(target);
}

void TGameEngine::SendMessage(const Message& message) {
    for (auto& system : componentSystems.systems) {
        system->HandleMessage(message);
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
