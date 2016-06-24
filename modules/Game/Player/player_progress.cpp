#include "player_progress.h"


namespace TD {

std::unique_ptr<GE::TComponent>
CPlayerProgress::Create(const GE::TComponentCreateArgs* args_) {
    const auto* args = dynamic_cast<CPlayerProgress::Parameters*>(args_);
    ASSERT(args != nullptr, "Wrong constructor parameters.")
    return new CPlayerProgress(*args);
}

CPlayerProgress::CPlayerProgress(const Parameters& args) :
    parent_type(),
    credits(args.credits),
    researches(args.researches),
    quests(args.quests)
{}

const CPlayerProgress::Credits& CPlayerProgress::GetCredits() const {
    return credits;
}

CPlayerProgress::Credits& CPlayerProgress::GetCredits() {
    return credits;
}

const CPlayerProgress::Researches& CPlayerProgress::GetResearches() const {
    return researches;
}

CPlayerProgress::Researches& CPlayerProgress::GetResearches() {
    return researches;
}

const CPlayerProgress::Quests& CPlayerProgress::GetQuests() const {
    return quests;
}

CPlayerProgress::Quests& CPlayerProgress::GetQuests() {
    return quests;
}

void CPlayerProgress::Update(GE::TScene* scene) { /*none*/ }

void CPlayerProgress::HandleMessage(const TMessage& message) {
    //TODO: ...
}

void CPlayerProgress::Subscribe(TComponentSystem& system) {
    //TODO: ...
}

void CPlayerProgress::Unsubscribe(TComponentSystem& system) {
    //TODO: ...
}

} // namespace TD
