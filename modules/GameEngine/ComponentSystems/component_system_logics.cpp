#include "component_system_logics.h"


namespace GE {

void CSLogicsSystem::Update(const TTime& step, Context& context) {
    for (auto& component : components) {
        static_cast<CLogicsComponent*>(component.get())->Update(step, context);
    }
}

CLogicsComponent::CLogicsComponent(const TComponent::ID& id) :
    TComponent(id)
{}

} //namespace GE
