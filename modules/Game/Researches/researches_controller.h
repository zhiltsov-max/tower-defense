#ifndef RESEARCHES_CONTROLLER_H
#define RESEARCHES_CONTROLLER_H

#include "researches_info.h"
#include "Game/Level/level_info_researches.h"



namespace TD {


class TResearchesController
{
public:
    using Registry = TResearchesRegistry;


    TResearchesController(const TLevelInfoResearches& info);

    TResearch CreateResearch(const TResearch::ID& id);

    const Registry& GetRegistry() const;
    Registry& GetRegistry();

private:
    Registry registry;
};


} // namespace TD

#endif // RESEARCHES_CONTROLLER_H
