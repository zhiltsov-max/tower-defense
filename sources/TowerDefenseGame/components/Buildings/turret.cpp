#include "turret.h"
#include "buildings_controller.h"


TTurret::TTurret() :
	parent_type(),
	shotTimer(0),
	turretRotation(0),
	cooldown(0),
	damage(0),
	range(0),
	bulletSize(0),
	bulletAcceleration(0)
{}
	
void TTurret::initialize(Info const* source) {
	parent_type::initialize(source);
    cooldown = info["cooldown"].asUint;
    damage = info["damage"].asUint;
    range = info["range"].asFloat * GameMechanics::TILE_SIZE;
    turretMaxAngle = info["maxAngle"].asInt;
	//bulletAcceleration = *source->at("bulletAcceleration").as
	//bulletSize = *source->at("bulletSize").as
}

void TTurret::loadAnimation(const Info& source) {
	UNUSED( source )
	//parent_type::loadAnimation(source);
    animation = std::unique_ptr<Animation>(new Animation(info["animation"]));
	animation->setAction(BuildingAnimationGroup::Normal);
}
	
void TTurret::loadSelection(const Info& source) {
	UNUSED( source )
	//parent_type::loadSelection(source);
    selection = std::unique_ptr<Selection>(new Selection(info["selection"], this));
}	

uint TTurret::getTimer() const {
	return shotTimer;
}	
uint TTurret::getCooldown() const {
	return cooldown;
}
uint TTurret::getDamage() const {
	return damage;
}	
float TTurret::getRange() const {
	return range;
}	
	
bool TTurret::isCharged() const {
	return cooldown <= shotTimer;
}
bool TTurret::canDamageMob(TMob const* mob) const {
	if (mob == nullptr) {
#if _DEBUG_
		throw_("Mob is null", "TTurret::canDamageMob");
#else
		return false; 
#endif
	}
		
	if (mob->getAppearance() & appearance) {
		return true;
	}
		
	return false;
}
	
void TTurret::seekEnemies() {
	std::list<TMob const*> enemies = findEnemiesInRange();
	if (enemies.empty() == true) {
		return;
	}
		
	TMob const* enemy = selectEnemy(enemies);
		
	float neededRotation = std::atan2f(enemy->getPos().y() - yAbs(), enemy->getPos.x() - xAbs());
	if (neededRotation < 0) { 
		neededRotation = 360.0f + neededRotation;
	}
	setRotation(neededRotation);
		
	if (isCharged() == true) {
		if (turretRotation == (int)neededRotation) {
			shot(enemy);
		}
	}
}
	
TMob const* TTurret::selectEnemy(std::list<TMob const*>& accessibleTargets) const {
	accessibleTargets.sort(TMob::CmpGetFastest);
	accessibleTargets.sort(TMob::CmpGetClosest);
	accessibleTargets.sort(TMob::CmpGetMostDamaged);
	return accessibleTargets.front();
}
	
void TTurret::setRotation(int angle = 361) {
	if (angle != 361) {
		turretRotation = angle % 360;
	}
	checkRotation();
}
	
std::list<TMob const*>&& TTurret::findEnemiesInRange() const {
    std::list<TMob const*> foundMobs;

	double range = std::pow(range * GameMechanics::TILE_SIZE, 2);

	auto sceneObjects = LevelHelper::getLevelInstance().getScene().getObjects();
	for(auto it = sceneObjects.cbegin(); it != sceneObjects.cend(); ++it) {
		TMob const* m = dynamic_cast<TMob const*>((*it).get());
		if (m == nullptr) { continue; }

		if (canDamageMob(*it) == false) {
			continue;
		}
		
		const Point2ui delta = absPos() - (*it)->getPos();
		if (norm(delta) < range) {
			foundMobs.push_back(*it);
		}
	}
		
    return std::move(foundMobs);
}
	
void TTurret::shot(TMob const* target) {
	bullets.push_back(std::shared_ptr<Bullet>(new Bullet(Point2f(xAbs(), yAbs()), getDamage(), bulletAcceleration, target, bulletSize)));
	shotTimer = 0;
}

	
void TTurret::updateBehaviour() {
	shotTimer += (shotTimer < cooldown);
	seekEnemies();
}

void TTurret::draw() {
	selection->draw(absPos(), baseRotation);

	Graphics::SetColor(0xFFFFFFFF);
	Graphics::SetRotation(baseRotation);
	Graphics::DrawImage(animation->getImage(), xAbs(), yAbs());

	if (animation->getImage().getFrameCount() == 2) /* turret */
		Graphics::SetRotation(turretRotation);
		Graphics::DrawImage(animation->getImage(), xAbs(), yAbs(), 1);
	}
	Graphics::SetRotation(0);
}
			
void TTurret::selectRotation() {
	parent_type::selectRotation();
	turretRotation = baseRotation;
}
	
void TTurret::updateParameters(const Info& source) {
	parent_type::updateParameters(source);
	cooldown = info["cooldown"].asUint;
	damage = info["damage"].asUint;
	range = info["range"].asFloat * GameMechanics::TILE_SIZE;
	turretMaxAngle = info["maxAngle"].asInt;
	//bulletAcceleration = *source->at("bulletAcceleration").as
    //bulletSize = *source->at("bulletSize").as
}

void TTurret::InfoLoader(TBuilding::Info& info, std::istream& source) {
    parent_type::InfoLoader(info, source);

    string buffer;

    std::getline(source, buffer);
    info["range"].asFloat = std::stof(buffer);

    std::getline(source, buffer);
    info["cooldown"].asUint = std::stoul(buffer);

    std::getline(source, buffer);
    info["damage"].asUint = std::stoul(buffer);

    std::getline(source, buffer);
    info["maxAngle"].asInt = std::stoi(buffer);
}
