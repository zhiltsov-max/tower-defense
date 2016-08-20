#include "component_system_logics.h"


namespace GE {

void CSLogicsSystem::Update(const TTime& step, Context& context) {
    // TODO: ...
}

void CSLogicsSystem::HandleMessage(const TMessage& message,
    const TComponentHandle& sender, Context& context)
{
    // TODO: ...
}

CLogicsComponent::CLogicsComponent(const TComponent::ID& id) :
    TComponent(id)
{}

} // namespace GE
