#include "level_data_common.h"



namespace TD {


TLevelDataCommon::TLevelDataCommon(const TLevelInfoCommon& info) :
    levelCode(info.levelCode),
    nextLevelCode(info.nextLevelCode),
    levelType(info.levelType)
{}


} // namespace TD
