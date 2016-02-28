#ifndef GAME_STATE_STAGELOADING_H
#define GAME_STATE_STAGELOADING_H

#include "game_state.h"



namespace TD {


class TGameState_StageLoading : public TGame::State
{
public:
    TGameState_StageLoading(TGame* game);

    virtual void Update() override;
    virtual void Draw(Graphics::TRenderTarget& target) override;
    virtual void HandleEvent(const TApplication::Event& event) override;

private:
    using parent_type = TGame::State;
};


} // namespace TD

#endif // GAME_STATE_STAGELOADING_H
