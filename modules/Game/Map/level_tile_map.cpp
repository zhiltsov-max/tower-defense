#include "Game/Map/level_tile_map.h"


namespace TD {

TLevelTileMap::TLevelTileMap(const Parameters& source) :
    size(),
    tilesets(),
    layers()
{
    if ((source.size.x == 0) || (source.size.y == 0)) {
        return;
    }
    SetSize(source.size);

    ASSERT(source.layers.size() == static_cast<size_t>(Layer::_count),
        "Unable to load levelTileMap: unexpected layers count.");
    for (uchar i = 0; i != source.layers.size(); ++i) {
        ASSERT(source.layers[i].tiles.size() == source.size.x * source.size.y,
            "Unexpected source layer size, layer #" + std::to_string(i));
    }
    loadTiles(source);
    loadTilesets();
}

void TLevelTileMap::loadTiles(const Parameters& source) {
    ASSERT(source.layers.size() <= static_cast<size_t>(Layer::_count),
        "Failed to load tiles for map: unexpected layers count");
    for (uchar i = 0; i < source.layers.size(); ++i) {
        ASSERT(source.layers[i].tiles.size() <= size.x * size.y,
            "Failed to load tiles for map: unexpected tiles count");
        std::copy(source.layers[i].tiles.begin(), source.layers[i].tiles.end(),
            layers.begin() + getLayerBegin(i));
    }
}

void TLevelTileMap::loadTilesets() {
    tilesets.clear();
    for (const auto& entry : layers) {
        tilesets.insert(entry.tileset);
    }
}

const TLevelTileMap::Size& TLevelTileMap::GetSize() const {
    return size;
}

const TLevelTileMap::Tilesets& TLevelTileMap::GetTilesets() const {
    return tilesets;
}

std::pair<
    TLevelTileMap::Layers::const_iterator,
    TLevelTileMap::Layers::const_iterator
>
TLevelTileMap::GetLayer(const Layer& layer) const {
    return {
        layers.cbegin() + getLayerBegin(static_cast<uchar>(layer)),
        layers.cbegin() + getLayerEnd(static_cast<uchar>(layer))
    };
}

uchar TLevelTileMap::GetLayerCount() const {
    return static_cast<uchar>(Layer::_count);
}

size_t TLevelTileMap::getLayerBegin(uchar index) const {
    return index * size.x * size.y;
}

size_t TLevelTileMap::getLayerEnd(uchar index) const {
    return (index + 1) * size.x * size.y;
}

std::pair<
    TLevelTileMap::Layers::iterator,
    TLevelTileMap::Layers::iterator
>
TLevelTileMap::GetLayer(const Layer& layer) {
    return {
        layers.begin() + getLayerBegin(static_cast<uchar>(layer)),
        layers.begin() + getLayerEnd(static_cast<uchar>(layer))
    };
}

void TLevelTileMap::SetSize(const Size& value) {
    ASSERT((0 < value.x) && (0 < value.y),
        "Unable to load levelTileMap: unexpected size.");
    if (size != value) {
        size = value;
        layers.resize(size.x * size.y * static_cast<uchar>(Layer::_count));
    }
}


std::unique_ptr<GE::TComponent>
CLevelTileMap::Create(const GE::TComponentCreateArgs* args_) {
    const auto* args = dynamic_cast<const Parameters*>(args_);
    if ((args_ != nullptr) && (args == nullptr)) {
        THROW("Wrong args passed to function.");
    }
    return std::unique_ptr<GE::TComponent>(new CLevelTileMap(args));
}

CLevelTileMap::CLevelTileMap(const Parameters* source) :
    parent_type(GE::ComponentID<CLevelTileMap>::value()),
    tileMap((source != nullptr) ? source->map : TLevelTileMap::Parameters())
{}


std::unique_ptr<GE::TComponent>
CLevelTileMapView::Create(const GE::TComponentCreateArgs* args_) {
    const auto* args = dynamic_cast<const Parameters*>(args_);
    if ((args_ != nullptr) && (args == nullptr)) {
        THROW("Wrong args passed to function.");
    }
    return std::unique_ptr<GE::TComponent>(new CLevelTileMapView(args));
}

CLevelTileMapView::CLevelTileMapView(const Parameters* source) :
    parent_type(GE::ComponentID<CLevelTileMapView>::value())
{
    UNUSED(source);
}

} // namespace TD
