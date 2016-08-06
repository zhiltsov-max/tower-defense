#ifndef BUILDING_H
#define BUILDING_H

#include "GameEngine/scene_object.h"
#include "GameEngine/component_systems.h"
#include "GameEngine/scene.h"


namespace TD {

using TBuildingClassId = TGameObjectClassId;

class CMouseInput : public GE::CInputComponent
{
public:
    virtual void HandleMessage(const GE::TMessage& message,
        Context& context) override;
    virtual forward_list<GE::TMessage::ID> GetAcceptedMessages() const override;
    virtual Update(Context& context) override;
};

class CSelectableModel : public GE::CDataComponent
{
public:
    bool IsSelected() const;
    void SetSelection(bool value);
private:
    bool selected;
};

class CExplodableBehaviour : public GE::CLogicsComponent
{
public:
    using Power = uint;

private:
    Power power;

    void Explode();
};

class CBreakableBehaviour : public GE::CLogicsComponent
{
public:
};

class CConstructibleBehaviour : public GE::CLogicsComponent
{
public:
    virtual void HandleMessage(const GE::TMessage& message,
        Context& context) override;
    virtual forward_list<GE::TMessage::ID> GetAcceptedMessages() const override;

    virtual void Update(const GE::TTime& step, Context& context) override;

private:
    enum class State : char {
        Undefined = 0,
        PositionSelection,
        RotationSelection,
        Placed,
        Built
    };
    GE::TScene::ComponentPath buildingsControllerPath;
    GE::TScene::ComponentHandle buildingsControllerHandle;
    GE::TScene::ComponentPath buildingModelPath;
    GE::TScene::ComponentHandle buildingModelHandle;
    State state;

    const Altitude& GetAltitude() const;

    bool IsPlaced() const;
    bool IsBuilt() const;
    bool IsOnTile(const Point2f& tilePos) const;
    bool CanBuildThere(const Point2f& tilePos) const;

    void RejectBuilding();
    void TryBuild();
    void SelectPlace();
    void SelectRotation();
};

class CTradableBehaviour : public GE::CLogicsComponent
{
public:
    using Cost = int;

private:
    Cost cost;

    const Cost& GetCost() const;
    void Sell();
};

class CUpgradableBehaviour : public GE::CLogicsComponent
{
public:

private:
    GE::TScene::ComponentPath buildingsControllerPath;
    GE::TScene::ComponentHandle buildingsControllerHandle;
    GE::TScene::ComponentPath buildingModelPath;
    GE::TScene::ComponentHandle buildingModelHandle;

    const Cost& GetUpgradeCost() const;

    const UpgradeIndex& GetMajorUpgrade() const;
    void UpgradeTo(const TBuildingClassId& newClass);
};

class CBuilding : public GE::CDataComponent
{
public:
    using ClassID = TBuildingClassId;

    const ClassID& GetClassID() const;
private:
    ClassID classId;
};

} // namespace TD

#endif //BUILDING_H
