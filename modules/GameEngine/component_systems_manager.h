#ifndef COMPONENT_SYSTEMS_MANAGER_H
#define COMPONENT_SYSTEMS_MANAGER_H

#include "GameEngine/engine_message.h"
#include "GameEngine/component_system.h"
#include "GameEngine/component_registry.h"
#include "GameEngine/game_engine_context.h"


namespace GE {

class TComponentSystemsManager
{
public:
    using Message = TMessage;
    using ID = ComponentSystem;
    using Context = TGameEngineContext;
    using ComponentRegistry = TComponentRegistry;
    using PSystem = std::unique_ptr<TComponentSystem>;

    void Update(const TTime& step, Context& context);

    TComponentSystem* AddSystem(const ID& id, PSystem&& system);

    template<class C>
    C* AddSystem(const ID& id);

    bool HasSystem(const ID& id) const;
    void RemoveSystem(const ID& id);

    const TComponentSystem* FindSystem(const ID& id) const;
    TComponentSystem* FindSystem(const ID& id);

    void SendMessage(const Message& message, Context& context);

    const ComponentRegistry& GetComponentRegistry() const;
    ComponentRegistry& GetComponentRegistry();

public:
    //TODO: hide implementation
    using Systems = map<ID, PSystem>;
    const Systems& GetSystems() const;
    Systems& GetSystems();

private:
    ComponentRegistry componentRegistry;

    Systems systems;
};

template<class C>
C* TComponentSystemsManager::AddSystem(const ID& id) {
    return dynamic_cast<C*>(AddSystem(id, std::move(PSystem(new C()))));
}

} //namespace GE

#endif // COMPONENT_SYSTEMS_MANAGER_H
