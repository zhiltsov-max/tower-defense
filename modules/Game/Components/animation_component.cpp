#include "Game/Components/animation_component.h"


namespace TD {

std::unique_ptr<GE::TComponent> CAnimation::Create(
    const GE::TComponentCreateArgs* args_)
{
    const auto* args = dynamic_cast<const Parameters*>(args_);
    if ((args_ != nullptr) && (args == nullptr)) {
        THROW("Wrong args passed to function.");
    }
    return std::unique_ptr<GE::TComponent>(new CAnimation(args));
}

CAnimation::CAnimation(const Parameters* parameters) :
    parent_type(GE::ComponentID<CAnimation>::value),
    resource(),
    currentFrame(0),
    actionIndex(0),
    speed(0),
    repeats(0)
{
    if (parameters != nullptr) {
        resource = parameters->resource;
        actionIndex = parameters->defaultActionIndex;
        speed = parameters->defaultSpeed;
        repeats = parameters->repeats;
    }
}

} // namespace TD
