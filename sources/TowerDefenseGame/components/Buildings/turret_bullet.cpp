#include "bullet.h"


TBuilding::Bullet::Bullet(const Point2f& pos_, float damage_, float acceleration_, TMob const* target_, ushort size_) :
	pos(pos_),
	damage(damage_),
	acceleration(acceleration_),
	target(target_),
	size(size_),
	color(DEFAULT_COLOR)
{}

static Graphics::ZIndex TBuilding::Bullet::getZIndex() const {
	return GraphicsZIndex::Bullet;
}
void TBuilding::Bullet::setZIndex(Graphics::ZIndex value) {
	UNUSED( value )
}

const Point2f TBuilding::Bullet::getPos() const {
	return pos;
}
void TBuilding::Bullet::setPos(float x, float y) {
	pos = Point2f(x, y);
}
void TBuilding::Bullet::setPos(const Point2f& pos_) {
	pos(pos_);
}
	
bool TBuilding::Bullet::isCloseToTarget() const {
	return (target->getPos() - pos).abs() <= target->getSize();
}

void TBuilding::Bullet::update() {
	if (target == nullptr) {
		return;
	}
	if (target->isAlive() == false) {
		return;
	}
			
	if (isCloseToTarget() == true) {
		hurt();
	} else {
		move();
	}
}

void TBuilding::Bullet::draw() {
	Graphics::SetColor(color);
	Graphics::DrawOval(pos.x() - size, pos.y() - size, 2 * size, 2 * size);
}

void TBuilding::Bullet::move() {
	speed += acceleration;

	const Point2f diff = target->getPos() - pos;
	double angle =  std::atan2(pos.y(), pos.x());
	pos += Point2f(speed * std::cos(angle), speed * std::sin(angle));
}	
void TBuilding::Bullet::hurt() {
	target->setHealth(target->getHealth() - damage);
}