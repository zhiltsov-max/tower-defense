#include "level_passability_map.h"
#include "Game/Map/level_tile_map.h"


namespace TD {

std::unique_ptr<GE::TComponent>
CPassabilityMap::Create(const GE::TComponentCreateArgs* args_) {
    const auto* args = dynamic_cast<TLevelPassabilityMapInfo*>(args_);
    return new CPassabilityMap(args);
}

CPassabilityMap::CPassabilityMap(const TLevelPassabilityMapInfo* source) :
    parent_type(GE::ComponentID<CPassabilityMap>::value)
{
    if (source != nullptr) {
        size = source->size;
        for (auto& map : maps) {
            map.reserve(source->size.x * source->size.y);
        }
    }
}

const CPassabilityMap::PassabilityMap&
CPassabilityMap::GetMap(const Altitude& altitude) {
    return maps[static_cast<uchar>(altitude)];
}

const Size& CPassabilityMap::GetSize() const {
    return size;
}

void CPassabilityMap::HandleMessage(const GE::TMessage& message) { /*none*/ }
void CPassabilityMap::Subscribe(GE::TComponentSystem& system) { /*none*/ }
void CPassabilityMap::Unsubscribe(GE::TComponentSystem& system) { /*none*/ }

void CPassabilityMap::SetScene(TLevelScene* instance) {
    scene = instance;
}

void CPassabilityMap::SetTileMapHandle(
    const TLevelScene::ComponentHandle& instance)
{
    tileMapHandle = instance;
}

void CPassabilityMap::SetTilesetRegistry(
    TLevelTileMapTilesetRegistry* instance)
{
    tilesetRegistry = instance;
}

} // namespace TD
