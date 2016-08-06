#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include "GameEngine/component_systems.h"


namespace TD {

class CPosition2d : public GE::CDataComponent
{
public:
    using Position = Point2f;
    using Rotation = float;
    struct Parameters;

    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args = nullptr);

    CPosition2d(const Parameters* args = nullptr);

    virtual void HandleMessage(const GE::TMessage& message,
        Context& context) override;
    virtual forward_list<GE::TMessage::ID> GetAcceptedMessages() const override;

    const Position& GetPosition() const;
    void SetPosition(const Position& value);

    const Rotation& GetRotation() const;
    void SetRotation(const Rotation& value);

private:
    using parent_type = GE::CDataComponent;

    Position position;
    Rotation rotation;

};

struct CPosition2d::Parameters : GE::TComponentCreateArgs
{
    Point2f position;
    float rotation;
};

} // namespace TD


namespace GE {

template<>
struct ComponentID<TD::CPosition2d>
{
    static const ComponentIDs value;
};

template<>
struct ComponentClass<TD::CPosition2d>
{
    static const ComponentSystem value;
};

} // namespace GE

#endif // POSITION_COMPONENT_H
