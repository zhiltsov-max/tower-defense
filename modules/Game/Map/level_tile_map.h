#ifndef LEVEL_TILE_MAP_H
#define LEVEL_TILE_MAP_H

#include "Core/core.h"
#include "Game/Components/components_list.h"
#include "Game/Map/level_tile_map_tileset.h"
#include "Game/Map/level_tile_map_tileset_registry.h"
#include "Game/Level/level_scene.h"


namespace TD {

class CLevelTileMap :
    public GE::CDataComponent
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
    using TileParameters = Tile;
    struct LayerParameters;

    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args = nullptr);

    CLevelTileMap(const CLevelTileMap::Parameters* source = nullptr);
		
    const Size& GetSize() const;
    void SetSize(const Size& value);

    const Tilesets& GetTilesets() const;

    std::pair<Layers::const_iterator, Layers::const_iterator> GetLayer(
        const Layer& layer) const;
    std::pair<Layers::iterator, Layers::iterator> GetLayer(const Layer& layer);

    uchar GetLayerCount() const;

private:
    using parent_type = CDataComponent;

    Layers layers;
    Tilesets tilesets;
    Size size;

    size_t getLayerBegin(uchar index) const;
    size_t getLayerEnd(uchar index) const;

    void loadTilesets();
    void loadTiles(const Parameters& source);
};

struct CLevelTileMap::LayerParameters
{
    vector<TileParameters> tiles;
};

struct CLevelTileMap::Parameters : GE::TComponentCreateArgs
{
    Size size;
    vector<LayerParameters> layers;
};

} // namepsace TD


namespace GE {

template<>
struct ComponentID<TD::CLevelTileMap>
{
    static constexpr ComponentIDs value = ComponentIDs::LevelTileMap;
};

} // namespace GE


namespace TD {

class CLevelTileMapView :
    public GE::CGraphicsComponent
{
public:
    using TileFrame = sf::IntRect;
    using ImageInstance = Graphics::TTexture*;
    using TileImage = Graphics::TSprite;
    struct Parameters;

    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args = nullptr);

    CLevelTileMapView(const Parameters* source = nullptr);

    virtual void HandleMessage(const GE::TMessage& message,
        Context& context) override;
    virtual forward_list<GE::TMessage::ID> GetAcceptedMessages() const override;

    virtual void Update(const GE::TTime& step, Context& context) override;
    virtual void Render(Graphics::TRenderTarget& target) override;

    void SetTilesetRegistry(TLevelTileMapTilesetRegistry* instance);

private:
    using parent_type = GE::CGraphicsComponent;

    TLevelTileMapTilesetRegistry* tilesetRegistry;
    TLevelScene::ComponentPath tileMapComponent;
};

struct CLevelTileMapView::Parameters : GE::TComponentCreateArgs
{
    TLevelTileMapTilesetRegistry* tilesetRegistry;
    TLevelScene::ComponentPath tileMapComponent;
};

} // namespace TD


namespace GE {

template<>
struct ComponentID<TD::CLevelTileMapView>
{
    static constexpr ComponentIDs value = ComponentIDs::LevelTileMapView;
};

} // namespace GE

#endif // LEVEL_TILE_MAP_H
