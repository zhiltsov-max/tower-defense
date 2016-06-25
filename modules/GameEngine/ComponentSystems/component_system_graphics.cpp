#include "component_system_graphics.h"


namespace GE {

void CSGraphicsSystem::Update(const TTime& step, Context& context) {
    //TODO: implementation
}

void CSGraphicsSystem::Draw(Graphics::TRenderTarget& target) {
    for (auto& component : components) {
        static_cast<CGraphicsComponent*>(component.get())->Draw(target, scene);
    }
}

void CSGraphicsSystem::SetScene(TScene* instance) {
    scene = instance;
}

CGraphicsComponent::CGraphicsComponent(const TComponent::ID& id) :
    TComponent(id)
{}

} // namespace GE
