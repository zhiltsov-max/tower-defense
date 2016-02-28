#include "tb_castle.h"
#include "buildings_info.h"


TB_Castle::TB_Castle() :
	parent_type(),
	health(0),
	maxHealth(0),
	buildState(BuildState::Complete)
{}

void TB_Castle::initialize(const Info& info) {
    parent_type::initialize(info);
    maxHealth = info[getClass()]["health"].asInt;
}

TBuilding* TB_Castle::clone() const {
    return new TB_Castle(*this);
}

bool TB_Castle::isAlive() const {
	return (0 < health);
}
bool TB_Castle::needsRepair() const {
    return health < maxHealth;
}	
bool TB_Castle::isSelected() const {
	return false;
}
bool TB_Castle::isRepairable() const {
	return BuildingsController::getParameter(getClass(), "repirable");
}
		
void TB_Castle::repair(int amount) const {
	if (health == maxHealth) {
#if _DEBUG_
		throw_("Attempt to repair not damaged castle.", "TB_Castle::repair");
#else
		return;
#endif
	}		
	health += amount;
}
	
void TB_Castle::hurt(int amount) {
	health -= amount;
	if (isAlive() == false) {
		TEvent_CastleDied(this);
	}
}	
	
int TB_Castle::getHealth() const {
	return health;
}	

int TB_Castle::getMaxHealth() const {
	return maxHealth;
}
	
TBuilding::ClassId TB_Castle::getClass() const {
	return BuildingClass::Castle;
}
	
	
void TB_Castle::setHealth(int value) {
#if _DEBUG_
	if (maxHealth < value) {
        Throw("Attempt to set castle health higher than maximum.", "TB_Castle::setHealth");
	}
#endif
	health = std::min(std::max(0, value), maxHealth);
}	
	
void TB_Castle::updateParameters() {
	/* none */
}		

void TB_Castle::loadSelection() {
	/* none */
}	
void TB_Castle::loadAnimation() {
    animation.reset(new Animation(getClass()));
	animation->setAction(BuildingAnimationGroup::Normal);
}	

void TB_Castle::updateBehaviour() {
	/* none */
}


void TB_Castle::InfoLoader(TBuilding::Info& info, std::istream& source) {
    parent_type::InfoLoader(info, source);

    string buffer;

    std::getline(source, buffer);
    info["health"].asInt = std::stoi(buffer);
}
