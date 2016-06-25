#include "component_system_input.h"


namespace GE {

void CSInputSystem::Update(const TTime& step, Context& context) {
    for (auto& component : components) {
        static_cast<CInputComponent*>(component.get())->Update(context);
    }

    UNUSED(step);
}

CInputComponent::CInputComponent(const TComponent::ID& id) :
    TComponent(id)
{}

} //namespace GE
