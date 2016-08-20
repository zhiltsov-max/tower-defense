#include "component_system_movement.h"


namespace GE {

void CSMovementSystem::Update(const TTime& step, Context& context) {
    // TODO: ...
}

void CSMovementSystem::HandleMessage(const TMessage& message,
    const TComponentHandle& sender, Context& context)
{
    // TODO: ...
}


CMovementComponent::CMovementComponent(const TComponent::ID& id) :
    TComponent(id)
{}

} // namespace GE
