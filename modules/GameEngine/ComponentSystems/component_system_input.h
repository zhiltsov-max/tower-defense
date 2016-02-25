#ifndef COMPONENT_SYSTEM_INPUT_H
#define COMPONENT_SYSTEM_INPUT_H

#include "GameEngine/component_system.h"



class CSInputSystem : public TComponentSystem
{
public:
    virtual ~CSInputSystem() = default;
};


class CInputComponent : public TComponent /*Abstract*/
{
public:
    CInputComponent(const ID& id);
    virtual ~CInputComponent();
};

#endif // COMPONENT_SYSTEM_INPUT_H
