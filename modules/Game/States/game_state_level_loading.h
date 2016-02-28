#ifndef GAME_STATE_LEVEL_LOADING_H
#define GAME_STATE_LEVEL_LOADING_H

#include "game_state.h"



namespace TD {


class TGameState_LevelLoading : public TGame::State
{
public:
    TGameState_LevelLoading(TGame* game);

    virtual void Update() override;
    virtual void Draw(Graphics::TRenderTarget& target) override;
    virtual void HandleEvent(const TApplication::Event& event) override;

private:
    using parent_type = TGame::State;

    void loadDataFromPreviousLevel(TLevel& newLevel, TLevel& previous);
};


} // namespace TD

#endif // GAME_STATE_LEVEL_LOADING_H
