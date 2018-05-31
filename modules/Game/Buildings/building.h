#ifndef BUILDING_H
#define BUILDING_H

#include "GameEngine/component_system.h"
#include "GameEngine/game_engine.h"
#include "GameEngine/scene.h"
#include "Game/Buildings/buildings_info.h"
#include "Game/Components/animation_component.h"


namespace TD {

using TBuildingClassId = TGameObjectClassId;



struct CPlayerInput : GE::TComponent
{
    // Listens to MouseInput and KeyboardInput components
    // Have to filter scene interaction and GUI interaction
};

struct CConstructibleMouseInput : GE::TComponent
{

};

struct CBuilding : GE::TComponent
{
    using ClassID = TBuildingClassId;

    ClassID classId;
};

struct CUpgrade : GE::TComponent
{
    enum class Type : char {
        _min = 0,

        Minor = 0,
        Major,

        _max,
        _count = _max - _min,
        _undefined
    };

    Type type;
};

struct CUpgradable : GE::TComponent
{
    using Level = uint;
    using UpgradeId = uint;
    static const UpgradeId UpgradeIdUndefined = -1u;

    Level level;
    UpgradeId currentUpgradeId;
    UpgradeId selectedUpgradeId;
};

struct CConstructible : GE::TComponent
{
    enum class State : char {
        Undefined = 0,
        PositionSelection,
        RotationSelection,
        Building,
        Built
    };
    State state;
};

struct CExplodable : GE::TComponent
{
    using Power = uint;

    Power power;
};

struct CExplodableImpact : GE::TComponent
{

};

struct CInteractiveSelectable : GE::TComponent
{
    bool selected;
};

struct CSelectionView : CAnimation { /*none*/ };

class CSBuildings :
    public GE::TComponentSystem
{
public:
    using BuildingsRegistry = TBuildingsRegistry;
    using UpgradesRegistry = TUpgradesRegistry;

    virtual void Update(const GE::TTime& step, Context& context) override {
        // ...
    }

    const BuildingsRegistry& GetBuildingsRegistry() const;
    BuildingsRegistry& GetBuildingsRegistry();

private:
    BuildingsRegistry buildingsRegistry;
    UpgradesRegistry upgradesRegistry;

    void UpgradeBuilding(const GE::TScene::ComponentHandle& buildingHandle,
        Context& context)
    {
        auto& object = context.scene->GetSceneObject(objectHandle);
        auto* upgradable = object.GetComponent<CUpgradable>();
        ASSERT(upgradable != nullptr, "Upgradable component is expected.");

        const auto& upgrade = upgradesRegistry[upgradable->selectedUpgradeId];
        switch (upgrade.type) {
        case CUpgrade::Type::Major:
            PerformMajorUpgrade(*upgradable, objectHandle, context);
            break;

        case CUpgrade::Type::Minor:
            PerformMinorUpgrade(*upgradable, objectHandle, context);
            break;

        default: /*none*/
            THROW("Unexpected Upgrade type.");
            break;
        }
    }

    void PerformMinorUpgrade(CUpgradable& upgradable,
        const GE::TScene::ObjectHandle& objectHandle, Context& context)
    {
        upgradable.level += 1;
        // ...

        MBuildingUpgraded message;
        // message setup
        context.engine->SendMessage(message, context);
    }

    void PerformMajorUpgrade(CUpgradable& upgradable,
        const GE::TScene::ObjectHandle& objectHandle, Context& context)
    {
        auto& object = context.scene->GetSceneObject(objectHandle);
        auto* building = object.GetComponent<CBuilding>();
        ASSERT(building != nullptr, "Expected building object.");

        const auto& upgrade = upgradesRegistry[upgradable.selectedUpgradeId];
        building->classId = upgrade.nextBuildingTypeId;
        upgradable.currentUpgradeId = upgradable.selectedUpgradeId;
        upgradable.selectedUpgradeId = CUpgradable::UpgradeIdUndefined;

        MBuildingUpgraded message;
        // message setup
        context.engine->SendMessage(message, context);
    }

    void RejectConstruction(
        const GE::TScene::ComponentHandle& constructionHandle,
        Context& context)
    {
        auto* object = context.scene->FindSceneObjectForComponent(
            constructionHandle);
        ASSERT(object != nullptr,
            "Can not find parent object of constructible component.");

        object->RemoveComponent<CConstructible>();

        MConstructionRejected message;
        // message setup
        context.engine->SendMessage(message, context);
    }

    void TryConstruct(
        const GE::TScene::ComponentHandle& constructionHandle,
        Context& context)
    {
        MCheckConstrictionAvailability message;
        // message setup
        context.engine->SendMessage(message, context);
    }

    void StartConstruction(
        const GE::TScene::ComponentHandle& constructionHandle,
        Context& context)
    {
        auto* construction = context.scene->GetComponent<CConstructible>(
            constructionHandle);
        ASSERT(construction != nullptr, "Expected constructible object.");

        construction->state = CConstructible::State::Building;

        MConstructionStarted message;
        // message setup
        context.engine->SendMessage(message, context);
    }

    void FinalizeConstruction(
        const GE::TScene::ComponentHandle& constructionHandle,
        Context& context)
    {
        auto* construction = context.scene->GetComponent<CConstructible>(
            constructionHandle);
        ASSERT(construction != nullptr, "Expected constructible object.");

        construction->state = CConstructible::State::Built;

        MConstructionCompleted message;
        // message setup
        context.engine->SendMessage(message, context);
    }
};

class CTradable : GE::TComponent
{
    using Money = uint;

    Money price;
};

class CSPlayerInteraction :
    public GE::TComponentSystem
{
public:

private:
    void Sell(CTradable& tradable, const GE::TScene::ObjectHandle& objectHandle,
        const GE::TScene::ObjectHandle& playerHandle, Context& context)
    {
        auto& player = context.scene->GetSceneObject(playerHandle);
        auto* playerInfo = player.GetComponent<CPlayerInfo>();
        playerInfo.money += tradable.price;

        MSellingCompleted message;
        // message setup
        context.engine->SendMessage(message, context);
    }

};

class CSExplosions :
    public GE::TComponentSystem
{
public:
    virtual void Update(const GE::TTime& step, Context& context) override {
        // might be animation & time update
    }
};

} // namespace TD

#endif //BUILDING_H
