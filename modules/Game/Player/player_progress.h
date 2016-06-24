#ifndef PLAYER_PROGRESS_H
#define PLAYER_PROGRESS_H

#include "Game/Components/components_list.h"
#include "Game/Player/player_credits.h"
#include "Game/Player/player_researches.h"
#include "Game/Player/player_quests.h"


namespace TD {

class CPlayerProgress :
    public GE::CLogicsComponent
{
public:
    using Credits = CPlayerCredits;
    using Researches = CPlayerResearches;
    using Quests = CPlayerQuests;
    struct Parameters;

    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args);

    CPlayerProgress(const Parameters& args);

    virtual void Update(GE::TScene* scene) override;
    virtual void HandleMessage(const TMessage& message) override;
    virtual void Subscribe(TComponentSystem& system) override;
    virtual void Unsubscribe(TComponentSystem& system) override;

    const Credits& GetCredits() const;
    Credits& GetCredits();

    const Researches& GetResearches() const;
    Researches& GetResearches();

    const Quests& GetQuests() const;
    Quests& GetQuests();

private:
    using parent_type = CLogicsComponent;

    Credits credits;
    Researches quests;
    Quests researches;
};

template<>
struct GE::ComponentID< CPlayerProgress >
{
    static constexpr GE::ComponentIDs value = GE::ComponentIDs::PlayerProgress;
};

struct CPlayerProgress::Parameters : GE::TComponentCreateArgs
{
    CPlayerCredits::Parameters credits;
    CPlayerResearches::Parameters researches;
    TPLayerQuestsInfo quests;
};

} // namespace TD

#endif // PLAYER_PROGRESS_H
