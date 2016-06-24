#include "component_system_graphics.h"


namespace GE {

void CSGraphicsSystem::Update(const TTime& step) {
    //TODO: implementation
}

void CSGraphicsSystem::Draw(Graphics::TRenderTarget& target) {
    // TODO: graphics subsystem
    THROW("Not implemented yet");
}

CGraphicsComponent::CGraphicsComponent(const TComponent::ID& id) :
    TComponent(id)
{}

} // namespace GE
