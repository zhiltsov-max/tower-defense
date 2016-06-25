#ifndef COMPONENT_SYSTEMS_H
#define COMPONENT_SYSTEMS_H

#include "GameEngine/component_system.h"
#include "GameEngine/ComponentSystems/component_system_data.h"
#include "GameEngine/ComponentSystems/component_system_input.h"
#include "GameEngine/ComponentSystems/component_system_sound.h"
#include "GameEngine/ComponentSystems/component_system_movement.h"
#include "GameEngine/ComponentSystems/component_system_logics.h"
#include "GameEngine/ComponentSystems/component_system_graphics.h"
#include "GameEngine/ComponentSystems/component_system_ui.h"


namespace GE {

using TComponentSystemTypeId = uchar;
enum class ComponentSystem : TComponentSystemTypeId {
    _min = 0,

    input = 0,
    data,
    movement,
    logics,
    ui,
    graphics,
    sound,

    _count,
    _undefined = _count
};

template< class Component >
struct ComponentClass;

class TGameEngine;

struct TComponentSystems
{
    CSInputSystem input;
    CSMovementSystem movement;
    CSLogicsSystem logics;
    CSGraphicsSystem graphics;
    CSSoundSystem sound;
    CSUiSystem ui;
    CSDataSystem data;

    using Systems = std::array<TComponentSystem*,
        static_cast<TComponentSystemTypeId>(ComponentSystem::_count)>;
    Systems systems;

    TComponentSystems(TGameEngine* engine);

    void SetGameEngine(TGameEngine* instance);
};

} //namespace GE

#endif // COMPONENT_SYSTEMS_H
