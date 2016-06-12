#ifndef PLAYER_POINTS_H
#define PLAYER_POINTS_H

#include "Game/Components/components_list.h"


namespace TD {

class CPlayerPoints : public CLogicsComponent
{
public:
    static std::unique_ptr<TComponent> Create(
        const TComponentCreateArgs* args = nullptr);


    using Points = int;


    CPlayerPoints();

    virtual void Update() override;
    virtual void HandleMessage(const TMessage& message) override;
    virtual void Subscribe(TComponentSystem& system) override;
    virtual void Unsubscribe(TComponentSystem& system) override;

    const Points& GetPoints() const;
    void SetPoints(const Points& value);

private:
    using parent_type = CLogicsComponent;

    Points points;
};

template<>
struct ComponentID< CPlayerPoints > {
    static constexpr ComponentID value = ComponentID::PlayerPoints;
};

template<>
struct ComponentClass< CPLayerPoints > {
    static constexpr CompponentClass value = ComponentClass::logics;
};

} // namespace TD

#endif // PLAYER_POINTS_H
