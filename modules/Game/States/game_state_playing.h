#ifndef GAME_STATE_PLAYING_H
#define GAME_STATE_PLAYING_H

#include "Game/States/game_state.h"


namespace TD {

class TGameState_Playing : public TGame::State
{
public:
    TGameState_Playing(TGame* game);

    virtual void Update() override;
    virtual void Draw(Graphics::TRenderTarget& target) override;
    virtual void HandleEvent(const TApplication::Event& event) override;

private:
    using parent_type = TGame::State;
};

} // namespace TD

#endif // GAME_STATE_PLAYING_H
