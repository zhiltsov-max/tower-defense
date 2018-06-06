#include "gameobjectresources.h"


std::list<string> GameObjectResources::get(const TNamedData<string>& source, const TLevel& level) {
    std::list<string> res;

    if (source.contains(GameObjectsResourcesEntry::Mobs) == true) {
        res.push_back(MobResources::get(source.slice(GameObjectsResourcesEntry::Mobs), level));
    }

    if (source.contains(GameObjectsResourcesEntry::Buildings) == true) {
        res.push_back(BuildingResources::get(source.slice(GameObjectsResourcesEntry::Buildings), level));
    }

    return res;
}
