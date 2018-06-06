#ifndef APPLICATION_TASK_GAME_H
#define APPLICATION_TASK_GAME_H

#include "Application/debug.h"
#include "Game/Application/application_task.h"
#include "Game/Level/level.h"
#include "GameEngine/game_engine.h"
#include "GameEngine/scene_object.h"


namespace TD {

class TGame :
    public TApplicationTask
{
public:
    TGame(TTowerDefenseApplication* app);

    virtual const TDAppState& GetCode() const override;

    virtual void Update() override;
    virtual void Draw(Graphics::TRenderTarget& target) override;
    virtual void HandleEvent(const TApplication::Event& event) override;

private:
    using parent_type = TApplicationTask;

    using GameEngine = GE::TGameEngine;
    GameEngine gameEngine;

    using PGameWorld = std::unique_ptr<TLevel>;
    GameWorld world;

    using Player = GE::TSceneObject;
    Player player;

    class State;
    using PState = std::unique_ptr<State>;
    PState state;

    void setState(State* value);
    const State* getState() const;
    State* getState();

    void exit();
};

} // namespace TD

#endif // APPLICATION_TASK_GAME_H
