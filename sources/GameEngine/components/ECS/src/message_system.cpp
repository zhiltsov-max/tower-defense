#include "GameEngine/ECS/message_system.h"


namespace GE {

TMessageSystem::TMessageSystem() :
    routingTable(),
    componentSystemsManager(nullptr)
{}

void TMessageSystem::ClearSubscriptions() {
    routingTable.clear();
}

void TMessageSystem::Subscribe(const ComponentHandle& source,
    const ComponentHandle& listener, const MessageID& messageId,
    const MessageCallback& callback)
{
    ASSERT(static_cast<bool>(callback) != false, "Wrong callback function.");
    ASSERT(source != listener, "Can not subscribe component to himself.");

    auto& listeners = routingTable[source];
    const auto it = FindListener(listeners, listener);
    if (it != listeners.end()) {
        it->second.emplace_back(messageId, callback);
    } else {
        listeners.emplace_back(listener,
            Subscriptions{ Subscription(messageId, callback) });
    }
}

void
TMessageSystem::Unsubscribe(const ComponentHandle& listener) {
    for (auto it = routingTable.begin(); it != routingTable.end();) {
        const auto listenerIt = FindListener(it->second, listener);
        if (listenerIt != it->second.end()) {
            it->second.erase(listenerIt);
        }
        if (it->second.empty() == true) {
            it = routingTable.erase(it);
        } else {
            ++it;
        }
    }
}

void
TMessageSystem::Unsubscribe(const ComponentHandle& source,
    const ComponentHandle& listener)
{
    auto listenersIt = routingTable.find(source);
    if (listenersIt == routingTable.end()) {
        return;
    }

    const auto listenerIt = FindListener(listenersIt->second, listener);
    if (listenerIt != listenersIt->second.end()) {
        listenersIt->second.erase(listenerIt);
    }

    if (listenersIt->second.empty() == true) {
        routingTable.erase(listenersIt);
    }
}

void TMessageSystem::Unsubscribe(const ComponentHandle& source,
    const ComponentHandle& listener, const MessageID& messageId)
{
    auto listenersIt = routingTable.find(source);
    if (listenersIt == routingTable.end()) {
        return;
    }

    auto listenerIt = FindListener(listenersIt->second, listener);
    if (listenerIt == listenersIt->second.end()) {
        return;
    }

    auto& subscriptions = listenerIt->second;
    const auto subscritpionIt =
        FindSubscription(subscriptions, messageId);
    if (subscritpionIt != subscriptions.end()) {
        subscriptions.erase(subscritpionIt);
    }

    if (subscriptions.empty() == true) {
        listenersIt->second.erase(listenerIt);
    }

    if (listenersIt->second.empty() == true) {
        routingTable.erase(listenersIt);
    }
}

void
TMessageSystem::UnsubscribeFrom(const ComponentHandle& source) {
    routingTable.erase(source);
}

void TMessageSystem::SendMessage(const Message& message, EngineContext& context,
    const ComponentHandle& sender)
{
    auto it = routingTable.find(sender);
    if (it == routingTable.end()) {
        return;
    }

    const auto& listeners = it->second;
    for (const auto& listener : listeners) {
        const auto& subscriptions = listener.second;
        const auto subIt = FindSubscription(subscriptions, message.GetID());
        if (subIt != subscriptions.end()) {
            const auto& listenerHandle = listener.first;
            const auto& callback = subIt->second;
            callback(listenerHandle, sender, message, context);
        }
    }
}

void TMessageSystem::SetComponentSystemsManager(
    TComponentSystemsManager* instance)
{
    componentSystemsManager = instance;
}

TMessageSystem::Listeners::const_iterator
TMessageSystem::FindListener(const Listeners& listeners,
    const ComponentHandle& listener) const
{
    auto it = listeners.cbegin();
    const auto iend = listeners.cend();
    while (it != iend) {
        if (it->first != listener) {
            ++it;
        } else {
            break;
        }
    }
    return it;
}

TMessageSystem::Listeners::iterator
TMessageSystem::FindListener(Listeners& listeners,
    const ComponentHandle& listener)
{
    auto it = listeners.begin();
    const auto iend = listeners.end();
    while (it != iend) {
        if (it->first != listener) {
            ++it;
        } else {
            break;
        }
    }
    return it;
}

TMessageSystem::Subscriptions::const_iterator
TMessageSystem::FindSubscription(const Subscriptions& subscriptions,
    const MessageID& messageId) const
{
    auto it = subscriptions.cbegin();
    const auto iend = subscriptions.cend();
    while (it != iend) {
        if (it->first != messageId) {
            ++it;
        } else {
            break;
        }
    }
    return it;
}

TMessageSystem::Subscriptions::iterator
TMessageSystem::FindSubscription(Subscriptions& subscriptions,
    const MessageID& messageId)
{
    auto it = subscriptions.begin();
    const auto iend = subscriptions.end();
    while (it != iend) {
        if (it->first != messageId) {
            ++it;
        } else {
            break;
        }
    }
    return it;
}

} // namespace GE
