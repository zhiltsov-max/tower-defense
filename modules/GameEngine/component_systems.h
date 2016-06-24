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

enum class ComponentSystem : uchar {
    _min = 0,

    input = 0,
    movement = 1,
    logics = 2,
    graphics = 3,
    sound = 4,
    ui = 5,
    data = 6,

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
        static_cast<uchar>(ComponentSystem::_count)>;
    Systems systems;

    TComponentSystems(TGameEngine* engine);
};

} //namespace GE

#endif // COMPONENT_SYSTEMS_H
