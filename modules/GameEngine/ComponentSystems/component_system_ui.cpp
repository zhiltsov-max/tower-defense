#include "component_system_ui.h"
#include "GameEngine/script_engine.h"
#include "Application/application_ui.h"



CSUiSystem::~CSUiSystem() {
    if (ui != nullptr) {
        ui->getUIParent()->RemoveChildren();
    }
}

void CSUiSystem::Update(const TTime& step) {
    if (ui != nullptr) {
        ui->update();
    }
    parent_type::Update(step);
}

void CSUiSystem::Draw(Graphics::TRenderTarget& target) {
    if (ui != nullptr) {
        ui->draw();
    }

    UNUSED(target)
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
