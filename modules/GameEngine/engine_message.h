#ifndef ENGINE_MESSAGE_H
#define ENGINE_MESSAGE_H

#include "Core/core.h"
#if defined(SendMessage)
    #undef SendMessage
#endif // SendMessage



class TMessage
{
public:
    typedef uint ID;


    virtual ~TMessage() = default;

    virtual const ID& GetID() const final;

protected:
    TMessage(const ID& id);

private:
    const ID id;
};


#endif // ENGINE_MESSAGE_H
