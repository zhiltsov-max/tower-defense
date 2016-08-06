#include "Game/Components/components_list.h"

#include "Game/Map/level_node_map.h"
#include "Game/Map/level_tile_map.h"
#include "Game/Map/level_passability_map.h"


namespace TD {

namespace CS {

namespace impl {

template<class C>
void RegisterComponentClass(GE::TComponentRegistry& registry) {
    GE::TComponentRegistry::Entry entry;
    entry.create = &C::Create;
    entry.system = GE::ComponentClass<C>::value;
    registry.Register(GE::ComponentID<C>::value, entry);
}

} // namespace impl

const GE::TComponentRegistry componentsRegistry = [] {
    GE::TComponentRegistry registry;

    impl::RegisterComponentClass<TD::CLevelNodeMap>(registry);
    impl::RegisterComponentClass<TD::CLevelNodeMapView>(registry);
    impl::RegisterComponentClass<TD::CLevelTileMap>(registry);
    impl::RegisterComponentClass<TD::CLevelTileMapView>(registry);
    impl::RegisterComponentClass<TD::CLevelPassabilityMap>(registry);

    return registry;
} ();

const GE::TComponentRegistry& GetComponentsRegistry() {
    return componentsRegistry;
}

} // namespace CS

} // namespace TD
