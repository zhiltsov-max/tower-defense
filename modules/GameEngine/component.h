#ifndef COMPONENT_H
#define COMPONENT_H

#include "Core/core.h"
#include "GameEngine/engine_message.h"
#include "GameEngine/game_engine_context.h"


namespace GE {

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

    /*
    Handles given message.
    */
    virtual void HandleMessage(const TMessage& message, Context& context) = 0;

    /*
    List all needed messages.
    */
    virtual forward_list<TMessage::ID> GetAcceptedMessages() const = 0;

protected:
    TComponent(const ID& id);

private:
    const ID id;
};

template< class Component >
struct ComponentID;

} // namespace GE

#endif // COMPONENT_H
