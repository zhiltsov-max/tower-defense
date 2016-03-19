#ifndef BUILDING_H
#define BUILDING_H

#include "GameEngine/scene_object.h"


namespace TD {


using TBuilding = TSceneObject;
using TBuildingClassId = TGameObjectClassId;


class CMouseInput : public CInputComponent
{
public:
    virtual void Update() override;
    virtual void HandleMessage(const TMessage& message) override;
    virtual void Subscribe(TComponentSystem& system) override;
    virtual void Unsubscribe(TComponentSystem& system) override;
};


class CPosition : public CMovementComponent
{
public:
    virtual void Update() override;
    virtual void HandleMessage(const TMessage& message) override;
    virtual void Subscribe(TComponentSystem& system) override;
    virtual void Unsubscribe(TComponentSystem& system) override;

private:
    Point2f position;
    float rotation;
};


class CSelection : public CGraphicsComponent
{
public:
    virtual void Update() override;
    virtual void HandleMessage(const TMessage& message) override;
    virtual void Subscribe(TComponentSystem& system) override;
    virtual void Unsubscribe(TComponentSystem& system) override;

private:
    bool selected;
    std::unique_ptr<TBuildingSelection> selection;
};


enum class BuildingAppearance {
    undefined = 0,
    Ground = 1,
    Air = 2
};


class TBuildingsController;

class CBuildingBehaviour : public CLogicsComponent
{
public:
    virtual void Update() override;
    virtual void HandleMessage(const TMessage& message) override;
    virtual void Subscribe(TComponentSystem& system) override;
    virtual void Unsubscribe(TComponentSystem& system) override;

private:
    const TBuildingClassId id;

    enum class State {

    };
    State state;

    TBuildingsController* controller;


    virtual uint getUpgradeCost() const;
    virtual uint getMajorUpgrade() const;
    virtual const BuildingAppearance& getAppearance() const;
    virtual uint getCost() const;

    virtual void sell();
    virtual void rejectBuilding();
    virtual void upgradeTo(uint newClass);
    virtual void explode();

    virtual bool isPlaced() const;
    virtual bool isBuilt() const;
    virtual bool isSelected() const;
    virtual bool isOnTile(const Point2f& tilePos) const;
    virtual bool canBuildThere(const Point2f& tilePos) const;

    virtual void updateBuildState();
    virtual void updateSelection();
    virtual void updateAnimation();
    virtual void updateBehaviour() = 0;

    virtual void tryBuild();
    virtual void selectPlace();
    virtual void selectRotation();
};


class CHealth : public CLogicsComponent
{
public:
    virtual void Update() override;
    virtual void HandleMessage(const TMessage& message) override;
    virtual void Subscribe(TComponentSystem& system) override;
    virtual void Unsubscribe(TComponentSystem& system) override;

private:
    int health;
};


static void BuildingInfoLoader_Basic(Info& info, std::istream& source);


} // namespace TD

#endif //BUILDING_H
