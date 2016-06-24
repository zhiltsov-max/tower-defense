#include "level_tile_map.h"


namespace TD {

std::unique_ptr<GE::TComponent>
CLevelTileMap::Create(const GE::TComponentCreateArgs* args_) {
    const auto* args = dynamic_cast<CLevelTileMap::Parameters*>(args_);
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
        ASSERT(source->layers[i].size() == source->size.x * source->size.y,
            "Unexpected source layer size, layer #" + std::to_string(i));
    }
    loadTiles(source);
    loadTilesets();
}

void CLevelTileMap::loadTiles(const Parameters& source) {
    for (uchar i = 0; i < source.layers.size(); ++i) {
        std::copy(source.layers[i].begin(), source.layers[i].end(),
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

void CLevelTileMap::HandleMessage(const TMessage& message) { /*none*/ }
void CLevelTileMap::Subscribe(TComponentSystem& system) { /*none*/ }
void CLevelTileMap::Unsubscribe(TComponentSystem& system) { /*none*/}

std::pair<CLevelTileMap::Layers::iterator, CLevelTileMap::Layers::iterator>
CLevelTileMap::GetLayer(const Layer& layer) const {
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
        layers.reserve(size.x * size.y * source.layers.size());
    }
}


std::unique_ptr<GE::TComponent>
CLevelTileMapView::Create(const GE::TComponentCreateArgs* args_) {
    const auto* args = dynamic_cast<CLevelTileMap::Parameters*>(args_);
    return std::unique_ptr<GE::TComponent>(new CLevelTileMapView(*args));
}

CLevelTileMapView::CLevelTileMapView(const Parameters* source) :
    parent_type(GE::ComponentID<CLevelTileMapView>::value)
{
    if (source != nullptr) {
        scene = source->scene;
        tilesetRegistry = source->tilesetRegistry;
        tileMapHandle = source->tileMapHandle;
    }
}

void CLevelTileMapView::Update() { /*none*/ }
void CLevelTileMapView::HandleMessage(const TMessage& message) { /*none*/ }
void CLevelTileMapView::Subscribe(TComponentSystem& system) { /*none*/ }
void CLevelTileMapView::Unsubscribe(TComponentSystem& system) { /*none*/}

void CLevelTileMapView::SetScene(TLevelScene* instance) {
    scene = instance;
}

void CLevelTileMapView::SetTilesetRegistry(
    TLevelTileMapTilesetRegistry* instance)
{
    tilesetRegistry = instance;
}

void CLevelTileMapView::SetTileMap(const TLevelScene::ComponentHandle& handle) {
    tileMapHandle = handle;
}

void CLevelTileMapView::draw(Graphics::TRenderTarget& target) {
    if (scene == nullptr) {
        return;
    }
    const auto* tileMap =
            scene->GetRaw().GetComponent<CLevelTileMap>(tileMapHandle);
    if (tileMap == nullptr) {
        tileMapHandle = TLevelScene::ComponentHandle::Undefined;
        return;
    }
    for (uchar i = 0; i < CLevelTileMap::Layer::_count; ++i) {
        const auto boundaries =
            tileMap->GetLayer(static_cast<CLevelTileMap::Layer>(i));

        size_t x = 0;
        size_t y = 0;
        for (auto it = boundaries.first; it != boundaries.second; ++it) {
            const auto tileId = *it;
            if (tileId.index != 0) {
                //TODO: ...
                sf::Sprite sprite = tileset.getImage(tileId - 1);
                sprite.setPosition(x * tileSize, y * tileSize);
                target.draw(sprite);
            }
        }
    }
}

} // namespace TD
