#ifndef RESEARCH_H
#define RESEARCH_H

#include "Game/Components/game_objects_info.h"



namespace TD {


class TResearch
{
public:
    using ID = TGameObjectClassId;


    TResearch(const ID& id);

    const ID& GetID() const;

    void SetResearched(bool value);
    bool IsResearched() const;

private:
    const ID id;
};


} // namespace TD

#endif // RESEARCH_H
