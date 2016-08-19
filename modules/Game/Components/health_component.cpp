#include "Game/Components/health_component.h"


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

} // namespace TD
