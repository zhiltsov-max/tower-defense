#include "component_systems.h"
#include "game_engine.h"
#include <initializer_list>



TComponentSystems::TComponentSystems(TGameEngine* engine) :
    input(),
    movement(),
    logics(),
    graphics(),
    sound(),
    ui(),
    systems({
        &input,
        &movement,
        &logics,
        &graphics,
        &sound,
        &ui
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
}
