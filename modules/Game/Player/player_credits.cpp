#include "player_credits.h"


namespace TD {

std::unique_ptr<GE::TComponent>
CPlayerCredits::Create(const GE::TComponentCreateArgs* args_) {
    const auto* args = dynamic_cast<TPlayerCreditsInfo*>(args_);
    ASSERT(args != nullptr, "Wrong constructor parameters.")
    return new CPlayerCredits(*args);
}

CPlayerCredits::CPlayerCredits(const TPlayerCreditsInfo& info) :
    parent_type(GE::ComponentID<CPlayerCredits>::value),
    credits(info.startValue)
{}

void CPlayerCredits::HandleMessage(const TMessage& message) {
    //TODO: ...
}

void CPlayerCredits::Subscribe(TComponentSystem& system) {
    //TODO: ...
}

void CPlayerCredits::Unsubscribe(TComponentSystem& system) {
    //TODO: ...
}

const CPlayerCredits::Credits&CPlayerCredits::GetCredits() const {
    return credits;
}

void CPlayerCredits::SetCredits(const CPlayerCredits::Credits& value) {
    if (credits != value) {
        credits = value;
        // TODO: send message "changed"
    }
}

} // namespace TD
