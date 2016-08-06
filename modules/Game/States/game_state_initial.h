#ifndef GAME_STATE_INITIAL_H
#define GAME_STATE_INITIAL_H

#include "Game/States/game_state.h"
#include "GameEngine/game_engine.h"


namespace TD {


class TGameState_Initial : public TGame::State
{
public:
    TGameState_Initial(TGame* game);

    virtual void Update() override;
    virtual void Draw(Graphics::TRenderTarget& target) override;
    virtual void HandleEvent(const TApplication::Event& event) override;

private:
    using parent_type = TGame::State;

    void setUpGameEngine(GE::TGameEngine& engine);
    void setUpComponentSystems(GE::TComponentSystems& manager);
    void setUpComponentRegistry(GE::TComponentRegistry& registry);
};


} // namespace TD

#endif // GAME_STATE_INITIAL_H
