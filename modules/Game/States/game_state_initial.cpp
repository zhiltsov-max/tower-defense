#include "game_state_initial.h"
#include "Game/States/game_state_level_loading.h"
#include "Game/Level/level_lua_binding.h"
#include "Game/Components/td_components_registry.h"
#include "Game/ComponentSystems/td_component_systems.h"


namespace TD {

TGameState_Initial::TGameState_Initial(TGame* game) :
    parent_type(game)
{}

void TGameState_Initial::Update() {
    ASSERT(game != nullptr, "Game instance must be set")

    setUpGameEngine(game->gameEngine);


    auto* nextState = new TGameState_LevelLoading(game);
    game->setState(nextState);
}

void TGameState_Initial::Draw(Graphics::TRenderTarget& target) {/*none*/}

void TGameState_Initial::HandleEvent(const TApplication::Event& event) {/*none*/}

void TGameState_Initial::setUpGameEngine(GE::TGameEngine& engine) {
    setUpComponentSystems(engine.GetComponentSystems());
    setUpComponentRegistry(engine.GetComponentRegistry());
    lua_binding::bindToLUA(engine.GetScriptEngine().Get());
}

void TGameState_Initial::setUpComponentSystems(GE::TComponentSystems& manager) {
    manager.AddSystem<GE::CSInputSystem>(GE::ComponentSystem::input);
    manager.AddSystem<GE::CSMovementSystem>(GE::ComponentSystem::movement);
    manager.AddSystem<GE::CSDataSystem>(GE::ComponentSystem::data);
    manager.AddSystem<GE::CSLogicsSystem>(GE::ComponentSystem::logics);
    manager.AddSystem<GE::CSGraphicsSystem>(GE::ComponentSystem::graphics);
    manager.AddSystem<GE::CSSoundSystem>(GE::ComponentSystem::sound);

    auto* ui = manager.AddSystem<GE::CSUiSystem>(GE::ComponentSystem::ui);
    ui->SetApplicationUI(&app->getUI());
}

void
TGameState_Initial::setUpComponentRegistry(GE::TComponentRegistry& registry) {
    registry = CS::GetComponentRegistry();
}

} // namespace TD
