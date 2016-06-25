#ifndef COMPONENT_H
#define COMPONENT_H

#include "Core/core.h"
#include "GameEngine/game_engine_context.h"


namespace GE {

class TMessage;

class TComponentSystem;
using TComponentID = uint;
enum class ComponentIDs : TComponentID;

std::ostream& operator << (std::ostream& os, const ComponentIDs& id);

class TComponent /*Abstract*/
{
public:
    using ID = ComponentIDs;
    using Context = TGameEngineContext;

    virtual ~TComponent() = default;

    virtual const ID& GetID() const final;

    virtual void HandleMessage(const TMessage& message, Context& context) = 0;

    /*
    Subscribes this component for all needed messages.
    */
    virtual void Subscribe(TComponentSystem& system) = 0;

    /*
    Unsibscribes this component from all messages.
    */
    virtual void Unsubscribe(TComponentSystem& system) = 0;

protected:
    TComponent(const ID& id);

private:
    const ID id;
};

template< class Component >
struct ComponentID;

} // namespace GE

#endif // COMPONENT_H
