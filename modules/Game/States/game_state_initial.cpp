#include "game_state_initial.h"
#include "game_state_level_loading.h"
#include "Game/Level/level_lua_binding.h"



namespace TD {


TGameState_Initial::TGameState_Initial(TGame* game) :
    parent_type(game)
{}

void TGameState_Initial::Update() {
    ASSERT(game != nullptr, "Game instance must be set")

    game->gameEngine.GetComponentSystems().
        ui.SetApplicationUI(&app->getUI());

    TD::lua_binding::bindToLUA(
        game->gameEngine.GetScriptEngine().Get());


    auto* nextState = new TGameState_LevelLoading(game);
    game->setState(nextState);
}

void TGameState_Initial::Draw(Graphics::TRenderTarget& target) {/*none*/}

void TGameState_Initial::HandleEvent(const TApplication::Event& event) {/*none*/}


}
