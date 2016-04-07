#include "building.h"
#include "buildings_controller.h"
#include "building_selection.h"
#include "building_animation.h"


	
void TBuilding::update() {
	if (isBuilt() == true) {
		updateSelection();
		updateBehaviour();
		updateAnimation();	
	} else {
		updateBuildState();
	}
}
	
void TBuilding::draw() {
	selection->draw(absPos(), baseRotation);
	Graphics::SetColor(0xFFFFFFFF);
	Graphics::SetRotation(baseRotation);
	Graphics::DrawImage(animation->getImage(), xAbs(), yAbs(), animation->getCurrentFrame());
	Graphics::SetRotation(0);
}

void TBuilding::setPos(float x_, float y_) {
	pos.x() = x_;
	pos.y() = y_;
}
void TBuilding::setZIndex(Graphics::ZIndex value) {
	UNUSED( value );
}	
void TBuilding::setSelection(bool value) {
	selected = value;
}
	
Graphics::ZIndex TBuilding::getZIndex() const {
	return GraphicsZIndex::Buildings;
}
uint TBuilding::getUpgradeCost() const {
	return getCost() * GameMechanics::BUILDING_UPGRADE_COST_MODIFIER;
}	
uint TBuilding::getMajorUpgrade() const {
    return *BuildingsController::getParameter(getClass(), "majorUpgrade").as<int>();
}
Appearance TBuilding::getAppearance() const {
	return appearance;
}
const Point2f& TBuilding::getSize() const {
	return animation->getSize();
}	
uint TBuilding::getCost() const {
	return BuildingsController::getParameter(getClass(), "cost");
}
const Point2f& TBuilding::getSize() const {
	return animation->getSize() / GameMechanics::TILE_SIZE;
}
const Point2f& TBuilding::getPos() const {
	return pos;
}
Point2ui TBuilding::absPos() const {
	return Point2ui(xAbs(), yAbs());
}
uint TBuilding::xAbs() const {
	return (uint)pos.x() * GameMechanics::TILE_SIZE;
}	
uint TBuilding::yAbs() const {
	return (uint)pos.y() * GameMechanics::TILE_SIZE;
}		
		
void TBuilding::sell() {
	TEvent_BuildingSold(this, std::to_string((long long)getClass()));
	remove();
}	
void TBuilding::rejectBuilding() {
	remove();
}	
void TBuilding::upgradeTo(uint newClass) { // TODO:
		const TBuildingUpgrades& upgrades = BuildingsController::getUpgrades();
		const TBuildingUpgrade& upgrade = upgrades.getUpgrade(BuildingsController::getParameter(newClass, "majorUpgrade").asInt);
		const bool isNewClassUpgrade = (upgrades.getUpgrade(getMajorUpgrade()) = 
		                            upgrade.findFirstPrevMajor());

	if (isNewClassUpgrade == false) {
		throw_("Building #" + std::to_string((long long)newClass) +
			" does not upgrade building #" + std::to_string((long long)getClass()) +
			".", "TBuilding::upgradeTo");
	}

	const TLevelProgress& progess = LevelHelper::getLevelInstance().getProgress();
	if (progess.getCredits() < (BuildingsController::getParameter(newClass, "cost").asInt) * GameMechanics::BUILDING_UPGRADE_COST_MODIFIER) {
		TMovingText::CreateDefaultMessage("Not enough credits for upgrading.", Point2ui(xAbs(), yAbs()));
		return;
	}
		
	if (BuildingUpgrades.isResearched(upgrade.getID()) == false) {
		TMovingText::CreateDefaultMessage("You need to recearh upgrade first.", Point2ui(xAbs(), yAbs()));
		return;
	}
		
	if (BuildingUpgrades.findClassForMajorUpgrade(upgrade.getID()) == "") {
		throw_("Buildng with major upgrade #" +
			std::to_string((long long)upgrade.getID()) + 
			" not found.", "TBuilding::upgradeTo");
	}
		
	const string& newTypeName = BuildingUpgrades.findTypeForMajorUpgrade(upgrade.getID());
	TBuilding* newBuilding = BuildingFactory::create(newTypeName);

	newBuilding->initialize();
	newBuilding->pos = pos;
		
	buildState = BuildState::NotBuilt;
	newBuilding->tryBuild();
	if (newBuilding->isPlaced() == false) {
		newBuilding->remove();
		buildState = BuildState::Complete;
		return;
	}
		
	newBuilding->selected == true;
	remove();
	GetScene().AddObject(newBuilding);

	TEvent_BuildingUpgraded(this, [newBuilding->getClass()]);
}
	
