#include "component_system_logics.h"
#include "GameEngine/script_engine.h"
#include "GameEngine/scene.h"


namespace GE {

void CSLogicsSystem::Update(const TTime& step) {
    for (auto& component : components) {
        static_cast<CLogicsComponent*>(component.get())->Update(scene);
    }
}

void CSLogicsSystem::SetScriptEngine(TScriptEngine* instance) {
    scriptEngine = instance;
}

void GE::CSLogicsSystem::SetScene(GE::TScene* instance) {
    scene = instance;
}

CLogicsComponent::CLogicsComponent(const TComponent::ID& id) :
    TComponent(id)
{}

} //namespace GE
