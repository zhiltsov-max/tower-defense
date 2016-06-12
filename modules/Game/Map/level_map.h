#ifndef LEVEL_MAP_H
#define LEVEL_MAP_H

#include "Core/core.h"
#include "Game/Level/level_scene.h"
#include "Game/Map/level_node_map.h"
#include "Game/Map/level_passability_map.h"
#include "Game/Map/level_tile_map.h"


namespace TD {

struct TLevelInfoMap
{
    using Size = Vec2ui;

    Size size;
    TLevelInfoTileMap tileMap;
    TNodeMapParameters nodeMap;
    TLevelScene* scene;
};

class TLevelMap
{
public:
    using Size = TLevelInfoMap::Size;

    TLevelMap(const TLevelInfoMap& source = TLevelInfoMap());
			
    const CLevelTileMap& GetTileMap() const;
    CLevelTileMap& GetTileMap();
	
    const CLevelNodeMap& GetNodeMap() const;
    CLevelNodeMap& GetNodeMap();

    const CLevelPassabilityMap& GetPassabilityMap() const;
    CLevelPassabilityMap& GetPassabilityMap();

private:
    static const string DEFAULT_OBJECT_NAME;

    using ObjectHandle = TLevelScene::ObjectHandle;
    ObjectHandle sceneObjectHandle;

    using ComponentHandle = TLevelScene::ComponentHandle;
    ComponentHandle tileMapHandle;
    ComponentHandle nodeMapHandle;
    ComponentHandle passabilityMapHandle;

    TLevelScene* scene;
};

} // namespace TD

#endif //LEVEL_MAP_H
