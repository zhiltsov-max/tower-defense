#include "component_system_data.h"


namespace GE {

void CSDataSystem::Update(const TTime& step, Context& context) { /*none*/ }

CDataComponent::CDataComponent(const TComponent::ID& id) :
    TComponent(id)
{}

} //namespace GE
