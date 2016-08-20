#ifndef COMPONENT_SYSTEM_MOVEMENT_H
#define COMPONENT_SYSTEM_MOVEMENT_H

#include "GameEngine/component_system.h"


namespace GE {

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

} // namespace GE

#endif // COMPONENT_SYSTEM_MOVEMENT_H
