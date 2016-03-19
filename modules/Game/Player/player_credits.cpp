#include "player_credits.h"



namespace TD {


std::unique_ptr<TComponent> CPlayerCredits::Create(const TComponentCreateArgs* args) {
    return new CPlayerCredits;
    UNUSED(args)
}

CPlayerCredits::CPlayerCredits() :
    parent_type(),
    credits(0)
{}

void CPlayerCredits::Update() {
    /*none*/
}

void CPlayerCredits::HandleMessage(const TMessage& message) {
    1
}

void CPlayerCredits::Subscribe(TComponentSystem& system) {
    1
}

void CPlayerCredits::Unsubscribe(TComponentSystem& system) {
    1
}

const CPlayerCredits::Credits&CPlayerCredits::GetCredits() const {
    return credits;
}

void CPlayerCredits::SetCredits(const CPlayerCredits::Credits& value) {
    if (credits != value) {
        credits = value;
        1 // TO DO: send message "changed"
    }
}


} // namespace TD
