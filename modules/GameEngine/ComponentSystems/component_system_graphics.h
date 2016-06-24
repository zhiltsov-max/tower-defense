#ifndef COMPONENT_SYSTEM_GRAPHICS_H
#define COMPONENT_SYSTEM_GRAPHICS_H

#include "GameEngine/component_system.h"


namespace GE {

class CSGraphicsSystem :
    public TComponentSystem
{
public:
    virtual ~CSGraphicsSystem() = default;

    virtual void Update(const TTime& step) override;
    virtual void Draw(Graphics::TRenderTarget& target);
};

class CGraphicsComponent : /*Abstract*/
    public TComponent
{
public:
    CGraphicsComponent(const ID& id);
    virtual ~CGraphicsComponent() = default;
};

} //namespace GE

#endif // COMPONENT_SYSTEM_GRAPHICS_H
