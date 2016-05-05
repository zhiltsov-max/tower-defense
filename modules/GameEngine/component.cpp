#include "component.h"



namespace GE {


std::ostream& operator <<(std::ostream& os, const ComponentIDs& id) {
    return os << static_cast<TComponentID>(id);
}

TComponent::TComponent(const TComponent::ID& id) :
    id(id)
{}

const TComponent::ID& TComponent::GetID() const {
    return id;
}


} //namespace GE
