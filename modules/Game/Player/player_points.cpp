#include "player_points.h"



namespace TD {


std::unique_ptr<TComponent> CPlayerPoints::Create(const TComponentCreateArgs* args) {
    return new CPlayerPoints;
    UNUSED(args)
}

CPlayerPoints::CPlayerPoints() :
    parent_type(),
    points(0)
{}


void TD::CPlayerPoints::Update() {
    /*none*/
}

void CPlayerPoints::HandleMessage(const TMessage& message) {
    1
}

void CPlayerPoints::Subscribe(TComponentSystem& system) {
    1
}

void CPlayerPoints::Unsubscribe(TComponentSystem& system) {
    1
}

const CPlayerPoints::Points& CPlayerPoints::GetPoints() const {
    return points;
}

void CPlayerPoints::SetPoints(const CPlayerPoints::Points& value) {
    if (points != value) {
        points = value;
        1 // TODO: send message "changed"
    }
}


} // namespace TD
