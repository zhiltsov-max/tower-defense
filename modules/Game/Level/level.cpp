#include "level.h"



BEGIN_TD


TLevel::TLevel(const TLevelInfo& info, TGameEngine* engine) :
    common(info.common),
    gameObjects(info.gameObjects),
    stages(info.stages),
    clock(),
    scene(info.scene, engine),
    gameEngine(engine)
{}

const TLevel::Clock& TLevel::GetClock() const {
    return clock;
}

TLevel::Clock& TLevel::GetClock() {
    return clock;
}

const TLevel::Scene& TLevel::GetScene() const {
    return scene;
}

TLevel::Scene& TLevel::GetScene() {
    return scene;
}

void TLevel::Update() {
    for(auto i = 0; i < (uint)clock.GetRate(); ++i) {
        gameEngine->Update(clock.tick());
        clock.Update();
    }
}

const TGameEngine* TLevel::GetGameEngine() const {
    return gameEngine;
}

TGameEngine* TLevel::GetGameEngine() {
    return gameEngine;
}


END_TD