void TBuilding::explode() {
	animation->setAction(BuildingAnimationGroup::Explode);
}
	
	
bool TBuilding::isPlaced() const {
	return BuildState::Built <= buildState;
}
bool TBuilding::isBuilt() const {
	return buildState == BuildState::Complete;
}	
bool TBuilding::isSelected() const {
	return selected;
}
bool TBuilding::isOnTile(const Point2f& tilePos) const {
	if (isPlaced() == false) { return false; }

	const Point2ui posAbs = (tilePos + Point2f(0.5f, 0.5f)) * GameMechanics::TILE_SIZE;
	const Point2ui p1((uint)std::floor(pos.x() - getSize().x() * 0.5f) * GameMechanics::TILE_SIZE + 1u,
					  (uint)std::floor(pos.y() - getSize().y() * 0.5f) * GameMechanics::TILE_SIZE + 1u);
	const Point2ui p2((uint)std::ceil(pos.x() + getSize().x() * 0.5f) * GameMechanics::TILE_SIZE - 1u,
					  (uint)std::ceil(pos.y() + getSize().y() * 0.5f) * GameMechanics::TILE_SIZE - 1u);
	return posAbs.isInRect(p1, p2);
}
	
bool TBuilding::canBuildThere(const Point2f& where_) const {
	return BuildingsController::canBuildThere(where_, getSize());
}	
	
void TBuilding::updateBuildState() {
	if (MouseController::MouseHit(MOUSE_RIGHT) == true) {
		if (UIParent().isMouseOver() == false) {
			rejectBuilding();
		}
	} else {
		if (isPlaced() == false) {
			selectPlace();
		} else {
			selectRotation();
		}
	}
}
void TBuilding::updateSelection() {
	if (MouseListener::MouseDown(MOUSE_LEFT) == false) {
		return;
	}	

	if (UIParent().isMouseOver() == true) {
		return;
	}
		
	const Point2ui p1((uint)std::floor(pos.x() - getSize().x() * 0.5f) * GameMechanics::TILE_SIZE + 1u,
					  (uint)std::floor(pos.y() - getSize().y() * 0.5f) * GameMechanics::TILE_SIZE + 1u);
	const Point2ui p2((uint)std::ceil(pos.x() + getSize().x() * 0.5f) * GameMechanics::TILE_SIZE - 1u,
					  (uint)std::ceil(pos.y() + getSize().y() * 0.5f) * GameMechanics::TILE_SIZE - 1u);
	if (MouseListener::isCursorInRect(p1, p2) == true) {
		setSelection(true);
	} else {
		setSelection(false);
	}
}	
void TBuilding::updateAnimation() {
	switch (animation->getAction()) {
	case BuildingAnimationGroup::Normal: /*none*/
	case BuildingAnimationGroup::Explode:
		{
			if (animation->isCurrentActionCompleted() == true) {
				//TODO: 
				remove();
			}
			break;
		}
		default:
			{
				throw_("Unexpected animation group of Building: " + animation->getAction(), "TBuilding::updateAnimation");
			}
	}
	
	animation.update();
}
		
void TBuilding::tryBuild() {
	if ((getCost() <= LevelHelper::getLevelInstance().getProgress().getCredits()) == false) {
		TMovingText::CreateDefaultMessage("Not enough credits, need " + getCost(), absPos());
		return;
	}
		
	if (canBuildThere(pos) == false) {
		TMovingText::CreateDefaultMessage("Not enough space.", absPos());
		return;
	}
		
	buildState = BuildState::Built;
	MobsController::updatePathes();
}
	
void TBuilding::selectPlace() {
	pos = Point2f(
		float(MouseListener::mouseX() / GameMechanics::TILE_SIZE) + 0.5f,
		float(MouseListener::mouseY() / GameMechanics::TILE_SIZE) + 0.5f);

	if ((MouseListener::MouseHit(MOUSE_LEFT) == true) && (UIParent().isMouseOver() == false)) {
		tryBuild();
	}
		
	selected = true;
}
	
void TBuilding::selectRotation() {
	float angle = std::atan2f(MouseListener::mouseY() - yAbs(), MouseListener::mouseX() - xAbs());
	if (angle < 0.0f) { angle = 360.0f + angle; }
	baseRotation = (int)angle;

	if ((MouseListener::MouseHit(MOUSE_LEFT) == false) || (UIParent().isMouseOver() == true)) {
		return;
	}
		
	buildState = BuildState::Complete;
		
	TEvent_BuildingCreated(this, std::to_string((long long)getClass()));
}
	
TGameEvent const* TBuilding::getCurrentEvent() {
	const TEventQueue& queue = LevelHelper::getLevelInstance().getProgress().getEventQueue();
	if (queue.empty() == false) {
		return &(queue.getCurrentEvent());
	} else {
		return nullptr;
	}
}

void TBuilding::updateParameters(Info const* source) {
	UNUSED( source )
}

void TBuilding::InfoLoader(TBuilding::Info& info, std::istream& source) {
    string buffer;

    std::getline(source, buffer);
    (*info)["name"].as<string>() = new string(buffer);

    std::getline(source, buffer);
    (*info)["appearance"].as<int>() = new int(std::stoi(buffer));

    std::getline(source, buffer);
    (*info)["cost"].as<int>() = new int(std::stoi(buffer));

    std::getline(source, buffer);
    (*info)["majorUpgrade"].as<int>() = new int(std::stoi(buffer));

    std::getline(source, buffer);
    (*info)["description"].as<string>() = new string(buffer);

    std::getline(source, buffer);
    (*info)["resources"].as<string>() = new string(buffer);
}
