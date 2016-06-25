#include "level.h"
#include "Game/Level/level_lua_binding.h"


namespace TD {

TLevel::CommonData::CommonData(const TLevelInfoCommon& info) :
    levelCode(info.levelCode),
    nextLevelCode(info.nextLevelCode),
    levelType(info.levelType)
{}

TLevel::TLevel(const TLevelInfo& info, GE::TGameEngine& engine) :
    common(info.common),
    clock(Clock::Rate::Pause),
    scene(info.scene, &engine),
    gameEngine(&engine)
{
    loadScript(info);
}

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
    GE::TGameEngine::Context context(gameEngine, &scene.GetRaw());
    for(auto i = 0; i < (uint)clock.GetRate(); ++i) {
        gameEngine->Update(clock.tick(), context);
        clock.Update();
    }
}

void TLevel::SetGameEngine(GE::TGameEngine* instance) {
    gameEngine = instance;
}

void TLevel::loadScript(const TLevelInfo& info) {
    ASSERT(gameEngine != nullptr, "Game engine must be set");

    auto& scriptEngine = gameEngine->GetScriptEngine();
    const auto& script = info.common.loadingScript;

    if (script.empty() == false) {
        scriptEngine.Get().runFile(script);
        lua_binding::loadLevel(scriptEngine.Get(), &level);
    }
}

} // namespace TD
