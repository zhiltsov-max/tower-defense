#include "engine_message.h"



std::ostream& operator <<(std::ostream& os, const MessageID& id) {
    return os << static_cast<TMessageID>(id);
}

TMessage::TMessage(const ID& id) :
    id(id)
{}

const TMessage::ID& TMessage::GetID() const {
    return id;
}
