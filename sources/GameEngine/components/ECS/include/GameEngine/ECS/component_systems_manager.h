#ifndef COMPONENT_SYSTEMS_MANAGER_H
#define COMPONENT_SYSTEMS_MANAGER_H

#include "GameEngine/ECS/engine_message.h"
#include "GameEngine/ECS/component_system.h"
#include "GameEngine/ECS/component_system_type.h"
#include "GameEngine/ECS/component_registry.h"
#include "GameEngine/ECS/game_engine_context.h"


namespace GE {

class TComponentHandle
{
public:
    using Handle = TComponentSystem::Handle;

    static const TComponentHandle Undefined;

    TComponentHandle();
    TComponentHandle(const Handle& handle, const ComponentSystem& system);

    operator Handle() const;
    const ComponentSystem& GetSystem() const;
    const Handle& GetValue() const;

    bool operator == (const TComponentHandle& other) const;
    bool operator != (const TComponentHandle& other) const;

    bool IsNull() const;

private:
    Handle value;
    ComponentSystem system;
};

class TComponentSystemsManager
{
public:
    using Message = TMessage;
    using ID = ComponentSystem;
    using Context = TGameEngineContext;
    using ComponentRegistry = TComponentRegistry;
    using PSystem = std::unique_ptr<TComponentSystem>;
    using ComponentHandle = TComponentHandle;

    void Update(const TTime& step, Context& context);

    TComponentSystem* AddSystem(const ID& id, PSystem&& system);

    template<class C>
    C* AddSystem(const ID& id);

    bool HasSystem(const ID& id) const;
    void RemoveSystem(const ID& id);

    const TComponentSystem* FindSystem(const ID& id) const;
    TComponentSystem* FindSystem(const ID& id);

    void SendMessage(const Message& message, Context& context,
        const ComponentHandle& sender = ComponentHandle::Undefined);

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

} // namespace GE

#endif // COMPONENT_SYSTEMS_MANAGER_H
