#ifndef ENGINE_MESSAGE_H
#define ENGINE_MESSAGE_H

#include "GameEngine/utility.h"
#if defined(SendMessage)
    #undef SendMessage
#endif // SendMessage


GE_BEGIN_ENGINE_NAMESPACE

using TMessageID = uint;
enum class MessageID : TMessageID;

std::ostream& operator << (std::ostream& os, const MessageID& id);

class TMessage
{
public:
    using ID = MessageID;

    virtual ~TMessage() = default;

    const ID& GetID() const;

protected:
    TMessage(const ID& id);

private:
    const ID id;
};

GE_END_ENGINE_NAMESPACE

#endif // ENGINE_MESSAGE_H
