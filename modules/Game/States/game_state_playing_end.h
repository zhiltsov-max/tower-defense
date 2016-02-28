#ifndef GAME_STATE_PLAYING_END_H
#define GAME_STATE_PLAYING_END_H

#include "game_state.h"



namespace TD {

class TGameState_PlayingEnd : public TGame::State
{
public:
    TGameState_PlayingEnd(TGame* game);

    virtual void Update() override;
    virtual void Draw(Graphics::TRenderTarget& target) override;
    virtual void HandleEvent(const TApplication::Event& event) override;

private:
    using parent_type = TGame::State;
};

} // namespace TD

#endif // GAME_STATE_PLAYING_END_H
