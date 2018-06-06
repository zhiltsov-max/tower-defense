#ifndef LEVEL_TILE_MAP_H
#define LEVEL_TILE_MAP_H

#include "GameEngine/Utility/core.h"
#include "GameEngine/component.h"
#include "GameEngine/component_registry.h"
#include "Game/Components/td_components_list.h"
#include "Game/ComponentSystems/td_component_systems_list.h"
#include "Game/Map/level_tile_map_tileset.h"
#include "Game/Map/level_tile_map_tileset_registry.h"


namespace TD {

class TLevelTileMap
{
public:
    using Size = Vec2ui;
    union Tile {
        struct {
            ushort tileset;
            ushort tile;
        };
        uint index;
    };
    enum class Layer : uchar {
        _min = 0,

        Ground = 0,
        GroundEffects = 1,
        Objects = 2,
        ObjectEffects = 3,

        _count
    };
    using Layers = vector<Tile>;
    using Tilesets = std::set<TLevelTileMapTilesetId>;
    struct Parameters;
    struct LayerParameters;
    using TileParameters = TLevelTileMap::Tile;

    TLevelTileMap() = default;
    TLevelTileMap(const Parameters& source);

    const Size& GetSize() const;
    void SetSize(const Size& value);

    const Tilesets& GetTilesets() const;

    std::pair<Layers::const_iterator, Layers::const_iterator> GetLayer(
        const Layer& layer) const;
    std::pair<Layers::iterator, Layers::iterator> GetLayer(const Layer& layer);

    uchar GetLayerCount() const;

private:
    Layers layers;
    Tilesets tilesets;
    Size size;

    size_t getLayerBegin(uchar index) const;
    size_t getLayerEnd(uchar index) const;

    void loadTilesets();
    void loadTiles(const Parameters& source);
};

struct TLevelTileMap::LayerParameters
{
    vector<TileParameters> tiles;
};

struct TLevelTileMap::Parameters
{
    Size size;
    vector<LayerParameters> layers;
};

} // namespace TD


TD_DECLARE_COMPONENT_CLASS(CLevelTileMap,
    GE::ComponentIDs::LevelTileMap, GE::ComponentSystem::Map)


namespace TD {

struct CLevelTileMap : GE::TComponent
{
    using TileMap = TLevelTileMap;
    struct Parameters;

    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args = nullptr);

    CLevelTileMap(const CLevelTileMap::Parameters* source = nullptr);

    TileMap tileMap;

private:
    using parent_type = GE::TComponent;
};

struct CLevelTileMap::Parameters : GE::TComponentCreateArgs
{
    TileMap::Parameters map;
};

} // namepsace TD


TD_DECLARE_COMPONENT_CLASS(CLevelTileMapView,
    GE::ComponentIDs::LevelTileMapView, GE::ComponentSystem::Graphics)


namespace TD {

struct CLevelTileMapView : GE::TComponent // TODO: maybe it is Presenter and should be attached to Map CS?
{
    using TileFrame = sf::IntRect;
    using ImageInstance = Graphics::TTexture*;
    using TileImage = Graphics::TSprite;
    struct Parameters;

    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args = nullptr);

    CLevelTileMapView(const Parameters* source = nullptr);

private:
    using parent_type = GE::TComponent;
};

struct CLevelTileMapView::Parameters : GE::TComponentCreateArgs
{
    /*none*/
};

//void CLevelTileMapView::Render(Graphics::TRenderTarget& target) {
//    //TODO: implementation
//    THROW("Not implemented yet.");
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
//                sf::Sprite sprite = tileset.getImage(tileId - 1);
//                sprite.setPosition(x * tileSize, y * tileSize);
//                target.draw(sprite);
//            }
//        }
//    }
//}

} // namespace TD

#endif // LEVEL_TILE_MAP_H
