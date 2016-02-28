#include "game_state_playing.h"
#include "Game/Level/level_lua_binding.h"
#include "game_state_statistics.h"



namespace TD {


TGameState_Playing::TGameState_Playing(TGame* game) :
    parent_type(game)
{}

void TGameState_Playing::Update() {
    ASSERT(game != nullptr, "Game must be specified")
    ASSERT(game->world != nullptr, "World must be created")

    if (game->player->GetProgress().IsGameOver() == true) {
        auto* nextState = new TGameState_Statistics(game);
        game->setState(nextState);
        return;
    }

    game->world->Update();
}

void TGameState_Playing::Draw(Graphics::TRenderTarget& target) {
    if (game == nullptr) {
        return;
    }

    game->gameEngine.Draw(target);
}

void TGameState_Playing::HandleEvent(const TApplication::Event& event) {
    if (game == nullptr) {
        return;
    }

    const auto message = TMessage_SystemEvent(event);
    game->gameEngine->SendMessage(message);
}


} // namespace TD
