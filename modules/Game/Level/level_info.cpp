#include "level_info.h"



namespace TD {


TLevelInfo::TLevelInfo(const TRawLevelInfo& source) :
    common(source.slice(LevelInfo::Common)),
    stages(source.slice(LevelInfo::Stages)),
    scene(source.slice(LevelInfo::Scene)),
    gameObjects(source.slice(LevelInfo::GameObjects))
{}


} // namespace TD
