#ifndef LEVEL_PASSABILITY_MAP_H
#define LEVEL_PASSABILITY_MAP_H

#include "Core/core.h"
#include "Game/Components/components_list.h"
#include "GameEngine/component_systems.h"
#include "Game/Map/level_tile_map_tileset.h"
#include "Game/Map/level_tile_map_tileset_registry.h"


namespace TD {

class CLevelPassabilityMap :
    public GE::CDataComponent
{
public:
    using Size = Vec2ui;
    using Passability = uchar;
    using PassabilityMap = vector<Passability>;
    struct Parameters;

    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args = nullptr);

    CLevelPassabilityMap(const Parameters* source);
	
    const PassabilityMap& GetMap(const Altitude& altitude);
    const Size& GetSize() const;

private:
    using parent_type = GE::CDataComponent;

    std::array<PassabilityMap, static_cast<TAltitude>(Altitude::_count)> maps;
    Size size;
};

struct CLevelPassabilityMap::Parameters : GE::TComponentCreateArgs
{
    Size size;
};

} // namespace TD


namespace GE {

template<>
struct ComponentID<TD::CLevelPassabilityMap>
{
    static const ComponentIDs value;
};

} // namespace GE

#endif // LEVEL_PASSABILITY_MAP_H
