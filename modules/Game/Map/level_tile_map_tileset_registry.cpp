#include "level_tile_map_tileset_registry.h"
#include <iostream>
#include <fstream>


namespace TD {

void TLevelTileMapTilesetRegistryLoader::Load(
    const std::set<TLevelTileMapTilesetId>& ids,
    TLevelTileMapTilesetRegistry& registry
) {
    if (ids.empty() == true) {
        return;
    }

    std::ifstream source(dataPath);
    if (source.is_open() == false) {
        THROW("Unable to load tileset info: source is not found.");
    }

    std::set<TLevelTileMapTilesetId> remaining_ids;
    for (const auto& id : ids) {
        if (registry.IsRegistered(id) == false) {
            remaining_ids.insert(id);
        }
    }

    while ((data.good()) && (remaining_ids.empty() == false)) {
        string raw_data;
        std::getline(data, raw_data);
        if ((raw_data.empty() == true) ||
            (String::startsWith(raw_data, "'") == true))
        {
            continue;
        }

        const auto parts = String::split(raw_data, ',');
        if (parts.size() < 4) {
            THROW("Unable to load tileset: wrong symbol at pos " +
                std::to_string(data.tellg()));
        }

        const TileID id = std::stoi(parts[0]);
        if (id == 0) {
            THROW("Unable to load tileset: wrong tile index at pos " +
                std::to_string(data.tellg()));
        }
        if (remaining_ids.count(id) == 0) {
            continue;
        }

        TLevelTileMapTileset info;
        readInfo(source, info);
        registry.Register(id, entry);

        remaining_ids.remove(id);
    }
    data.close();
}

void TLevelTileMapTilesetRegistryLoader::readInfo(std::istream& is,
    TLevelTileMapTileset& info)
{
    //TODO: upgrade when necessary
    is >> info.imageResourceHash;
    is >> info.tileSize.x;
    is >> info.tileSize.y;

    int count;
    is >> count;
    info.properties.resize(count);
    for (int i = 0; i < count; ++i) {
        is >> info.properties[i].passability;
        is >> info.properties[i].passWeight;
        is >> info.properties[i].buildability;
    }
}

} // namepsace TD
