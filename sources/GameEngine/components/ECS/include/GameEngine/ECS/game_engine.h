#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "GameEngine/Utility/core.h"
#include "GameEngine/ECS/engine_core.h"
#include "GameEngine/ECS/component_systems_manager.h"
#include "GameEngine/ECS/message_system.h"
#include "GameEngine/ECS/script_engine.h"
#include "GameEngine/ECS/game_engine_context.h"


namespace GE {

class TMessage;

class TGameEngine
{
public:
    using ScriptEngine = TScriptEngine;
    using ComponentSystemsManager = TComponentSystemsManager;
    using ComponentHandle = TComponentHandle;
    using Message = TMessage;
    using MessageSystem = TMessageSystem;
    using Context = TGameEngineContext;

    TGameEngine();

    void Update(const TTime& step, Context& context);
    void SendMessage(const Message& message, Context& context,
        const ComponentHandle& sender = ComponentHandle::Undefined);

    const ScriptEngine& GetScriptEngine() const;
    ScriptEngine& GetScriptEngine();

    const ComponentSystemsManager& GetComponentSystemsManager() const;
    ComponentSystemsManager& GetComponentSystemsManager();

    const MessageSystem& GetMessageSystem() const;
    MessageSystem& GetMessageSystem();

protected:
    ComponentSystemsManager componentSystemsManager;
    MessageSystem messageSystem;
    ScriptEngine scriptEngine;
};

} // namespace GE

#endif // GAME_ENGINE_H
