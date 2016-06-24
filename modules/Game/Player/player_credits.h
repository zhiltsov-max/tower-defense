#ifndef PLAYER_CREDITS_H
#define PLAYER_CREDITS_H

#include "Game/Components/components_list.h"


namespace TD {

struct TPlayerCreditsInfo
{
    using Credits = int;
    Credits startValue;
};

class CPlayerCredits :
    public GE::CDataComponent
{
public:
    using Credits = TPlayerCreditsInfo::Credits;

    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args = nullptr);

    CPlayerCredits(const TPlayerCreditsInfo& info);

    virtual void HandleMessage(const TMessage& message) override;
    virtual void Subscribe(TComponentSystem& system) override;
    virtual void Unsubscribe(TComponentSystem& system) override;

    const Credits& GetCredits() const;
    void SetCredits(const Credits& value);

private:
    using parent_type = CDataComponent;

    Credits credits;
};

template<>
struct GE::ComponentID< CPlayerCredits > {
    static constexpr GE::ComponentIDs value = GE::ComponentIDs::PlayerCredits;
};

} // namespace TD

#endif // PLAYER_CREDITS_H
