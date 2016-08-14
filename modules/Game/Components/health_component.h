#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include "GameEngine/component_systems.h"


namespace TD {

class CHealth : public GE::CDataComponent
{
public:
    using Health = int;
    struct Parameters;

    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args = nullptr);

    CHealth(const Parameters* args = nullptr);

    virtual void HandleMessage(const GE::TMessage& message,
        Context& context) override;

    const Health& GetActualHealth() const;
    void SetActualHealth(const Health& value);

    const Health& GetMaxHealth() const;
    void SetMaxHealth(const Health& value);

private:
    using parent_type = GE::CDataComponent;

    int actualHealth;
    int maxHealth;
};

struct CHealth::Parameters : GE::TComponentCreateArgs
{
    Health actualHealth;
    Health maxHealth;
};

} // namespace TD


namespace GE {

template<>
struct ComponentID<TD::CHealth>
{
    static const ComponentIDs value;
};

template<>
struct ComponentClass<TD::CHealth>
{
    static const ComponentSystem value;
};

} // namespace GE

#endif // HEALTH_COMPONENT_H
