#include "player_researches.h"



namespace TD {


std::unique_ptr<TComponent> CPlayerResearches::Create(TComponentCreateArgs* args_) {
    auto* args = dynamic_cast< TPlayerResearchesInfo* >(args_);
    ASSERT(args != nullptr, "Arguments is expected.")

    return new CPlayerResearches(*args);
}

CPlayerResearches::CPlayerResearches(const TPlayerResearchesInfo& args) :
    parent_type(ComponentID<CPlayerResearches>::value),
    level(args.level),
    model(),
    view()
{
    model.Load(level);
    view
}

void CPlayerResearches::Update() {
    /*none*/
}

void CPlayerResearches::HandleMessage(const TMessage& message) {
    1
}

void CPlayerResearches::Subscribe(TComponentSystem& system) {
    1
}

void CPlayerResearches::Unsubscribe(TComponentSystem& system) {
    1
}

const TResearchesTree&CPlayerResearches::GetTree() const {
    return model;
}


} // namespace TD
