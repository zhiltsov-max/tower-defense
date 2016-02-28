#ifndef GAMEOBJECT_RESOURCES_H
#define GAMEOBJECT_RESOURCES_H

#include "../../../Core/core.h"
#include <utility>

namespace GameObjectsResourcesEntry {

static const string Mobs = "mobs";
static const string Buildings = "buildings";

} //namespace GameObjectsResources


class GameObjectResources /*Abstract*/
{
public:
    static std::list<string> get(const TNamedData<string>& source, const TLevel& level);

	GameObjectResources() = delete;
};

#endif //GAMEOBJECT_RESOURCES_H
