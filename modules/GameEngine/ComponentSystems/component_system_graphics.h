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
    virtual void Render(Graphics::TRenderTarget& target);

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

    /*
    This method should be used to perform all computations needed to render this
    component. The data used after in rendering should be saved.
    a) May be used to implement 'presenter' logics in MVP model.
    b) May be left empty to implement 'passive view' pattern in the case of
    existence of additional specific 'presenter'.
    */
    virtual void Update(const TTime& step, Context& context);

    /*
    Renders this component data to render target.
    */
    virtual void Render(Graphics::TRenderTarget& target) = 0;
};

} //namespace GE

#endif // COMPONENT_SYSTEM_GRAPHICS_H
