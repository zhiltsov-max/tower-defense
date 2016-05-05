#ifndef ENGINE_MESSAGE_H
#define ENGINE_MESSAGE_H

#include "Core/core.h"
#if defined(SendMessage)
    #undef SendMessage
#endif // SendMessage



namespace GE {


using TMessageID = uint;
enum class MessageID : TMessageID;

std::ostream& operator << (std::ostream& os, const MessageID& id);

class TMessage
{
public:
    typedef MessageID ID;


    virtual ~TMessage() = default;

    virtual const ID& GetID() const final;

protected:
    TMessage(const ID& id);

private:
    const ID id;
};


} //namespace GE

#endif // ENGINE_MESSAGE_H
