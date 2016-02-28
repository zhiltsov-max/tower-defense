#ifndef COMMON_LEVEL_INFO_H
#define COMMON_LEVEL_INFO_H

#include "level_info_raw.h"
#include "Game/Level/level_code.h"



namespace TD {


namespace CommonLevelInfo {


static constexpr string NextLevelCode = "nextLevel";

static constexpr string LevelType = "type";
static constexpr string LevelType_Normal = "normal";
static constexpr string LevelType_Free = "free";


} // namespace CommonLevelInfo


enum class LevelType {
    Undefined = 0,
    Normal,
    Free
};


struct TLevelInfoCommon {
    TLevelCode levelCode;
    TLevelCode nextLevelCode;
    LevelType  levelType;


    TLevelInfoCommon(const TRawLevelInfo& source);
};


} // namespace TD

#endif // COMMON_LEVEL_INFO_H
