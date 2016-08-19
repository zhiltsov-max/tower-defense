#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include "GameEngine/component.h"
#include "GameEngine/component_registry.h"
#include "Game/Components/td_components_list.h"
#include "Game/ComponentSystems/td_component_systems_list.h"


TD_DECLARE_COMPONENT_CLASS(CPosition2d,
    GE::ComponentIDs::Position2d, GE::ComponentSystem::Movement)

namespace TD {

struct CPosition2d : GE::TComponent
{
    using Position = Point2f;
    using Rotation = float;
    struct Parameters;

    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args = nullptr);

    CPosition2d(const Parameters* args = nullptr);

    Position position;
    Rotation rotation;

private:
    using parent_type = GE::TComponent;
};

struct CPosition2d::Parameters : GE::TComponentCreateArgs
{
    Point2f position;
    float rotation;
};

} // namespace TD

#endif // POSITION_COMPONENT_H
