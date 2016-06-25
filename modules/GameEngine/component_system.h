#ifndef COMPONENT_SYSTEM_H
#define COMPONENT_SYSTEM_H

#include "GameEngine/engine_core.h"
#include "GameEngine/component.h"
#include "GameEngine/component_registry.h"
#include "GameEngine/component_system.h"
#include "GameEngine/engine_message.h"
#include "GameEngine/game_engine_context.h"


namespace GE {

class TComponentSystem /*Abstract*/
{
public:
    using Message = TMessage;
    using Component = TComponent;
    using Context = TGameEngineContext;
    using Handle = size_t;
    static const Handle HandleUndefined;

    virtual ~TComponentSystem() = default;

    Handle CreateComponent(const TComponent::ID& typeID,
        const TComponentCreateArgs* args = nullptr);

    void RemoveComponent(const Handle& componentHandle);
    Component* GetComponent(const Handle& handle);

    virtual void Update(const TTime& step, Context& context) = 0;

    virtual void Subscribe(Component* component, const TMessage::ID& id);
    virtual void Unsubscribe(Component* component, const TMessage::ID& id);

    virtual void HandleMessage(const Message& message, Context& context);

    void SetComponentRegistry(TComponentRegistry* instance);

protected:
    using ComponentRegistry = TComponentRegistry;
    using PComponentRegistry = ComponentRegistry *;
    PComponentRegistry componentRegistry;

    using PComponent = std::unique_ptr<Component>;
    vector<PComponent> components;

    using Listener = Component*;
    using Listeners = std::map< Message::ID, list<Listener> >;
    Listeners listeners;
};

} //namespace GE

#endif // COMPONENT_SYSTEM_H
