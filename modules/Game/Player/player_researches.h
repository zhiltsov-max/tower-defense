#ifndef PLAYER_RESEARCHES_H
#define PLAYER_RESEARCHES_H

#include "Game/Components/components_list.h"
#include "Game/Researches/researches_tree.h"


namespace TD {

class CPlayerResearches :
    public GE::CDataComponent
{
public:
    struct Parameters;

    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args);

    CPlayerResearches(const Parameters& args);
    virtual ~CPlayerResearches();

    virtual void Update() override;
    virtual void HandleMessage(const TMessage& message) override;
    virtual void Subscribe(TComponentSystem& system) override;
    virtual void Unsubscribe(TComponentSystem& system) override;

    const TResearchesTree& GetTree() const;
private:
    using parent_type = CDataComponent;
};

template<>
struct ComponentID< CPlayerResearches >
{
    static constexpr ComponentID value = ComponentID::PlayerResearches;
};

struct CPlayerResearches::Parameters : GE::TComponentCreateArgs
{
    1
};

//TODO: add researches tree view and controller components

} // namespace TD


#endif // PLAYER_RESEARCHES_H
