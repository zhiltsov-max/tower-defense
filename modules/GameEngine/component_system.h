#ifndef COMPONENT_SYSTEM_H
#define COMPONENT_SYSTEM_H

#include "GameEngine/engine_core.h"
#include "GameEngine/engine_message.h"
#include "GameEngine/component.h"
#include "GameEngine/component_registry.h"
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

    bool HasComponent(const Handle& handle) const;

    void RemoveComponent(const Handle& handle);
    Component* GetComponent(const Handle& handle);

    bool IsEmpty() const;
    void Clear();

    virtual void Update(const TTime& step, Context& context) = 0;

    virtual void Subscribe(const Handle& handle, const TMessage::ID& id);
    virtual void Unsubscribe(const Handle& handle, const TMessage::ID& id);

    template < typename FwdIt >
    void Subscribe(const Handle& handle,
        const FwdIt& begin, const FwdIt& end);
    template < typename FwdIt >
    void Unsubscribe(const Handle& handle,
        const FwdIt& begin, const FwdIt& end);

    virtual void HandleMessage(const Message& message, Context& context);

    void SetComponentRegistry(TComponentRegistry* instance);

protected:
    using ComponentRegistry = TComponentRegistry;
    using PComponentRegistry = ComponentRegistry *;
    PComponentRegistry componentRegistry;

    using PComponent = std::unique_ptr<Component>;
    vector<PComponent> components;

    using Listener = Handle;
    using Listeners = std::map< Message::ID, vector<Listener> >;
    Listeners listeners;
};


template<typename FwdIt>
void TComponentSystem::Subscribe(const TComponentSystem::Handle& handle,
    const FwdIt& begin, const FwdIt& end)
{
    ASSERT(handle < components.size(), "Wrong component handle.");

    auto current = begin;
    while (current != end) {
        Subscribe(handle, *current);
        ++current;
    }
}

template<typename FwdIt>
void TComponentSystem::Unsubscribe(const TComponentSystem::Handle& handle,
    const FwdIt& begin, const FwdIt& end)
{
    ASSERT(handle < components.size(), "Wrong component handle.");

    auto current = begin;
    while (current != end) {
        Unsubscribe(handle, *current);
        ++current;
    }
}

} //namespace GE

#endif // COMPONENT_SYSTEM_H
