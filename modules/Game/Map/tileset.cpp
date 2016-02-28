#include "tileset.h"
#include "../../../Application/application.h"


TTileset::TTileset(const TTilesetInfo& source) :
    m_info()
{
    if ((source.texture == nullptr) || (source.info.empty() == true)) {
        Throw("Unable to load tileset: source is empty.", "TTileset::TTileset");
    }

    const int textureHorizontalCapacity = source.texture->getSize().x / source.tileSize;

    std::ifstream data = std::ifstream(source.info);
    if (data.is_open() == false) {
        Throw("Unable to load tileset: source was not found.", "TTileset::TTileset");
    }

    while (data.good()) {
        string raw_data;
        std::getline(data, raw_data);
        if (raw_data.empty() || (String::startsWith(raw_data, "'"))) { continue; }

        vector<string> parts = std::move(String::split(raw_data, ','));
        if (parts.size() < 4) {
            Throw("Unable to load tileset: wrong symbol at pos " + std::to_string(data.tellg()) + std::string("."), "TTileset::TTileset");
        }

        const TileID id = std::stoi(parts[0]);
        if (id == 0) {
            Throw("Unable to load tileset: wrong tile index at pos " + std::to_string(data.tellg()) + std::string("."), "TTileset::TTileset");
        }

        auto& entry = m_info[id];
        entry.altitude  = (Altitude)std::stoi(parts[1]);
        entry.weight    = (PassWeight)std::stoi(parts[2]);
        entry.buildable = std::stoi(parts[3]);
        entry.frame     = TileFrame(
            id % textureHorizontalCapacity * source.tileSize,
            id / textureHorizontalCapacity * source.tileSize,
            source.tileSize, source.tileSize);
    }

    m_info.emplace(0, Altitude::_min, PassWeight::Min, false);

    data.close();
}	
	
const PassWeight& TTileset::GetTilePassWeight(const TileID& id) const {
    return m_info.at(id).weight;
}

const Altitude& TTileset::GetTileAltitude(const TileID& id) const {
    return m_info.at(id).altitude;
}

bool TTileset::GetTileBuildability(const TileID& id) const {
    return m_info.at(id).buildable;
}

TTileset::TileImage TTileset::GetTileImage(const TTileset::TileID& id) const {
    return TileImage(e_image, m_info.at(id).frame);
}

void TTileset::SetImageInstance(TTileset::ImageInstance& value) {
    e_image = value;
}
