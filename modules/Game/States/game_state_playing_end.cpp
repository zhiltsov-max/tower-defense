#include "game_state_playing_end.h"
#include "Game/Level/level.h"
#include "Game/Level/level_lua_binding.h"
#include "game_state_level_loading.h"
#include "game_state_exit.h"



namespace TD {


TGameState_PlayingEnd::TGameState_PlayingEnd(TGame* game) :
    parent_type(game)
{}

void TGameState_PlayingEnd::Update() {
    ASSERT(game != nullptr, "Game instance must be set")
    if (game->world == nullptr) {
        return;
    }

    const TLevelInfo& info = game->world->GetInfo();
    auto& script = info.GetCommonInfo().GetScript();
    if (script.empty() == false) {
        lua_binding::finalizeStage(
            game->gameEngine.GetScriptEngine().Get(),
            game->world, game->gameEngine);
    }

    TGame::State* nextState = nullptr;
    if (game->world->GetProgress().IsLevelCompleted() == true) { // no stages left
        const auto& nextLevel = info.GetCommonInfo().GetNextLevelCode();
        if (nextLevel.empty() == false) {
            nextState = new TGameState_LevelLoading(game);
        } else {
            nextState = new TGameState_Exit(game);
        }
    } else { // one more stage
        nextState = new TGameState_StageLoading(game);
    }
    game->setState(nextState);
}

void TGameState_PlayingEnd::Draw(Graphics::TRenderTarget& target) {
    /*none*/
}

void TGameState_PlayingEnd::HandleEvent(const TApplication::Event& event) {
    /*none*/
}


} // namespace TD
