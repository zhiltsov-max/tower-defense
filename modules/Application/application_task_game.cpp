#include "application_task_game.h"
#include "GameEngine/engine_messages.h"
#include "Game/States/game_states.h"
#include "Game/Level/level.h"
#include "Game/Player/player.h"



using namespace TD;

TGame::TGame(TTowerDefenseApplication* app) :
    parent_type(app),
    debugTools(),
    gameEngine(),
    world(nullptr),
    player(nullptr),
    state(new TGameState_Initial(this))
{}

const TDAppState& TGame::GetCode() const {
    return TDAppState::Game;
}

void TGame::Update() {
#if defined(_DEBUG)
    ASSERT(state != nullptr, "Unexpected state of game.")
#else //_DEBUG
    if (state == nullptr) {
        return;
    }
#endif //_DEBUG

    state->Update();
}

void TGame::Draw(Graphics::TRenderTarget& target) {
#if defined(_DEBUG)
    ASSERT(state != nullptr, "Unexpected state of game.")
#else //_DEBUG
    if (state == nullptr) {
        return;
    }
#endif //_DEBUG

    state->Draw(target);
}

void TGame::HandleEvent(const TApplication::Event& event) {
#if defined(_DEBUG)
    ASSERT(state != nullptr, "Unexpected state of game.")
#else //_DEBUG
    if (state == nullptr) {
        return;
    }
#endif //_DEBUG

    state->HandleEvent(event);
}

void TGame::setState(State* value) {
#if defined(_DEBUG)
    ASSERT(value != nullptr, "Unexpected state of game.")
#else //_DEBUG
    if (value == nullptr) {
        return;
    }
#endif //_DEBUG

    state.reset(value);
}

const TGame::State*TGame::getState() const {
    return state.get();
}

TGame::State*TGame::getState() {
    return state.get();
}

void TGame::exit() {
    app->SetState(TDAppState::Menu);
}
