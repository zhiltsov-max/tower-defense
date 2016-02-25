#ifndef COMPONENT_H
#define COMPONENT_H

#include "Core/core.h"
#include "engine_message.h"



class TComponentSystem;

class TComponent /*Abstract*/
{
public:
    using ID = uint;


    virtual ~TComponent() = default;

    virtual const ID& GetID() const final;

    virtual void Update() = 0;
    virtual void HandleMessage(const TMessage& message) = 0;

    /*
    Subscribes this component for all needed messages.
    */
    virtual void Subscribe(TComponentSystem* system) = 0;

    /*
    Unsibscribes this component from all messages.
    */
    virtual void Unsubscribe(TComponentSystem* system) = 0;

protected:
    TComponent(uint id) : id(id) {}

private:
    const ID& id;
};


template< class Component >
struct ComponentID;


#endif // COMPONENT_H
