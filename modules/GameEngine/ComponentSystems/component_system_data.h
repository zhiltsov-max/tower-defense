#ifndef COMPONENT_SYSTEM_DATA_H
#define COMPONENT_SYSTEM_DATA_H

#include "GameEngine/component_system.h"


namespace GE {

class CSDataSystem :
    public TComponentSystem
{
public:
    virtual ~CSDataSystem() = default;

    virtual void Update(const TTime& step, Context& context) override;
};

class CDataComponent : /*Abstract*/
    public TComponent
{
public:
    CDataComponent(const ID& id);
    virtual ~CDataComponent() = default;
};

} //namespace GE

#endif // COMPONENT_SYSTEM_DATA_H
