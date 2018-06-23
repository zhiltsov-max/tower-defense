#ifndef COMPONENT_SYSTEM_GRAPHICS_H
#define COMPONENT_SYSTEM_GRAPHICS_H

#include "GameEngine/ECS/component_system.h"


GE_BEGIN_ENGINE_NAMESPACE

class CSGraphicsSystem :
    public TComponentSystem
{
public:
    virtual ~CSGraphicsSystem() = default;

    virtual void Update(const TTime& step, Context& context) override;
    virtual void Render(Graphics::TRenderTarget& target);
    virtual void HandleMessage(const TMessage& message,
        const TComponentHandle& sender, Context& context) override;
};

GE_END_ENGINE_NAMESPACE

#endif // COMPONENT_SYSTEM_GRAPHICS_H
