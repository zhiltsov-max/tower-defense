#include "component_system_movement.h"


namespace GE {

void CSMovementSystem::Update(const TTime& step, Context& context) {
    for (auto& component : components) {
        static_cast<CMovementComponent*>(component.get())->Update(step,
            context);
    }
}

CMovementComponent::CMovementComponent(const TComponent::ID& id) :
    TComponent(id)
{}

} //namespace GE
