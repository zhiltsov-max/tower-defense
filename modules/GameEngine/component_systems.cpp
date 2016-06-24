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
    systems({
        &input,
        &movement,
        &logics,
        &graphics,
        &sound,
        &ui,
        &data
    })
{
    input.SetRegistry(&engine->GetComponentRegistry());

    movement.SetRegistry(&engine->GetComponentRegistry());

    logics.SetRegistry(&engine->GetComponentRegistry());
    logics.SetScriptEngine(&engine->GetScriptEngine());

    graphics.SetRegistry(&engine->GetComponentRegistry());

    sound.SetRegistry(&engine->GetComponentRegistry());

    ui.SetRegistry(&engine->GetComponentRegistry());
    ui.SetScriptEngine(&engine->GetScriptEngine());

    data.SetRegistry(&engine->GetComponentRegistry());
}

} //namespace GE
