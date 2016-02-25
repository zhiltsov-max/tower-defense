#ifndef COMPONENT_SYSTEM_LOGICS_H
#define COMPONENT_SYSTEM_LOGICS_H

#include "GameEngine/component_system.h"



class TScriptEngine;

class CSLogicsSystem : public TComponentSystem
{
public:
    virtual ~CSLogicsSystem() = default;

    void SetScriptEngine(TScriptEngine* instance);

private:
    using ScriptEngine = TScriptEngine;
    using PScriptEngine = ScriptEngine *;
    PScriptEngine scriptEngine;
};


class CLogicsComponent : public TComponent /*Abstract*/
{
public:
    CLogicsComponent(const ID& id);
    virtual ~CLogicsComponent();
};

#endif // COMPONENT_SYSTEM_LOGICS_H
