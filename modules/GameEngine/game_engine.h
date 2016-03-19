#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "Core/core.h"
#include "GameEngine/engine_core.h"
#include "component_registry.h"
#include "component_systems.h"
#include "script_engine.h"



class TMessage;

class TGameEngine
{
public:
    using ScriptEngine = TScriptEngine;
    using ComponentSystems = TComponentSystems;
    using ComponentRegistry = TComponentRegistry;
    using Message = TMessage;


    TGameEngine();

    void Update(const TTime& step);
    void Draw(Graphics::TRenderTarget& target);
    void SendMessage(const Message& message);

    const ScriptEngine& GetScriptEngine() const;
    ScriptEngine& GetScriptEngine();

    const ComponentRegistry& GetComponentRegistry() const;
    ComponentRegistry& GetComponentRegistry();

    const ComponentSystems& GetComponentSystems() const;
    ComponentSystems& GetComponentSystems();

protected:
    ComponentRegistry componentRegistry;
    ComponentSystems componentSystems;

    ScriptEngine scriptEngine;
};

#endif // GAME_ENGINE_H
