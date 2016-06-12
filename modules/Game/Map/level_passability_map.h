#ifndef LEVEL_PASSABILITY_MAP_H
#define LEVEL_PASSABILITY_MAP_H

#include "Core/core.h"
#include "Game/Components/components_list.h"
#include "GameEngine/component_systems.h"
#include "Game/Map/level_tile_map_tileset.h"
#include "Game/Map/level_tile_map_tileset_registry.h"


namespace TD {

struct TLevelInfoPassabilityMap : GE::TComponentCreateArgs
{
    using Vec2ui = Size;
    Size size;

    TLevelScene* scene;
    TLevelScene::ComponentHandle tileMapHandle;
    TLevelTileMapTilesetRegistry* tilesetRegistry;
};

class CPassabilityMap :
    public GE::CLogicsComponent
{
public:
    using Passability = uchar;
    using PassabilityMap = vector<Passability>;

    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args = nullptr);

    CPassabilityMap(const TLevelPassabilityMapInfo* source);
	
    const PassabilityMap& GetMap(const Altitude& altitude);
    const Size& GetSize() const;

    virtual void Update() override;
    virtual void HandleMessage(const GE::TMessage& message) override;
    virtual void Subscribe(GE::TComponentSystem& system) override;
    virtual void Unsubscribe(GE::TComponentSystem& system) override;

    void SetScene(TLevelScene* instance);
    void SetTileMapHandle(const TLevelScene::ComponentHandle& instance);
    void SetTilesetRegistry(TLevelTileMapTilesetRegistry* instance);

private:
    std::array<PassabilityMap, static_cast<TAltitude>(Altitude::_count)> maps;
    Size size;

    TLevelScene* scene;
    TLevelScene::ComponentHandle tileMapHandle;
    TLevelTileMapTilesetRegistry* tilesetRegistry;
};

template<>
struct GE::ComponentID<CLevelPassabilityMap> {
    static constexpr GE::ComponentIDs value = GE::ComponentIDs::LevelPassabilityMap;
};

template<>
struct GE::ComponentClass<CLevelPassabilityMap> {
    static constexpr GE::CompponentClass value = GE::ComponentSystem::logics;
};

} // namespace TD

#endif // LEVEL_PASSABILITY_MAP_H