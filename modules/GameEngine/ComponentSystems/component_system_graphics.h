#ifndef COMPONENT_SYSTEM_GRAPHICS_H
#define COMPONENT_SYSTEM_GRAPHICS_H

#include "GameEngine/component_system.h"



class CSGraphicsSystem : public TComponentSystem
{
public:
    virtual ~CSGraphicsSystem() = default;

    virtual void Draw(Graphics::TRenderTarget& target);
};


class CGraphicsComponent : public TComponent /*Abstract*/
{
public:
    CGraphicsComponent(const ID& id);
    virtual ~CGraphicsComponent();
};

#endif // COMPONENT_SYSTEM_GRAPHICS_H
