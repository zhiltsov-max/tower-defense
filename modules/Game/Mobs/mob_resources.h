#ifndef MOB_RESOURCES_H
#define MOB_RESOURCES_H

#include "../../../Core/core.h"
#include "mob_info.h"


class MobResources /*Abstract*/
{
public:
    static std::vector<string> get(const TNamedData<string>& source, const TMobsInfo& info);

	MobResources() = delete;
};

#endif //MOB_RESOURCES_H
