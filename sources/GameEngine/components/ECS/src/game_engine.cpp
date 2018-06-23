#include "GameEngine/ECS/game_engine.h"
#include "GameEngine/ECS/engine_message.h"


GE_BEGIN_ENGINE_NAMESPACE

TGameEngine::TGameEngine() :
    componentSystemsManager(),
    messageSystem(),
    scriptEngine()
{
    messageSystem.SetComponentSystemsManager(&componentSystemsManager);
}

void TGameEngine::Update(const TTime& step, Context& context) {
    componentSystemsManager.Update(step, context);
}

void TGameEngine::SendMessage(const Message& message, Context& context,
    const ComponentHandle& sender)
{
    messageSystem.SendMessage(message, context, sender);
    componentSystemsManager.SendMessage(message, context, sender);
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
    return componentSystemsManager;
}

TGameEngine::ComponentSystemsManager&
TGameEngine::GetComponentSystemsManager() {
    return componentSystemsManager;
}

const TGameEngine::MessageSystem& TGameEngine::GetMessageSystem() const {
    return messageSystem;
}

TGameEngine::MessageSystem& TGameEngine::GetMessageSystem() {
    return messageSystem;
}

GE_END_ENGINE_NAMESPACE
