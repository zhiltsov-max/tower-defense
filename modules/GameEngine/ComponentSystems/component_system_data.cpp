#include "component_system_data.h"


namespace GE {

void CSDataSystem::Update(const TTime& step, Context& context) { /*none*/ }

CDataComponent::CDataComponent(const TComponent::ID& id) :
    TComponent(id)
{}

void CDataComponent::HandleMessage(const TMessage& message, Context& context) {
    /*none*/
}

forward_list<TMessage::ID> CDataComponent::GetAcceptedMessages() {
    return forward_list<TMessage::ID>();
}

} //namespace GE
