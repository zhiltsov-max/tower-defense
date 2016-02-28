#ifndef LEVEL_STAGES_INFO_H
#define LEVEL_STAGES_INFO_H

#include "level_info_stage.h"
#include "level_info_raw.h"



namespace TD {


struct TLevelInfoStages
{
    vector<TStageInfo> stages;


    TLevelInfoStages(const TRawLevelInfo& source);
};


} // namespace TD

#endif // LEVEL_STAGES_INFO_H
