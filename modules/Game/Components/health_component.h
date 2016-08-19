#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include "GameEngine/component.h"
#include "GameEngine/component_registry.h"
#include "Game/Components/td_components_list.h"
#include "Game/ComponentSystems/td_component_systems_list.h"


TD_DECLARE_COMPONENT_CLASS(CHealth,
    GE::ComponentIDs::Health, GE::ComponentSystem::Logics)

namespace TD {

struct CHealth : GE::TComponent
{
    using Health = int;
    struct Parameters;

    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args = nullptr);

    CHealth(const Parameters* args = nullptr);

    int actualHealth;
    int maxHealth;

private:
    using parent_type = GE::TComponent;
};

struct CHealth::Parameters : GE::TComponentCreateArgs
{
    Health actualHealth;
    Health maxHealth;
};

} // namespace TD

#endif // HEALTH_COMPONENT_H
