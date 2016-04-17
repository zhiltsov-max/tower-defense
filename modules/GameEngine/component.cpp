#include "component.h"



TComponent::TComponent(const TComponent::ID& id) :
    id(id)
{}

const TComponent::ID& TComponent::GetID() const {
    return id;
}
