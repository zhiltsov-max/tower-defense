#ifndef LEVEL_INFO_H
#define LEVEL_INFO_H

#include "level_info_raw.h"
#include "level_info_common.h"
#include "level_info_scene.h"
#include "level_info_stages.h"
#include "level_info_game_objects.h"



namespace TD {


namespace LevelInfo {


static constexpr string Common = "common";
static constexpr string Scene = "scene";
static constexpr string GameObjects = "gameObjects";
static constexpr string Stages = "stages";


} // namespace LevelInfo


struct TLevelInfo {
    TLevelInfoCommon common;
    TLevelInfoScene scene;
    TLevelInfoGameObjects gameObjects;
    TLevelInfoStages stages;


    TLevelInfo(const TRawLevelInfo& source);
};


} // namespace TD

#endif // LEVEL_INFO_H
