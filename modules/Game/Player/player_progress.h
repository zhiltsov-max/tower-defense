#ifndef PLAYER_PROGRESS_H
#define PLAYER_PROGRESS_H

#include "Game/Level/level.h"
#include "player_researches.h"
#include "player_quests.h"



namespace TD {


struct TPlayerProgressArgs;

class CPlayerProgress : public CLogicsComponent
{
public:
    static std::unique_ptr<TComponent> Create(const TComponentCreateArgs* args);


    using Points = CPlayerPoints;
    using Credits = CPlayerCredits;
    using Researches = CPlayerResearches;
    using Quests = CPlayerQuests;


    CPlayerProgress(TPlayerProgressArgs& args);
    virtual ~CPlayerProgress();

    virtual void Update() override;
    virtual void HandleMessage(const TMessage& message) override;
    virtual void Subscribe(TComponentSystem* system) override;
    virtual void Unsubscribe(TComponentSystem* system) override;

    const Credits& GetCredits() const;
    Credits& GetCredits();

    const Points& GetPoints() const;
    Points& GetPoints();

    const Researches& GetResearches() const;
    Researches& GetResearches();

    const Quests& GetQuests() const;
    Quests& GetQuests();

private:
    using parent_type = CLogicsComponent;

    using Handle = TLevelScene::SceneObjects::Handle;
    Handle points;
    Handle credits;
    Handle quests;
    Handle researches;

    using PLevel = TLevel *;
    const PLevel level;
};

template<>
struct ComponentID< CPlayerProgress > {
    static constexpr ComponentID value = ComponentID::PlayerProgress;
};

template<>
struct ComponentClass< CPLayerProgress > {
    static constexpr CompponentClass value = ComponentClass::logics;
};

struct TPlayerProgressArgs : TComponentCreateArgs
{
    TLevel* level;
};


} // namespace TD

#endif // PLAYER_PROGRESS_H
