#ifndef COMPONENT_SYSTEMS_H
#define COMPONENT_SYSTEMS_H

#include "component_system.h"
#include "ComponentSystems/component_system_input.h"
#include "ComponentSystems/component_system_sound.h"
#include "ComponentSystems/component_system_movement.h"
#include "ComponentSystems/component_system_logics.h"
#include "ComponentSystems/component_system_graphics.h"
#include "ComponentSystems/component_system_ui.h"



enum class ComponentSystem : uchar {
    _min = 0,

    input = 0,
    movement = 1,
    logics = 2,
    graphics = 3,
    sound = 4,
    ui = 5,

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

    using Systems = std::array<TComponentSystem*, (uchar) ComponentSystem::_count>;
    Systems systems;


    TComponentSystems(const TGameEngine* engine);
};

#endif // COMPONENT_SYSTEMS_H
