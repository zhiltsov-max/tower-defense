#include "game_state_statistics.h"
#include "game_state_playing_end.h"



namespace TD {


TGameState_Statistics::TGameState_Statistics(TGame* game) :
    parent_type(game)
{}

void TGameState_Statistics::Update() {
    ASSERT(game != nullptr, "Game instance must be set")
    if (game->world == nullptr) {
        return;
    }

    1//TODO: prepare statistics window


}

void TGameState_Statistics::Draw(Graphics::TRenderTarget& target) {
    1
}

void TGameState_Statistics::HandleEvent(const TApplication::Event& event) {
    switch (event.type) {
    case sf::Event::KeyReleased:
        switch (event.key.code) {
        case sf::Keyboard::Escape:
            auto* nextState = new TGameState_PlayingEnd(game);
            game->setState(nextState);
            break;

        default: {/*none*/}
        }
        break;

    default: {/*none*/}
    }
}


} // namespace TD
