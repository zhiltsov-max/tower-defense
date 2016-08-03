#ifndef LEVEL_H
#define LEVEL_H

#include "Game/Level/level_clock.h"
#include "Game/Level/level_scene.h"
#include "GameEngine/game_engine.h"


namespace TD {

using TLevelCode = string;

/*
See docs for complete information.
*/
class TLevel
{
public:
    using Clock = TLevelClock;
    using Scene = TLevelScene;
    enum class LevelType {
        Undefined = 0,
        Normal,
        Free
    };
    struct Parameters
    {
        struct Common
        {
            TLevelCode levelCode;
            TLevelCode nextLevelCode;
            LevelType levelType;
            string loadingScript;
        };

        struct Stage
        {
            TLevelScene::Parameters scene; //TODO: decide if it is needed
        };

        using Scene = TLevelScene::Parameters;

        Common common;
        Scene scene;
        vector<Stage> stages;
    };
    struct CommonData
    {
        TLevelCode levelCode;
        TLevelCode nextLevelCode;
        LevelType  levelType;

        CommonData(const Parameters::Common& info = Parameters::Common());
    };

    TLevel(const Parameters& info, GE::TGameEngine* engine);

    const Clock& GetClock() const;
    Clock& GetClock();

    const Scene& GetScene() const;
    Scene& GetScene();

    void Update();

    void SetGameEngine(GE::TGameEngine* instance);

private:
    Clock clock;
    Scene scene;
    CommonData common;

    using PGameEngine = GE::TGameEngine *;
    PGameEngine gameEngine;

    /*
    Level script engine loader.
    It have to implement all level-specific behaviour of loading process
    i.e. new game objects/components import, method overrides,
    scene loading, progress managing, etc.
    */
    void loadScript(const Parameters& info);
};

} // namespace TD

#endif //LEVEL_H
