#ifndef LEVEL_H
#define LEVEL_H

#define BEGIN_TD namespace TD {
#define END_TD }

#include "level_info.h"
#include "level_clock.h"
#include "level_scene.h"
#include "level_data_common.h"
#include "level_data_game_objects.h"
#include "level_data_stages.h"



class TGameEngine;

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
    using GameObjects = TLevelDataGameObjects;
    using Stages = TLevelDataStages;


    TLevel(const TLevelInfo& info, TGameEngine* engine);

    const Clock& GetClock() const;
    Clock& GetClock();

    const Scene& GetScene() const;
    Scene& GetScene();

    void Update();

    const TGameEngine* GetGameEngine() const;
    TGameEngine* GetGameEngine();

private:
    Clock clock;
    Scene scene;
    Common common;
    GameObjects gameObjects;
    Stages stages;


    using PGameEngine = TGameEngine *;
    PGameEngine gameEngine;

    class Loader;
};


END_TD


#endif //LEVEL_H
