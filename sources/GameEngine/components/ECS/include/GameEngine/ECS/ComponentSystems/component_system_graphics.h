#ifndef COMPONENT_SYSTEM_GRAPHICS_H
#define COMPONENT_SYSTEM_GRAPHICS_H

#include "GameEngine/ECS/component_system.h"


namespace GE {

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

} // namespace GE

#endif // COMPONENT_SYSTEM_GRAPHICS_H
