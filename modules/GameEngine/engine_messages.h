#ifndef ENGINE_MESSAGES_H
#define ENGINE_MESSAGES_H

#include "engine_message.h"



enum class MessageID : uint {
    _min = 0,

    Undefined = 0,
    SystemEvent,

    _count // keep it last
};


class TMessage_Undefined : public TMessage
{
public:
    TMessage_Undefined() :
        TMessage(MessageID::Undefined)
    {}
};

class TMessage_SystemEvent : public TMessage
{
public:
    TMessage_SystemEvent(const sf::Event& event) :
        TMessage(MessageID::SystemEvent),
        event(event)
    {}

    virtual ~TMessage_SystemEvent() = default;

    const sf::Event& GetEvent() const {
        return event;
    }

private:
    const sf::Event& event;
};


#endif // ENGINE_MESSAGES_H
