#include "level_tile_map.h"


const GE::ComponentIDs GE::ComponentID<TD::CLevelTileMap>::value =
    GE::ComponentIDs::LevelTileMap;

const GE::ComponentIDs GE::ComponentID<TD::CLevelTileMapView>::value =
    GE::ComponentIDs::LevelTileMapView;

namespace TD {

std::unique_ptr<GE::TComponent>
CLevelTileMap::Create(const GE::TComponentCreateArgs* args_) {
    const auto* args = dynamic_cast<const Parameters*>(args_);
    if ((args_ != nullptr) && (args == nullptr)) {
        THROW("Wrong args passed to function.");
    }
    return std::unique_ptr<GE::TComponent>(new CLevelTileMap(args));
}

CLevelTileMap::CLevelTileMap(const Parameters* source) :
    parent_type(GE::ComponentID<CLevelTileMap>::value),
    size(),
    tilesets(),
    layers()
{
    if (source == nullptr) {
        return;
    }

    SetSize(source->size);

    ASSERT(source->layers.size() == static_cast<size_t>(Layer::_count),
        "Unable to load levelTileMap: unexpected layers count.");
    for (uchar i = 0; i != source->layers.size(); ++i) {
        ASSERT(source->layers[i].tiles.size() == source->size.x * source->size.y,
            "Unexpected source layer size, layer #" + std::to_string(i));
    }
    loadTiles(*source);
    loadTilesets();
}

void CLevelTileMap::loadTiles(const Parameters& source) {
    ASSERT(source.layers.size() <= static_cast<size_t>(Layer::_count),
        "Failed to load tiles for map: unexpected layers count");
    for (uchar i = 0; i < source.layers.size(); ++i) {
        ASSERT(source.layers[i].tiles.size() <= size.x * size.y,
            "Failed to load tiles for map: unexpected tiles count");
        std::copy(source.layers[i].tiles.begin(), source.layers[i].tiles.end(),
            layers.begin() + getLayerBegin(i));
    }
}

void CLevelTileMap::loadTilesets() {
    tilesets.clear();
    for (const auto& entry : layers) {
        tilesets.insert(entry.tileset);
    }
}

const CLevelTileMap::Size& CLevelTileMap::GetSize() const {
    return size;
}

const CLevelTileMap::Tilesets& CLevelTileMap::GetTilesets() const {
    return tilesets;
}

std::pair<
    CLevelTileMap::Layers::const_iterator,
    CLevelTileMap::Layers::const_iterator
>
CLevelTileMap::GetLayer(const Layer& layer) const {
    return {
        layers.cbegin() + getLayerBegin(static_cast<uchar>(layer)),
        layers.cbegin() + getLayerEnd(static_cast<uchar>(layer))
    };
}

uchar CLevelTileMap::GetLayerCount() const {
    return static_cast<uchar>(Layer::_count);
}

size_t CLevelTileMap::getLayerBegin(uchar index) const {
    return index * size.x * size.y;
}

size_t CLevelTileMap::getLayerEnd(uchar index) const {
    return (index + 1) * size.x * size.y;
}

std::pair<
    CLevelTileMap::Layers::iterator,
    CLevelTileMap::Layers::iterator
>
CLevelTileMap::GetLayer(const Layer& layer) {
    return {
        layers.begin() + getLayerBegin(static_cast<uchar>(layer)),
        layers.begin() + getLayerEnd(static_cast<uchar>(layer))
    };
}

void CLevelTileMap::SetSize(const Size& value) {
    ASSERT((0 < value.x) && (0 < value.y),
        "Unable to load levelTileMap: unexpected size.");
    if (size != value) {
        size = value;
        layers.resize(size.x * size.y * static_cast<uchar>(Layer::_count));
    }
}


std::unique_ptr<GE::TComponent>
CLevelTileMapView::Create(const GE::TComponentCreateArgs* args_) {
    const auto* args = dynamic_cast<const Parameters*>(args_);
    if ((args_ != nullptr) && (args == nullptr)) {
        THROW("Wrong args passed to function.");
    }
    return std::unique_ptr<GE::TComponent>(new CLevelTileMapView(args));
}

CLevelTileMapView::CLevelTileMapView(const Parameters* source) :
    parent_type(GE::ComponentID<CLevelTileMapView>::value),
    tileMapComponent(),
    tilesetRegistry(nullptr)
{
    if (source != nullptr) {
        tilesetRegistry = source->tilesetRegistry;
        tileMapComponent = source->tileMapComponent;
    }
}

void CLevelTileMapView::HandleMessage(const GE::TMessage& message,
    Context& context) { /*TODO:...*/ }

void CLevelTileMapView::Update(const GE::TTime& step, Context& context) {
    //TODO: implementation
}

forward_list<GE::TMessage::ID> CLevelTileMapView::GetAcceptedMessages() const {
    /*TODO:...*/
    return forward_list<GE::TMessage::ID>();
}

void CLevelTileMapView::Render(Graphics::TRenderTarget& target) {
    //TODO: implementation
    THROW("Not implemented yet.");
//    if (tileMapComponent.empty() == true) {
//        return;
//    }
//    ASSERT(scene != nullptr, "Scene must be set.");
//    ASSERT(tileMapHandle != GE::TScene::ComponentHandle::Undefined,
//        "Tile map data component is not found.");

//    const auto* tileMap =
//        scene->GetComponent<CLevelTileMap>(tileMapHandle);
//    if (tileMap == nullptr) {
//        tileMapHandle = TLevelScene::ComponentHandle::Undefined;
//        return;
//    }
//    for (uchar i = 0; i < CLevelTileMap::Layer::_count; ++i) {
//        const auto boundaries =
//            tileMap->GetLayer(static_cast<CLevelTileMap::Layer>(i));

//        size_t x = 0;
//        size_t y = 0;
//        for (auto it = boundaries.first; it != boundaries.second; ++it) {
//            const auto tileId = *it;
//            if (tileId.index != 0) {
//                //TODO: ...
//                sf::Sprite sprite = tileset.getImage(tileId - 1);
//                sprite.setPosition(x * tileSize, y * tileSize);
//                target.draw(sprite);
//            }
//        }
//    }
}

void CLevelTileMapView::SetTilesetRegistry(
    TLevelTileMapTilesetRegistry* instance)
{
    tilesetRegistry = instance;
}

} // namespace TD
