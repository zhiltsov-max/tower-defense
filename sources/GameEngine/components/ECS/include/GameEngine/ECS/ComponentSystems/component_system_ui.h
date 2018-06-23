#ifndef COMPONENT_SYSTEM_UI_H
#define COMPONENT_SYSTEM_UI_H

#include "GameEngine/ECS/component_system.h"


class TApplicationUI;

GE_BEGIN_ENGINE_NAMESPACE

class TScriptEngine;

class CSUiSystem :
    public TComponentSystem
{
public:
    virtual ~CSUiSystem();

    virtual void Update(const TTime& step, Context& context) override;
    void Draw(Graphics::TRenderTarget& target);

    void SetScriptEngine(TScriptEngine* instance);
    void SetApplicationUI(TApplicationUI* instance);

private:
    using parent_type = TComponentSystem;
    using ScriptEngine = TScriptEngine;
    using PScriptEngine = ScriptEngine *;
    PScriptEngine scriptEngine;

    using Ui = TApplicationUI;
    using PUi = Ui *;
    PUi ui;
};

class CUiComponent :
    public TComponent
{
public:
    CUiComponent(const ID& id);
    virtual ~CUiComponent() = default;
};

GE_END_ENGINE_NAMESPACE

#endif // COMPONENT_SYSTEM_UI_H