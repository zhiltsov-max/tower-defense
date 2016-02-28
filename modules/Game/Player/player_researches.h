#ifndef PLAYER_RESEARCHES_H
#define PLAYER_RESEARCHES_H

#include "Game/Components/components_list.h"
#include "Game/Level/level.h"
#include "Game/Researches/researches_tree.h"



namespace TD {

class CResearchesTreeView;

struct TPlayerResearchesArgs : TComponentCreateArgs {
    TLevel* level;
};

class CPlayerResearches : public CLogicsComponent
{
public:
    static std::unique_ptr<TComponent> Create(TComponentCreateArgs* args);


    CPlayerResearches(const TPlayerResearchesArgs& args);
    virtual ~CPlayerResearches();

    virtual void Update() override;
    virtual void HandleMessage(const TMessage& message) override;
    virtual void Subscribe(TComponentSystem* system) override;
    virtual void Unsubscribe(TComponentSystem* system) override;

    const TResearchesTree& GetTree() const;

private:
    using parent_type = CLogicsComponent;

    using PLevel = TLevel *;
    const PLevel level;

    using TreeModel = TResearchesTree;
    TreeModel model;

    using TreeView = CResearchesTreeView;
    using Handle = TLevelScene::SceneObjects::Handle;
    Handle view;
};

template<>
struct ComponentID< CPlayerResearches > {
    static constexpr ComponentID value = ComponentID::PlayerResearches;
};

template<>
struct ComponentClass< CPlayerResearches > {
    static constexpr ComponentClass value = ComponentClass::logics;
};


} // namespace TD


#endif // PLAYER_RESEARCHES_H
