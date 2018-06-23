#include "component_system_movement.h"


GE_BEGIN_ENGINE_NAMESPACE

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

GE_END_ENGINE_NAMESPACE
