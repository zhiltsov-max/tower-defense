#ifndef LEVEL_TILE_MAP_TILESET_H
#define LEVEL_TILE_MAP_TILESET_H

#include "GameEngine/Utility/core.h"


namespace  TD {

using TLevelTileMapTilesetId = ushort;

using TAltitude = uchar;
enum class Altitude : TAltitude {
    _min = 0,

    Underground = 0,
    Water,
    Ground,
    Air,

    _count
};

using TPassWeight = uchar;
enum class PassWeight : TPassWeight {
    _min = 0,

    CanNotPass = 0,
    Min,
    Low,
    Medium,
    Hard,

    _count,
    _max = Hard
};


struct TLevelTileMapTileset
{
    Vec2ui tileSize;

    struct TileProperties
    {
        std::array<bool, static_cast<TAltitude>(Altitude::_count)> passability;
        std::array<PassWeight, static_cast<TAltitude>(Altitude::_count)>
            passWeight;
        bool buildable;
    };
    vector<TileProperties> properties;

    string imageResourceHash;
};

} // namespace TD

#endif // LEVEL_TILE_MAP_TILESET_H
