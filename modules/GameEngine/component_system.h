#ifndef COMPONENT_SYSTEM_H
#define COMPONENT_SYSTEM_H

#include <functional>
#include "GameEngine/engine_core.h"
#include "GameEngine/engine_message.h"
#include "GameEngine/component.h"
#include "GameEngine/component_registry.h"
#include "GameEngine/game_engine_context.h"


namespace GE {

class TComponentSystem /*Abstract*/
{
public:
    using Handle = size_t;
    static const Handle HandleUndefined;
    using Component = TComponent;
    using Context = TGameEngineContext;
    using Message = TMessage;
    using MessageCallback =
        std::function<void (const Handle&, const Message*, Context&)>;

    TComponentSystem();
    virtual ~TComponentSystem() = default;

    Handle CreateComponent(const TComponent::ID& typeID,
        const TComponentCreateArgs* args = nullptr);

    bool HasComponent(const Handle& handle) const;

    void RemoveComponent(const Handle& handle);

    const Component* GetComponent(const Handle& handle) const;
    Component* GetComponent(const Handle& handle);

    bool IsEmpty() const;
    void Clear();

    virtual void Update(const TTime& step, Context& context) = 0;

    void Subscribe(const Handle& source, const Handle& listener,
        const MessageCallback& callback);
    void Unsubscribe(const Handle& source, const Handle& listener);
    void Unsubscribe(const Handle& listener);
    void UnsubscribeFrom(const Handle& source);

    virtual void HandleMessage(const Message& message, Context& context,
        const Handle& source = HandleUndefined);

    void SetComponentRegistry(TComponentRegistry* instance);

protected:
    using ComponentRegistry = TComponentRegistry;
    using PComponentRegistry = ComponentRegistry *;
    PComponentRegistry componentRegistry;

    using PComponent = std::unique_ptr<Component>;
    vector<PComponent> components;

    struct Listener
    {
        Handle handle;
        MessageCallback callback;

        Listener(const Handle& handle = HandleUndefined,
            const MessageCallback& callback = MessageCallback());
        bool operator == (const Handle& otherHandle) const;
        bool operator != (const Handle& otherHandle) const;
    };
    using Listeners = std::map< Handle, vector<Listener> >;
    Listeners listeners;
};

} //namespace GE

#endif // COMPONENT_SYSTEM_H
