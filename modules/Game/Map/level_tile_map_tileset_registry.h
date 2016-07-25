#ifndef LEVEL_TILE_MAP_TILESET_REGISTRY_H
#define LEVEL_TILE_MAP_TILESET_REGISTRY_H

#include "GameEngine/registry.h"
#include "Game/Map/level_tile_map_tileset.h"


namespace TD {

using TLevelTileMapTilesetRegistry = GE::TRegistry<
    TLevelTileMapTileset, TLevelTileMapTilesetId>;

class TLevelTileMapTilesetRegistryLoader
{
public:
    void SetDataPath(const string& value);

    void Load(const std::set<TLevelTileMapTilesetId>& ids,
        TLevelTileMapTilesetRegistry& registry);

private:
    static const string DEFAULT_DATA_SOURCE_PATH;
    string dataPath;

    void readInfo(std::istream& is, TLevelTileMapTileset& info);
};

} // namespace TD

#endif // LEVEL_TILE_MAP_TILESET_REGISTRY_H
