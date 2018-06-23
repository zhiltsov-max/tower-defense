#include "GameEngine/ECS/component.h"


GE_BEGIN_ENGINE_NAMESPACE


std::ostream& operator <<(std::ostream& os, const ComponentIDs& id) {
    return os << static_cast<TComponentID>(id);
}

TComponent::TComponent(const TComponent::ID& id) :
    id(id)
{}

const TComponent::ID& TComponent::GetID() const {
    return id;
}

GE_END_ENGINE_NAMESPACE
