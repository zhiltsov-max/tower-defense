#include "level.h"
#include "Game/Level/level_lua_binding.h"


namespace TD {

TLevel::CommonData::CommonData(const TLevel::Parameters::Common& info) :
    levelCode(info.levelCode),
    nextLevelCode(info.nextLevelCode),
    levelType(info.levelType)
{}

TLevel::TLevel(const Parameters& info, GE::TGameEngine* engine) :
    common(info.common),
    clock(Clock::Rate::Pause),
    scene(info.scene, engine),
    gameEngine(engine)
{
    if (engine != nullptr) {
        loadScript(info);
    }
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
    for(uint i = 0; i < static_cast<uint>(clock.GetRate()); ++i) {
        scene.Update(clock.tick());
        clock.Update();
    }
}

void TLevel::SetGameEngine(GE::TGameEngine* instance) {
    gameEngine = instance;
    scene.SetGameEngine(instance);
}

void TLevel::loadScript(const Parameters& info) {
    ASSERT(gameEngine != nullptr, "Game engine must be set");

    auto& scriptEngine = gameEngine->GetScriptEngine();
    const auto& script = info.common.loadingScript;

    if (script.empty() == false) {
        scriptEngine.Get().runFile(script);
        lua_binding::loadLevel(scriptEngine.Get(), this);
    }
}

} // namespace TD
