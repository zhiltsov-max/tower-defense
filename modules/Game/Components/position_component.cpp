#include "Game/Components/position_component.h"


namespace TD {

std::unique_ptr<GE::TComponent>
CPosition2d::Create(const GE::TComponentCreateArgs* args_) {
    const auto* args = dynamic_cast<const Parameters*>(args_);
    if ((args_ != nullptr) && (args == nullptr)) {
        THROW("Wrong args passed to function.");
    }
    return std::unique_ptr<GE::TComponent>(new CPosition2d(args));
}

CPosition2d::CPosition2d(const Parameters* args) :
    position(0, 0),
    rotation(0)
{
    if (args != nullptr) {
        position = args->position;
        rotation = args->rotation;
    }
}

} // namespace TD
