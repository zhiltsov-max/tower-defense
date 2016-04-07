#include "game_state_level_loading.h"
#include "game_state_stage_loading.h"
#include "Game/Level/level.h"
#include "Game/Player/player.h"



namespace TD {


TGameState_LevelLoading::TGameState_LevelLoading(TGame* game) :
    parent_type(game)
{}

void TGameState_LevelLoading::Update() {
    ASSERT(game != nullptr, "Game instance must be set")

    TLevel* level = new TLevel(game, code);
    if (game->world != nullptr) {
        level->LoadFromPrevious(*level);
    }
    game->world.reset(level);

    TPlayer* player = game->player.get();
    if (player == nullptr) {
        game->player.reset(new TPlayer);
        player = game->player.get();
    }
    player->LoadDataFromLevel(level, game->world);

    auto* nextState = TGameState_StageLoading(game);
    game->setState(nextState);
}

void TGameState_LevelLoading::Draw(Graphics::TRenderTarget& target) {
    //TODO: loading screen
}

void TGameState_LevelLoading::HandleEvent(const TApplication::Event& event) {
    /*none*/
}

void TGameState_LevelLoading::loadDataFromPreviousLevel(
    TLevel& newLevel, TLevel& previous)
{
    1
}


} //namespace TD
