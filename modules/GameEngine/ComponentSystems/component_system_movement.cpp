#include "component_system_movement.h"



void CSMovementSystem::Update(const TTime& step) {
    for (PComponent& component : components) {
        component->Update();
    }
}


CMovementComponent::CMovementComponent(const TComponent::ID& id) :
    TComponent(id)
{}
