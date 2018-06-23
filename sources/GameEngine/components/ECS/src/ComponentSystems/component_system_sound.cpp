#include "component_system_sound.h"


GE_BEGIN_ENGINE_NAMESPACE

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

GE_END_ENGINE_NAMESPACE
