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

    virtual void Update(const TTime& step) override;

    void SetScriptEngine(TScriptEngine* instance);
    void SetScene(TScene* instance);
private:
    using ScriptEngine = TScriptEngine;
    using PScriptEngine = TScriptEngine*;
    PScriptEngine scriptEngine;

    using Scene = TScene;
    using PScene = TScene*;
    PScene scene;
};

class CLogicsComponent :
    public TComponent /*Abstract*/
{
public:
    CLogicsComponent(const ID& id);
    virtual ~CLogicsComponent() = default;

    virtual void Update(TScene* scene);
};

} //namespace GE

#endif // COMPONENT_SYSTEM_LOGICS_H
