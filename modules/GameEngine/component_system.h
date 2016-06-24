#ifndef COMPONENT_SYSTEM_H
#define COMPONENT_SYSTEM_H

#include "GameEngine/engine_core.h"
#include "GameEngine/component.h"
#include "GameEngine/component_registry.h"
#include "GameEngine/component_system.h"
#include "GameEngine/engine_message.h"


namespace GE {

class TComponentSystem
{
public:
    using Message = TMessage;
    using Component = TComponent;
    using Handle = size_t;
    static const Handle HandleUndefined;

    virtual ~TComponentSystem() = default;

    const Handle CreateComponent(const TComponent::ID& typeID,
        const TComponentCreateArgs* args = nullptr);

    void RemoveComponent(const Handle& componentHandle);
    Component* GetComponent(const Handle& handle);

    void SetRegistry(TComponentRegistry* instance);

    virtual void Update(const TTime& step) = 0;

    virtual void Subscribe(Component* component, const TMessage::ID& id);
    virtual void Unsubscribe(Component* component, const TMessage::ID& id);

    virtual void HandleMessage(const Message& message);

protected:
    using PComponent = std::unique_ptr<Component>;
    vector<PComponent> components;

    using PComponentRegistry = TComponentRegistry*;
    PComponentRegistry componentRegistry;

    using Listener = Component*;
    using Listeners = std::map< Message::ID, list<Listener> >;
    Listeners listeners;
};

} //namespace GE

#endif // COMPONENT_SYSTEM_H
