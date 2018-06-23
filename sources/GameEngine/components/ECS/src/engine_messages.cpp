#include "engine_messages.h"



GE_BEGIN_ENGINE_NAMESPACE


TMessage_SystemEvent::TMessage_SystemEvent(const Event& event) :
    TMessage(static_cast<TMessage::ID>(static_cast<TMessageID>(
        DefaultMessageID::SystemEvent))),
    event(event)
{}

const TMessage_SystemEvent::Event&
TMessage_SystemEvent::GetEvent() const {
    return event;
}


GE_END_ENGINE_NAMESPACE
