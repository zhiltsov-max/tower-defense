#ifndef MOB_INFO_H
#define MOB_INFO_H

#include "../gameobjects_info.h"
#include "mob.h"


using TMobsInfo = TGameObjectsInfo;

class TMobsInfoLoader {
public:
    using MobInfoLoader = function<void (*)(TMob::Info&, std::istream& source)>;


    void operator()(TMobsInfo& info);
private:
    static char* DATA_SOURCE_ADDRESS;


    const MobInfoLoader& getInfoLoader(const TMob::ClassId& classId) const;
};

#endif //MOB_INFO_H
