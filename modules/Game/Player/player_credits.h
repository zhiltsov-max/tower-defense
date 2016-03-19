#ifndef PLAYER_CREDITS_H
#define PLAYER_CREDITS_H

#include "Game/Components/components_list.h"



namespace TD {


class CPlayerCredits : public CLogicsComponent
{
public:
    static std::unique_ptr<TComponent> Create(const TComponentCreateArgs* args = nullptr);


    using Credits = int;


    CPlayerCredits();

    virtual void Update() override;
    virtual void HandleMessage(const TMessage& message) override;
    virtual void Subscribe(TComponentSystem& system) override;
    virtual void Unsubscribe(TComponentSystem& system) override;

    const Credits& GetCredits() const;
    void SetCredits(const Credits& value);

private:
    using parent_type = CLogicsComponent;

    Credits credits;
};

template<>
struct ComponentID< CPlayerCredits > {
    static constexpr ComponentID value = ComponentID::PlayerCredits;
};

template<>
struct ComponentClass< CPLayerCredits > {
    static constexpr CompponentClass value = ComponentClass::logics;
};


} // namespace TD

#endif // PLAYER_CREDITS_H
