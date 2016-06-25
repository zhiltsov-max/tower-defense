#ifndef LEVEL_INFO_H
#define LEVEL_INFO_H

#include "Core/core.h"


namespace TD {

using TLevelCode = string;

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

struct TLevelMobsControllerInfo : GE::TComponentCreateArgs
{
    float delay;
    vector<TLevelInfoMobSequence> sequence;
};

struct TLevelBuildingsControllerInfo : GE::TComponentCreateArgs
{
    vector<TBuildingClassId> restricted;
    vector<TBuildingClassId> allowed;
    size_t maxCount;
};

struct TLevelResearchesControllerInfo : GE::TComponentCreateArgs
{
    vector<TResearchClassId> restricted;
    vector<TResearchClassId> allowed;
    size_t maxCount;
};

struct TLevelQuestsControllerInfo : GE::TComponentCreateArgs
{
    vector<TNamedData<string>> quests;
};

struct TLevelInfoStage
{
    TLevelInfoScene scene; //TODO: decide if it is needed
};

struct TLevelInfo
{
    TLevelInfoCommon common;
    TLevelInfoScene scene;
    vector<TLevelInfoStage> stages;
};

} // namespace TD

#endif // LEVEL_INFO_H
