#include "component_systems.h"
#include "GameEngine/game_engine.h"


namespace GE {

TComponentSystems::TComponentSystems(TGameEngine* engine) :
    input(),
    movement(),
    logics(),
    graphics(),
    sound(),
    ui(),
    data(),
    systems()
{
    systems[static_cast<TComponentSystemTypeId>(ComponentSystem::data)] = &data;
    systems[static_cast<TComponentSystemTypeId>(ComponentSystem::graphics)] =
        &graphics;
    systems[static_cast<TComponentSystemTypeId>(ComponentSystem::input)] =
        &input;
    systems[static_cast<TComponentSystemTypeId>(ComponentSystem::logics)] =
        &logics;
    systems[static_cast<TComponentSystemTypeId>(ComponentSystem::movement)] =
        &movement;
    systems[static_cast<TComponentSystemTypeId>(ComponentSystem::sound)] =
        &sound;
    systems[static_cast<TComponentSystemTypeId>(ComponentSystem::ui)] = &ui;

    SetGameEngine(engine);
}

void TComponentSystems::SetGameEngine(TGameEngine* instance) {
    for (auto* system : systems) {
        system->SetComponentRegistry(&instance->GetComponentRegistry());
    }
}

} //namespace GE
