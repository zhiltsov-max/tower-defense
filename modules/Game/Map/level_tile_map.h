#ifndef LEVEL_TILE_MAP_H
#define LEVEL_TILE_MAP_H

#include "Core/core.h"
#include "Game/Components/components_list.h"
#include "Game/Map/level_tile_map_tileset.h"
#include "Game/Map/level_tile_map_tileset_registry.h"
#include "Game/Level/level_scene.h"


namespace TD {

struct TLevelInfoTileMapLayer
{
    union TileIndex {
        struct {
            ushort tileset;
            ushort tile;
        };
        uint index;
    };
    vector<TileIndex> tiles;
};

struct TLevelInfoTileMap : GE::TComponentCreateArgs
{
    using Size = Vec2ui;
    Size size;
    vector<TLevelInfoTileMapLayer> layers;
};

class CLevelTileMap :
    public GE::CLogicsComponent
{
public:
    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args = nullptr);

    CLevelTileMap(const TLevelInfoTileMap* source = nullptr);
		
    using Size = TLevelInfoTileMap::Size;
    const Size& GetSize() const;
    void SetSize(const Size& value);

    using Tilesets = std::set<TLevelTileMapTilesetId>;
    const Tilesets& GetTilesets() const;

    enum class Layer : uchar {
        _min = 0,

        Ground = 0,
        GroundEffects = 1,
        Objects = 2,
        ObjectEffects = 3,

        _count
    };
    using Tile = TLevelInfoTileMapLayer::TileIndex;
    std::pair<Layers::const_iterator, Layers::const_iterator> GetLayer(
        const Layer& layer) const;
    std::pair<Layers::iterator, Layers::iterator> GetLayer(const Layer& layer);

    virtual void Update() override;
    virtual void HandleMessage(const TMessage& message) override;
    virtual void Subscribe(TComponentSystem& system) override;
    virtual void Unsubscribe(TComponentSystem& system) override;

private:
    using parent_type = CLogicsComponent;

    using Layers = vector<Tile>;
    Layers layers;
    Tilesets tilesets;
    Size size;

    size_t getLayerBegin(uchar index) const;
    size_t getLayerEnd(uchar index) const;

    void loadTilesets();
    void loadTiles(const TLevelInfoTileMap& source);
};

template<>
struct GE::ComponentID<CLevelTileMap> {
    static constexpr GE::ComponentIDs value = GE::ComponentIDs::LevelTileMap;
};

template<>
struct GE::ComponentClass<CLevelTileMap> {
    static constexpr GE::CompponentClass value = GE::ComponentSystem::logics;
};


struct TLevelTileMapViewInfo : GE::TComponentCreateArgs
{
    TLevelScene* scene;
    TLevelTileMapTilesetRegistry* tilesetRegistry;
    TLevelScene::ComponentHandle tileMapHandle;
};

class CLevelTileMapView :
    public GE::CGraphicsComponent
{
public:
    using TileFrame = sf::IntRect;
    using ImageInstance = Graphics::TTexture*;
    using TileImage = Graphics::TSprite;

    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args = nullptr);

    CLevelTileMapView(const TLevelTileMapViewInfo* source = nullptr);

    virtual void Update() override;
    virtual void HandleMessage(const TMessage& message) override;
    virtual void Subscribe(TComponentSystem& system) override;
    virtual void Unsubscribe(TComponentSystem& system) override;

    void SetScene(TLevelScene* instance);
    void SetTilesetRegistry(TLevelTileMapTilesetRegistry* instance);
    void SetTileMap(const TLevelScene::ComponentHandle& handle);

protected:
    void draw(Graphics::TRenderTarget& target);

private:
    TLevelScene* scene;
    TLevelTileMapTilesetRegistry* tilesetRegistry;
    TLevelScene::ComponentHandle tileMapHandle;
};

template<>
struct GE::ComponentID<CLevelTileMapView> {
    static constexpr GE::ComponentIDs value = GE::ComponentIDs::LevelTileMapView;
};

template<>
struct GE::ComponentClass<CLevelTileMapView> {
    static constexpr GE::CompponentClass value = GE::ComponentSystem::graphics;
};

} // namespace TD

#endif // LEVEL_TILE_MAP_H
