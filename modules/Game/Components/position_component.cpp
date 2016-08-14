#include "Game/Components/position_component.h"
#include "Game/Components/components_list.h"


const GE::ComponentIDs GE::ComponentID<TD::CPosition2d>::value =
    GE::ComponentIDs::Position2d;

const GE::ComponentSystem GE::ComponentClass<TD::CPosition2d>::value =
    GE::ComponentSystem::data;

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

void CPosition2d::HandleMessage(const GE::TMessage& message, Context& context) {
    //TODO: ...
}

const CPosition2d::Position& CPosition2d::GetPosition() const {
    return position;
}

void CPosition2d::SetPosition(const Position& value) {
    position = value;
}

const CPosition2d::Rotation& CPosition2d::GetRotation() const {
    return rotation;
}

void CPosition2d::SetRotation(const Rotation& value) {
    rotation = value;
}

} // namespace TD

TD::CS::RegisterComponentClass<CPosition2d>();
