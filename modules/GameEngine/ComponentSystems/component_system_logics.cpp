#include "component_system_logics.h"
#include "GameEngine/script_engine.h"



namespace GE {


void CSLogicsSystem::SetScriptEngine(TScriptEngine* instance) {
    scriptEngine = instance;
}


CLogicsComponent::CLogicsComponent(const TComponent::ID& id) :
    TComponent(id)
{}


} //namespace GE
