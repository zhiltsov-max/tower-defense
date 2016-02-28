#ifndef BUILDINGS_LIST_H
#define BUILDINGS_LIST_H

#include "building.h"
#include "turret.h"

#include "tb_base.h"
#include "tb_rocket.h"
#include "tb_artillery.h"

#include "tb_watchpost.h"
#include "tb_castle.h"

#include "buildings_info.h"


namespace TD {


struct BuildingMetadata {
    using Create = TBuildingsRegistryEntry::Create;
    Create create;

    using Loader = TBuildingInfoLoader;
    Loader loader;


    BuildingMetadata(const Create& create, const Loader& loader) :
        create(create),
        loader(loader)
    {}
};

static const std::map<TBuilding::ClassId, BuildingMetadata> buildingMetadata = {
    //id, {create, loader} ...

};


} // namespace TD

#endif // BUILDINGS_LIST_H
