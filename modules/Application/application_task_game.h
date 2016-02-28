#ifndef APPLICATION_TASK_GAME_H
#define APPLICATION_TASK_GAME_H

#include "application_task.h"
#include "Core/core.h"
#include "GameEngine/game_engine.h"
#include "debug.h"



namespace TD {
class TLevel;
class TPlayer;
} // namespace TD


class TGame : public TTDApplicationTask
{
public:
    TGame(TTowerDefenseApplication* app);

    virtual const TDAppState& GetCode() const override;

    virtual void Update() override;
    virtual void Draw(Graphics::TRenderTarget& target) override;
    virtual void HandleEvent(const TApplication::Event& event) override;

private:
    typedef TTDApplicationTask parent_type;

    using DebugTools = TDebugTools;
    DebugTools debugTools;

    using GameEngine = TGameEngine;
    GameEngine gameEngine;

    using GameWorld = TD::TLevel;
    using PGameWorld = std::unique_ptr<GameWorld>;
    PGameWorld world;

    using Player = TD::TPlayer;
    using PPlayer = std::unique_ptr<Player>;
    PPlayer player;

    class State;
    using PState = std::unique_ptr<State>;
    PState state;


    void setState(State* value);
    const State* getState() const;
    State* getState();

    void exit();
};


#endif // APPLICATION_TASK_GAME_H
