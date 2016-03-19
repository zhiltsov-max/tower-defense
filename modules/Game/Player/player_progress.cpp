#include "player_progress.h"



namespace TD {


std::unique_ptr<TComponent> CPlayerProgress::Create(const TComponentCreateArgs* args_) {
    ASSERT(args_ != nullptr, "Constructor parameters expected.")

    const auto* args = dynamic_cast<TPlayerProgressArgs*>(args_);
    ASSERT(args != nullptr, "Wrong constructor parameters.")

    return new CPlayerProgress(*args);
}

CPlayerProgress::CPlayerProgress(TPlayerProgressArgs& args) :
    parent_type(),
    state(State::Undefined),
    points(),
    credits(),
    researches(),
    quests(),
    level(args.level)
{
    ASSERT(args.level != nullptr, "Level must be set.")

    points = args.level->GetScene().CreateComponent<CPlayerPoints>();

    credits = args.level->GetScene().CreateComponent<CPlayerCredits>();

    CPlayerResearchesArgs researchesArgs;
    researchesArgs.level = args.level;
    researches = args.level->GetScene().
        CreateComponent<CPlayerResearches>(researchesArgs);

    CPlayerQuestsArgs questsArgs;
    questsArgs.level = args.level;
    quests = args.level->GetScene().
        CreateComponent<CPlayerQuests>(questsArgs);
}

const CPlayerProgress::Credits& CPlayerProgress::GetCredits() const {
    return credits;
}

CPlayerProgress::Credits& CPlayerProgress::GetCredits() {
    return credits;
}

const CPlayerProgress::Points& CPlayerProgress::GetPoints() const {
    return points;
}

CPlayerProgress::Points& CPlayerProgress::GetPoints() {
    return points;
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

void CPlayerProgress::Update() {
    1
}

void CPlayerProgress::HandleMessage(const TMessage& message) {
    1
}

void CPlayerProgress::Subscribe(TComponentSystem& system) {
    1
}

void CPlayerProgress::Unsubscribe(TComponentSystem& system) {
    1
}


} // namespace TD
