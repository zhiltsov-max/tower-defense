#include "mob_walker.h"


Appearance TMob_Walker::getAppearance() const {
    return Appearance::Ground;
}
	
uint TMob_Walker::getBoilingConditionTime() const {
	return GameMechanics::MOB_BOILING_CONDITION_TIME;
}
	
	
bool TMob_Walker::isBoiling() const {
	return 0 < boilingTime;
}
		
void TMob_Walker::setBoiling(bool value) {
	if (value == isBoiling()) {
		return;
	}
		
	if (value == true) {
		TMovingText::CreateDefaultMessage("Warning! Mob is blocked!",
			Point2ui(pos.x() - getSize().x() * 0.5, pos.y() - getSize().y() - 20),
			DefaultMessageColor::exclamation);
		boilingTime = 1;
	} else {
		boilingTime = 0;
	}
}	
	
void TMob_Walker::draw() {
	int boilingStage = 0;
	if (0 < boilingTime) {
		boilingStage = (int)(float(boilingTime) / float(getBoilingConditionTime())) * 255;
	}
		
	Graphics::SetColor(255, 255 - boilingStage, 255 - boilingStage);
	Graphics::SetAlpha(1);
		
	TImage const* image = animation->getImage();
	if (image != nullptr) {
		Graphics::DrawImage(image, pos.x() - getSize().x() * 0.5, pos.y() - getSize().y(), animation->getCurrentFrame());
	} else {
		Graphics::DrawRect(pos.x() - getSize().x() * 0.5, pos.y() - getSize().y(), getSize()x(), getSize().y());
	}
}

void TMob_Walker::updatePosition() {
	parent_type::updatePosition();
	updateBoiling();
}
	
void TMob_Walker::updateBoiling() {
	setBoiling(path.Exists() == false);

	if (boilingTime == getBoilingConditionTime());
		hurtAround();
		die();
		return;
	}
		
	if (isBoil() == true) {
		health += GameMechanics::MOB_BOILING_HEALTH_INCREASE;
		maxHealth += GameMechanics::MOB_BOILING_HEALTH_INCREASE;
		++boilingTime;
	}
}

void TMob_Walker::hurtAround() {
	const Point2ui p1(pos.x() - getSize().x() * 0.5 - GameMechanics::TILE_SIZE,
					    pos.y() - getSize().y() - GameMechanics::TILE_SIZE);
	const Point2ui p2(pos.x() + getSize().x() * 0.5 + GameMechanics::TILE_SIZE,
						pos.y() + GameMechanics::TILE_SIZE);
	BuildingsController::explodeAround(p1, p2);
}
