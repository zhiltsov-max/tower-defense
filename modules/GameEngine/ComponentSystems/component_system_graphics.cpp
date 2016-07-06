#include "component_system_graphics.h"


namespace GE {

void CSGraphicsSystem::Update(const TTime& step, Context& context) {
    for (auto& component : components) {
        static_cast<CGraphicsComponent*>(component.get())->Update(step,
            context);
    }
}

void CSGraphicsSystem::Render(Graphics::TRenderTarget& target) {
    for (auto& component : components) {
        static_cast<CGraphicsComponent*>(component.get())->Render(target);
    }
}

void CSGraphicsSystem::SetScene(TScene* instance) {
    scene = instance;
}


CGraphicsComponent::CGraphicsComponent(const TComponent::ID& id) :
    TComponent(id)
{}

void CGraphicsComponent::Update(const TTime& step, Context& context) {
    /*none*/
}

} // namespace GE
