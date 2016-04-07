#include "level_loader.h"
#include "level.h"
#include "GameEngine/game_engine.h"
#include "level_lua_binding.h"



namespace TD {


void TLevel::Loader::loadInfo(TLevel& level, TLevelCode& code) {
    level.info = std::move(TLevelInfo(code));
}

void TLevel::Loader::loadScript(TLevel& level) {
    auto& scriptEngine = level.gameEngine.GetScriptEngine();
    const auto& script = level.info.GetCommonInfo().GetScript();

    if (script.empty() == false) {
        scriptEngine.Get().runFile(script);
        lua_binding::loadLevel(scriptEngine.Get(), &level);
    }
}

void TLevel::Loader::loadScene(TLevel& level) {
    level.scene.SetGameEngine(level.gameEngine);
    //TODO: resources loading?
}

void TLevel::Loader::load(TLevel& level,
    TLevelCode& code, TGameEngine* engine)
{
    ASSERT(engine != nullptr, "Game engine must be set")

    level.SetGameEngine(engine);
    loadInfo(level, code);
    loadScript(level);
    loadScene(level);
    level.clock.SetRate(Clock::Rate::Pause);
}


} // namespace TD
