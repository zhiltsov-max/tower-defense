#ifndef LEVEL_H
#define LEVEL_H

#define BEGIN_TD namespace TD {
#define END_TD }

#include "level_info.h"
#include "level_clock.h"
#include "level_scene.h"
#include "level_data_common.h"
#include "level_data_stages.h"
#include "GameEngine/game_engine.h"



BEGIN_TD


/*
See docs for complete information.
*/
class TLevel
{
public:
    using Clock = TLevelClock;
    using Scene = TLevelScene;
    using Common = TLevelDataCommon;
    using GameObjects = TLevelSceneDataGameObjects;
    using Stages = TLevelDataStages;


    TLevel(const TLevelInfo& info, GE::TGameEngine& engine);

    const Clock& GetClock() const;
    Clock& GetClock();

    const Scene& GetScene() const;
    Scene& GetScene();

    void Update();

    const GE::TGameEngine* GetGameEngine() const;
    GE::TGameEngine* GetGameEngine();

private:
    Clock clock;
    Scene scene;
    Common common;
    Stages stages;


    using PGameEngine = GE::TGameEngine *;
    PGameEngine gameEngine;

    /* Level LUA loader.
    It have to implement all level-specific behaviour of loading process
    i.e. new game objects/components import, method overrides,
    scene loading, progress managing, etc.
    */
    void loadScript(const TLevelInfo& info);
};


END_TD


#endif //LEVEL_H
