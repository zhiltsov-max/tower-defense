#include "level_info_common.h"



namespace TD {


TLevelInfoCommon::TLevelInfoCommon(const TRawLevelInfo& source) :
    levelCode(),
    nextLevelCode(source[CommonLevelInfo::NextLevelCode]),
    levelType(LevelType::Undefined)
{
    const auto& type = source[CommonLevelInfo::LevelType];
    switch (type) {
    case CommonLevelInfo::LevelType_Normal:
        levelType = LevelType::Normal;
        break;

    case CommonLevelInfo::LevelType_Free:
        levelType = LevelType::Free;
        break;

    default: {
        THROW("Unexpected level type: " + type)
        }
    }
}


} // namespace TD
