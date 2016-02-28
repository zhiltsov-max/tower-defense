#ifndef LEVEL_COMMON_DATA_H
#define LEVEL_COMMON_DATA_H

#include "level_info_common.h"



namespace TD {


class TLevelDataCommon
{
public:
    TLevelDataCommon(const TLevelInfoCommon& info);

private:
    TLevelCode levelCode;
    TLevelCode nextLevelCode;
    LevelType  levelType;
};


} // namespace TD

#endif // LEVEL_COMMON_DATA_H
