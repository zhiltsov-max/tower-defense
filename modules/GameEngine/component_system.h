#ifndef COMPONENT_SYSTEM_H
#define COMPONENT_SYSTEM_H

#include "engine_core.h"
#include "component.h"
#include "component_registry.h"
#include "component_system.h"
#include "engine_message.h"



class TComponentSystem
{
public:
    using Message = TMessage;
    using Component = TComponent;
    using Handle = size_t;
    static constexpr Handle HandleUndefined = (Handle) -1;


    virtual ~TComponentSystem() = default;


    const Handle CreateComponent(const TComponent::ID& typeID,
        const TComponentCreateArgs* args = nullptr);

    void RemoveComponent(const Handle& componentHandle);
    Component* GetComponent(const Handle& handle);

    void SetRegistry(TComponentRegistry* instance);

    virtual void Update(const TTime& step);

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

#endif // COMPONENT_SYSTEM_H
