#ifndef LEVEL_INFO_H
#define LEVEL_INFO_H

#include "Core/core.h"
#include "Game/Level/level_code.h"
#include "Game/Buildings/buildings_info.h"
#include "Game/Mobs/mob_info.h"
#include "Game/Quests/quests_info.h"
#include "Game/Researches/researches_info.h"
#include "Game/Map/level_map.h"
#include "Game/Player/player_info.h"


namespace TD {

enum class LevelType {
    Undefined = 0,
    Normal,
    Free
};

struct TLevelInfoCommon
{
    TLevelCode levelCode;
    TLevelCode nextLevelCode;
    LevelType levelType;
    string loadingScript;
};

struct TLevelInfoMobSequenceEntry
{
    uint count;
    TMobClassId id;
};

struct TLevelInfoMobs
{
    float delay;
    vector<TLevelInfoMobSequence> sequence;
};

struct TLevelInfoBuildings
{
    vector<TBuildingClassId> restricted;
    vector<TBuildingClassId> allowed;
    size_t maxCount;
};

struct TLevelInfoResearches
{
    vector<TResearchClassId> restricted;
    vector<TResearchClassId> allowed;
    size_t maxCount;
};

struct TLevelInfoQuests
{
    vector<TNamedData<string>> quests;
};

struct TLevelInfoStage
{
    TLevelInfoMobs mobs;
    TLevelInfoBuildings buildings;
    TLevelInfoResearches researches;
    TLevelInfoQuests quests;
    TLevelInfoMap map;
};

struct TLevelInfoScene
{
    vector<string> resources;
    vector<TNamedData<string>> objects;
    TLevelInfoMap map;
};

struct TLevelInfo
{
    TLevelInfoCommon common;
    TLevelInfoScene scene;
    vector<TLevelInfoStage> stages;
};

} // namespace TD

#endif // LEVEL_INFO_H
