#ifndef MESSAGE_SYSTEM_H
#define MESSAGE_SYSTEM_H

#include <functional>
#include "GameEngine/engine_message.h"
#include "GameEngine/component_systems_manager.h"


namespace GE {

class TMessageSystem
{
public:
    using ComponentHandle = TComponentHandle;
    using Context = TGameEngineContext;
    using Message = TMessage;
    using MessageCallback =
        std::function<void (const ComponentHandle&, const Message&, Context&)>;

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

    void SendMessage(const Message& message, Context& context,
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

} // namespace GE

#endif // MESSAGE_SYSTEM_H
