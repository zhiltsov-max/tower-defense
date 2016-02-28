#ifndef STAGEINFO_H
#define STAGEINFO_H

#include "level_info_raw.h"



namespace TD {


namespace StageInfo {


static constexpr string Mobs = "mobs";
static constexpr string Buildings = "buildings";
static constexpr string Researches = "researches";
static constexpr string Quests = "quests";
static constexpr string Map = "map";
static constexpr string Scripts = "scripts";


namespace MobsInfo {
static constexpr string Count = "count";
static constexpr string Delay = "delay";
static constexpr string Sequence = "sequence";
} // namespace MobsInfo

namespace BuildingsInfo {
static constexpr string Restricted = "restricted";
static constexpr string Allowed = "allowed";
static constexpr string MaxCount = "maxCount";
} // namespace BuildingsInfo

namespace ResearchesInfo {
static constexpr string Restricted = "restricted";
} // namespace ResearchesInfo

namespace QuestesInfo {
static constexpr string Count = "count";
} // namespace QuestsInfo

namespace MapInfo {
static constexpr string Size = "size";
static constexpr string TileSets = "tileSets";
static constexpr string NodeMap = "nodeMap";
static constexpr string Layers = "layers";

namespace NodeMapInfo {
static constexpr string Pathes = "pathes";
static constexpr string Enters = "enters";
static constexpr string Exits = "exits";
} // namespace NodeMapInfo

} // namespace MapInfo


} //namespace StageInfo


struct TStageInfo {

    TStageInfo(const TRawLevelInfo& source);
};


} // namespace TD

#endif
