#include "Game/Components/health_component.h"
#include "Game/Components/components_list.h"


const GE::ComponentIDs GE::ComponentID<TD::CHealth>::value =
    GE::ComponentIDs::Health;

const GE::ComponentSystem GE::ComponentClass<TD::CHealth>::value =
    GE::ComponentSystem::data;


namespace TD {

std::unique_ptr<GE::TComponent>
CHealth::Create(const GE::TComponentCreateArgs* args) {
    const auto* args = dynamic_cast<const Parameters*>(args_);
    if ((args_ != nullptr) && (args == nullptr)) {
        THROW("Wrong args passed to function.");
    }
    return std::unique_ptr<GE::TComponent>(new CHealth(args));
}

CHealth::CHealth(const CHealth::Parameters* args) :
    actualHealth(0),
    maxHealth(0)
{
    if (args != nullptr) {
        actualHealth = args->actualHealth;
        maxHealth = args->maxHealth;
    }
}

void CHealth::HandleMessage(const GE::TMessage& message, Context& context) {
    //TODO: ...
}

forward_list<GE::TMessage::ID> CHealth::GetAcceptedMessages() const {
    //TODO: ...
}

const CHealth::Health& CHealth::GetActualHealth() const {
    return actualHealth;
}

void CHealth::SetActualHealth(const Health& value) {
    actualHealth = value;
}

const CHealth::Health& CHealth::GetMaxHealth() const {
    return maxHealth;
}

void CHealth::SetMaxHealth(const Health& value) {
    maxHealth = value;
}

} // namespace TD

TD::CS::RegisterComponentClass<CHealth>();
