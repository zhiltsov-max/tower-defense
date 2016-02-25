#include "component_system_sound.h"



void CSSoundSystem::Update(const TTime& step) {
    for (PComponent& component : components) {
        component->Update();
    }

    UNUSED(step)
}


CSoundComponent::CSoundComponent(const TComponent::ID& id) :
    TComponent(id)
{}
