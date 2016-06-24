#ifndef COMPONENT_REGISTRY_H
#define COMPONENT_REGISTRY_H

#include "GameEngine/component.h"
#include "GameEngine/registry.h"


namespace GE {

struct TComponentCreateArgs
{
    virtual ~TComponentCreateArgs() = default;
};

using TComponentCreate =
    std::unique_ptr<TComponent> (*)(const TComponentCreateArgs*);

using TComponentRegistry = TRegistry< TComponentCreate, TComponent::ID >;

} //namespace GE

#endif // COMPONENT_REGISTRY_H
