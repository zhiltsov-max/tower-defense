#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "GameEngine/Utility/core.h"
#include "Application/application_task_game.h"


class TGame::State /*Abstract*/
{
public:
    State(TGame* game);
    virtual ~TGameState() = default;

    virtual void Update() = 0;
    virtual void Draw(Graphics::TRenderTarget& target) = 0;
    virtual void HandleEvent(const TApplication::Event& event) = 0;

protected:
    using PGame = TGame *;
    PGame game;
};


#endif // GAME_STATE_H

