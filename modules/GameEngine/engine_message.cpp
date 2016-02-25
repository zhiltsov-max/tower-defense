#include "engine_message.h"



TMessage::TMessage(const ID& id) :
    id(id)
{}

const TMessage::ID& TMessage::GetID() const {
    return id;
}
