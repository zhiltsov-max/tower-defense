#include "building.h"
#include "buildings_controller.h"


	
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
