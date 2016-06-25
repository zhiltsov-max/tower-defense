#ifndef COMPONENT_SYSTEM_LOGICS_H
#define COMPONENT_SYSTEM_LOGICS_H

#include "GameEngine/component_system.h"


namespace GE {

class TScene;
class TScriptEngine;

class CSLogicsSystem :
    public TComponentSystem
{
public:
    virtual ~CSLogicsSystem() = default;

    virtual void Update(const TTime& step, Context& context) override;
};

class CLogicsComponent : /*Abstract*/
    public TComponent
{
public:
    CLogicsComponent(const ID& id);
    virtual ~CLogicsComponent() = default;

    virtual void Update(const TTime& step, Context& context) = 0;
};

} //namespace GE

#endif // COMPONENT_SYSTEM_LOGICS_H
