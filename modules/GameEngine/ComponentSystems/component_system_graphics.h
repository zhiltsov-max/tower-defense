#ifndef COMPONENT_SYSTEM_GRAPHICS_H
#define COMPONENT_SYSTEM_GRAPHICS_H

#include "GameEngine/component_system.h"


namespace GE {

class CSGraphicsSystem :
    public TComponentSystem
{
public:
    virtual ~CSGraphicsSystem() = default;

    virtual void Update(const TTime& step, Context& context) override;
    virtual void Draw(Graphics::TRenderTarget& target);

    void SetScene(TScene* instance);

private:
    using Scene = TScene;
    using PScene = TScene*;
    PScene scene;
};

class CGraphicsComponent : /*Abstract*/
    public TComponent
{
public:
    CGraphicsComponent(const ID& id);
    virtual ~CGraphicsComponent() = default;

    virtual void Draw(Graphics::TRenderTarget& target, const TScene* scene) = 0;
};

} //namespace GE

#endif // COMPONENT_SYSTEM_GRAPHICS_H
