#ifndef ENGINE_MESSAGES_H
#define ENGINE_MESSAGES_H

#include "GameEngine/ECS/engine_message.h"
#include "Application/application.h"


GE_BEGIN_ENGINE_NAMESPACE

enum class DefaultMessageID : TMessageID {
    _min = 0,

    Undefined = 0,
    SystemEvent,

    _max,
    _count = _max - _min
};

class TMessage_SystemEvent : public TMessage
{
public:
    using Event = TApplication::Event;

    TMessage_SystemEvent(const Event& event);
    virtual ~TMessage_SystemEvent() = default;

    const Event& GetEvent() const;

private:
    const Event& event;
};

} //namespavce GE

#endif // ENGINE_MESSAGES_H
