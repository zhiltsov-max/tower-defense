#ifndef MESSAGE_SYSTEM_H
#define MESSAGE_SYSTEM_H

#include <functional>
#include "GameEngine/ECS/engine_message.h"
#include "GameEngine/ECS/component_systems_manager.h"


GE_BEGIN_ENGINE_NAMESPACE

class TMessageSystem
{
public:
    using ComponentHandle = TComponentHandle;
    using EngineContext = TGameEngineContext;
    using Message = TMessage;
    using MessageCallback = std::function<
        void (const ComponentHandle& reciever, const ComponentHandle& sender,
            const Message& message, EngineContext& context)
    >;

    TMessageSystem();

    void Subscribe(const ComponentHandle& source,
        const ComponentHandle& listener, const MessageID& messageId,
        const MessageCallback& callback);

    void Unsubscribe(const ComponentHandle& listener);
    void Unsubscribe(const ComponentHandle& source,
        const ComponentHandle& listener);
    void Unsubscribe(const ComponentHandle& source,
        const ComponentHandle& listener, const MessageID& messageId);
    void UnsubscribeFrom(const ComponentHandle& source);

    void ClearSubscriptions();

    void SendMessage(const Message& message, EngineContext& context,
        const ComponentHandle& sender = ComponentHandle::Undefined);

    void SetComponentSystemsManager(TComponentSystemsManager* instance);

protected:
    using Subscription = std::pair<MessageID, MessageCallback>;
    using Subscriptions = vector<Subscription>;
    using Listener = std::pair<ComponentHandle, Subscriptions>;
    using Listeners = vector<Listener>;
    using RoutingTable = map<ComponentHandle, Listeners>;
    RoutingTable routingTable;

    Listeners::const_iterator FindListener(const Listeners& listeners,
        const ComponentHandle& listener) const;
    Listeners::iterator FindListener(Listeners& listeners,
        const ComponentHandle& listener);

    Subscriptions::const_iterator FindSubscription(
        const Subscriptions& subscriptions, const MessageID& messageId) const;
    Subscriptions::iterator FindSubscription(
        Subscriptions& subscriptions, const MessageID& messageId);

    using PComponentSystemsManager = TComponentSystemsManager *;
    PComponentSystemsManager componentSystemsManager;
};

GE_END_ENGINE_NAMESPACE

#endif // MESSAGE_SYSTEM_H
