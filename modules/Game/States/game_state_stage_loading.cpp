#include "game_state_stage_loading.h"
#include "game_state_playing.h"



namespace TD {

TGameState_StageLoading::TGameState_StageLoading(TGame* game) :
    parent_type(game)
{}

void TGameState_StageLoading::Update() {
    ASSERT(game != nullptr, "Game instance must be set")
    ASSERT(game->world != nullptr, "Game world instance must be set")


    auto& scriptEngine = game->gameEngine.GetScriptEngine();
    const auto& script = level->GetInfo().getCommonInfo().getScript();

    if (script.empty() == false) {
        lua_binding::loadStage(scriptEngine.Get(), game->world);
    }

    auto* nextState = new TGameState_Playing(game);
    game->setState(nextState);
}

void TGameState_StageLoading::Draw(Graphics::TRenderTarget& target) {
    1//TO DO: loading screen
}

void TGameState_StageLoading::HandleEvent(const TApplication::Event& event) {
    /*none*/
}


} // namespace TD
