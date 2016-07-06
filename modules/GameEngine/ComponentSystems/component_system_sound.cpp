#include "component_system_sound.h"


namespace GE {

void CSSoundSystem::Update(const TTime& step, Context& context) {
    //TODO: implementation
    THROW("Not impleneted yet");
}

CSoundComponent::CSoundComponent(const TComponent::ID& id) :
    TComponent(id)
{}

} // namespace GE
