#ifndef COMPONENT_SYSTEM_MOVEMENT_H
#define COMPONENT_SYSTEM_MOVEMENT_H

#include "GameEngine/component_system.h"



class CSMovementSystem : public TComponentSystem
{
public:
    virtual ~CSMovementSystem() = default;

    virtual void Update(const TTime& step) override;
};


class CMovementComponent : public TComponent /*Abstract*/
{
public:
    CMovementComponent(const ID& id);
    virtual ~CMovementComponent();
};

#endif // COMPONENT_SYSTEM_MOVEMENT_H
