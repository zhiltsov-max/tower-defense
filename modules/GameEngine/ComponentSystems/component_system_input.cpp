#include "component_system_input.h"


namespace GE {

void CSInputSystem::Update(const TTime& step) {
    for (auto& component : components) {
        static_cast<CInputComponent*>(component.get())->Update();
    }
}

CInputComponent::CInputComponent(const TComponent::ID& id) :
    TComponent(id)
{}

} //namespace GE
