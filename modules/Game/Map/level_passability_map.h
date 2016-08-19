#ifndef LEVEL_PASSABILITY_MAP_H
#define LEVEL_PASSABILITY_MAP_H

#include "Core/core.h"
#include "GameEngine/component.h"
#include "GameEngine/component_registry.h"
#include "Game/Components/td_components_list.h"
#include "Game/ComponentSystems/td_component_systems_list.h"
#include "Game/Map/level_tile_map_tileset.h"
#include "Game/Map/level_tile_map_tileset_registry.h"


TD_DECLARE_COMPONENT_CLASS(CLevelPassabilityMap,
    GE::ComponentIDs::LevelPassabilityMap, GE::ComponentSystem::Map)


namespace TD {

struct CLevelPassabilityMap : GE::TComponent
{
    using Size = Vec2ui;
    using Passability = uchar;
    using PassabilityMap = vector<Passability>;
    struct Parameters;

    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args = nullptr);

    CLevelPassabilityMap(const Parameters* source);
	
    std::array<PassabilityMap, static_cast<TAltitude>(Altitude::_count)> maps;
    Size size;

private:
    using parent_type = GE::CDataComponent;
};

struct CLevelPassabilityMap::Parameters : GE::TComponentCreateArgs
{
    Size size;
};

} // namespace TD

#endif // LEVEL_PASSABILITY_MAP_H
