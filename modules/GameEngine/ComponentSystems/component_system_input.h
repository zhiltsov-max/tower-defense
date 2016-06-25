#ifndef COMPONENT_SYSTEM_INPUT_H
#define COMPONENT_SYSTEM_INPUT_H

#include "GameEngine/component_system.h"


namespace GE {

class CSInputSystem :
    public TComponentSystem
{
public:
    virtual ~CSInputSystem() = default;

    virtual void Update(const TTime& step, Context& context) override;
};

class CInputComponent : /*Abstract*/
    public TComponent
{
public:
    CInputComponent(const ID& id);
    virtual ~CInputComponent() = default;

    virtual Update(Context& context) = 0;
};

} //namespace GE

#endif // COMPONENT_SYSTEM_INPUT_H
