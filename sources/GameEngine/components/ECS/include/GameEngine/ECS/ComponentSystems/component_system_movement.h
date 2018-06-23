#ifndef COMPONENT_SYSTEM_MOVEMENT_H
#define COMPONENT_SYSTEM_MOVEMENT_H

#include "GameEngine/ECS/component_system.h"


GE_BEGIN_ENGINE_NAMESPACE

class CSMovementSystem :
    public TComponentSystem
{
public:
    virtual ~CSMovementSystem() = default;

    virtual void Update(const TTime& step, Context& context) override;
    virtual void HandleMessage(const TMessage& message,
        const TComponentHandle& sender, Context& context) override;
};


class CMovementComponent :
    public TComponent
{
public:
    CMovementComponent(const ID& id);
    virtual ~CMovementComponent() = default;
};

GE_END_ENGINE_NAMESPACE

#endif // COMPONENT_SYSTEM_MOVEMENT_H
