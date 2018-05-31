#include "component_system_sound.h"


namespace GE {

void CSSoundSystem::Update(const TTime& step, Context& context) {
    // TODO: implementation
}

void CSSoundSystem::HandleMessage(const TMessage& message,
    const TComponentHandle& sender, Context& context)
{
    // TODO: ...
}

CSoundComponent::CSoundComponent(const TComponent::ID& id) :
    TComponent(id)
{}

} // namespace GE
