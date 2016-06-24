#ifndef PLAYER_PROGRESS_H
#define PLAYER_PROGRESS_H

#include "Game/Components/components_list.h"
#include "Game/Player/player_credits.h"
#include "Game/Player/player_researches.h"
#include "Game/Player/player_quests.h"


namespace TD {

struct TPlayerProgressInfo : GE::TComponentCreateArgs
{
    TPlayerCreditsInfo credits;
    TPlayerResearchesInfo researches;
    TPLayerQuestsInfo quests;
};

class CPlayerProgress :
    public GE::CLogicsComponent
{
public:
    using Credits = CPlayerCredits;
    using Researches = CPlayerResearches;
    using Quests = CPlayerQuests;

    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args = nullptr);

    CPlayerProgress(const TPlayerProgressInfo& args);

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
struct GE::ComponentID< CPlayerProgress > {
    static constexpr GE::ComponentIDs value = GE::ComponentIDs::PlayerProgress;
};

} // namespace TD

#endif // PLAYER_PROGRESS_H
