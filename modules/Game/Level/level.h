#ifndef LEVEL_H
#define LEVEL_H

#include "Game/Level/level_info.h"
#include "Game/Level/level_clock.h"
#include "Game/Level/level_scene.h"
#include "GameEngine/game_engine.h"


namespace TD {

/*
See docs for complete information.
*/
class TLevel
{
public:
    using Clock = TLevelClock;
    using Scene = TLevelScene;
    struct CommonData {
        TLevelCode levelCode;
        TLevelCode nextLevelCode;
        LevelType  levelType;

        CommonData(const TLevelInfoCommon& info);
    };

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
    CommonData common;

    using PGameEngine = GE::TGameEngine *;
    PGameEngine gameEngine;

    /* Level LUA loader.
    It have to implement all level-specific behaviour of loading process
    i.e. new game objects/components import, method overrides,
    scene loading, progress managing, etc.
    */
    void loadScript(const TLevelInfo& info);
};

} // namespace TD

#endif //LEVEL_H
