#ifndef COMPONENT_SYSTEM_UI_H
#define COMPONENT_SYSTEM_UI_H

#include "GameEngine/component_system.h"



class TScriptEngine;
class TApplicationUI;

class CSUiSystem : public TComponentSystem
{
public:
    virtual ~CSUiSystem();

    virtual void Update(const TTime& step) override;
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


class CUiComponent : public TComponent /*Abstract*/
{
public:
    CUiComponent(const ID& id);
    virtual ~CUiComponent();
};

#endif // COMPONENT_SYSTEM_UI_H
