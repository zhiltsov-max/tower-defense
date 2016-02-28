#include "mob.h"
#include "mob_controller.h"


TMob::TMob() :
	parent_type(),
	path(),
	speed(0.0f),
	health(0),
	maxHealth(0),
	animation(nullptr),
	pos()
{}

TMob::TMob(const TMob& other) :
	parent_type(other),
	path(other.path),
	speed(other.speed),
	health(other.health),
	maxHealth(other.maxHealth),
	animation(nullptr),
	pos(other.pos)
{}
	
TMob::~TMob()
{}

void TMob::initialize(Info const* source) {
    maxHealth = source->at("maxHealth").asInt;
    speed = source->at("speed").asFloat;
	loadAnimation(source);
	loadHealthBar();
}

void TMob::update() {
	if (isAlive() == false) {
		die();
		return;
	}
		
	updateTarget();
	updatePosition();
	updateAnimation();
}

void TMob::draw() {
	Graphics::SetColor(0xffffffff);
		
	TImage* image = animation->getImage();
	if (image != nullptr) {
		Graphics::DrawImage(image, pos.x() - getSize().x() * 0.5, pos.y() - getSize().y(), animation->getCurrentFrame());
	} else {
		Graphics::DrawRect(pos.x() - getSize().x() * 0.5, pos.y() - getSize().y());
	}
}


void TMob::setPos(const Point2ui& value) {
	pos = value;
}
void TMob::setZIndex(int value) {
	UNUSED( value )
}	
void TMob::setHealth(int value) {
	health = value;
}
	
const TMob::Path& TMob::getPath() const {
	return path;
}
int TMob::getReward() const {
	return MobController::getCurrentReward(getClass());
}
int TMob::getPoints() const {
	return MobController::getCurrentPoints(getClass());
}	
Graphics::ZIndex TMob::getZIndex() const {
	return GraphicsZIndex::Mobs;
}
const string& TMob::getDescription() const {
	return *MobController::getParameter(getClass(), "description").as<string>();
}	
int TMob::getHealth() const {
	return health;
}
int TMob::getMaxHealth() const {
	return maxHealth;
}
float TMob::getSpeed() const {
	return speed;
}
const Point2ui& TMob::getSize() const {
	return animation->getSize();
}	
const Point2ui& TMob::getPos() const {
	return pos;
}
	
bool TMob::isOnTile(const Point2ui& tilePos, int tileAppearance = MobAppearance::Ground) const {
	if ((pos.isInRect(
			tilePos * GameMechanics::TILE_SIZE,
			(tilePos + Point2ui(1, 1)) * GameMechanics::TILE_SIZE) == true
		) && (getAppearance() & tileAppearance)) {
		return true;
	}
	return false;
}
		
bool TMob::isAlive() const {
	return (0 < health);
}

bool TMob::hasReachedPathEnd() const {
	return (path.exists() == true) && (path.getPosition() == path.length());
}

void TMob::loadHealthBar() {
	healthBar = std::unique_ptr<HealthBar>(new HealthBar(this, Point2ui(-getSize().x() * 0.5, -getSize().y() - 5)));
}
	
void TMob::checkPath() {
	if (path.exists() == true) { return; }

	int policy = MobController::getPathSelectionPolicy();
	switch (policy) {
	case PathSelectionPolicy::Static:
        /* none or find nearest node */
							
	case PathSelectionPolicy::Dynamic:
        findPath();
        break;
			
	default:
		{
			throw_("Wrong game type: " + std::to_string((long long)policy) + ".", "TMob::checkPath");
		}
	}	
}
	
void TMob::updatePosition() {
	if (isAlive() == false) { return; }
	if (path.exists() == false) { return; }
	if (path.empty() == true) { return; }
	
	float speed = getSpeed();
	const Path::Node& nextNode = path.getNextNode();

	float direction = std::atan2f(nextNode.absPos().y() - pos.y(), nextNode.absPos().x() - pos.x());
	pos.x() += speed * (std::cos(direction) + rnd(-0.5, 0.5));
	pos.y() += speed * (std::sin(direction) + rnd(-0.5, 0.5));
}	

void TMob::updateTarget() {
	if (path.exists() == false) {
		checkPath();
		if (path.exists() == false) { /* If mob in a closet */
			return;
		}
	}
		
	if ((path.empty() == false) && (hasCrossedNode() == false)) { return; }
	if (hasReachedPathEnd() == true) {
		hurtBase();
		return;
	}

	if (MobController::getPathSelectionPolicy() == PathSelectionPolicy::Dynamic) {
		path.removeFirst();
	} else {
		switch (getAppearance()) {
		case MobAppearance::Ground:
            path.makeStep();
            break;

		case MobAppearance::Air:
            if ((hasCrossedNode() == true) && (path.getPosition() == path.length() - 1)) {
                path.makeStep();
            } else {
                path.setPosition(path.length() - 1);
            }
            break;

		case MobAppearance::Water:
            path.makeStep();
            break;

		default:
			{
                Throw("Unexpected mob appearance " + std::to_string(getAppearance()), "TMob::updateTarget");
			}
		}
	}
}

void TMob::updateAnimation() {
	if (isAlive() == false) { return; }
	//animation->setAction(MobAnimationGroups::Walk);
	animation->update();
}	
	
			
bool TMob::hasCrossedNode() const {
	const Path::Node& nextNode = path.getNextNode();
	return norm(nextNode.getPos(), pos, NormType::NORM_SQUARED) < std::pow(nextNode.getSize(), 2);
}
		
void TMob::findPath() {
	const auto moveCosts = MobController::getPassabilityMap().forAppearance(getAppearance());
		
	const Path::Node& pathEnd = MobController::getNodeMap().findNearestExit(
		(int)((pos.x() + 0.0) / GameMechanics::TILE_SIZE), (int)((pos.y() + 0.0) / GameMechanics::TILE_SIZE));

	Path::Path newPath = TPathCreator::CreatePath(
		Point2ui((pos.x() + 0.0) / GameMechanics::TILE_SIZE, (pos.y() + 0.0) / GameMechanics::TILE_SIZE),
		Point2ui((pathEnd.absPos().x() + 0.0) / GameMechanics::TILE_SIZE, (pathEnd.absPos().y() + 0.0) / GameMechanics::TILE_SIZE),
		moveCosts);
	path.set(newPath);
}

void TMob::die() {
    TEvent_MobKilled(getClass());
	remove();
}
	
void TMob::hurtBase() {
    TEvent_MobPassed(getClass());
	remove();
}

void TMob::loadAnimation(Info const* source) {
	UNUSED( source )
    animation.reset(new Animation(getClass()));
	animation->setActionIndex(MobAnimationGroup::Walking);
}

int TMob::CmpGetFastest(TMob const* m1, TMob const* m2) {
	if ((m1 == nullptr) || (m2 == nullptr)) { return 0; }
	return (m1->speed - m2->speed);
}
	
int TMob::CmpGetMostDamaged(TMob const* m1, TMob const* m2) {
	if ((m1 == nullptr) || (m2 == nullptr)) { return 0; }
	return (m1->health - m2->health);
}
	
int TMob::CmpGetClosest(TMob const* m1, TMob const* m2) {
	if ((m1 == nullptr) || (m2 == nullptr)) { return 0; }
	float mob1PP = m1->getPath().getPercentage();
	float mob2PP = m2->getPath().getPercentage();
	return (mob2PP - mob1PP);
}
