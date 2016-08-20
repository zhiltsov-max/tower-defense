#include "component_system_ui.h"
#include "GameEngine/script_engine.h"
#include "Application/application_ui.h"
#include "GUI/uiparent.h"


namespace GE {

CSUiSystem::~CSUiSystem() {
    if (ui != nullptr) {
        ui->getUIParent()->RemoveChildren();
    }
}

void CSUiSystem::Update(const TTime& step, Context& context) {
    if (ui != nullptr) {
        ui->update();
    }

    UNUSED(step);
    UNUSED(context);
}

void CSUiSystem::Draw(Graphics::TRenderTarget& target) {
    if (ui != nullptr) {
        ui->draw();
    }

    UNUSED(target);
}

void CSUiSystem::SetScriptEngine(TScriptEngine* instance) {
    scriptEngine = instance;
}

void CSUiSystem::SetApplicationUI(TApplicationUI* instance) {
    ui = instance;
}


CUiComponent::CUiComponent(const TComponent::ID& id) :
    TComponent(id)
{}

} // namespace GE
