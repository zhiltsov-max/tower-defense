#include "mob_healthbar.h"


HealthBar::HealthBar(TMob const* owner_, Point2ui& offset_) :
	owner(owner_),
	offset(offset_),
	color(defaultColor)
{}


Graphics::ZIndex getZIndex() const {
	return GraphicsZIndex::MobEffects;
}

void HealthBar::setZIndex(int value) {
	UNUSED( value )
}

void HealthBar::setOffset(const Point2ui& value) {
	offset = value;
}

void HealthBar::draw(const Point2ui& where_) {
	Graphics::SetColor(color);
	Graphics::DrawRect(mob->getPos().x() + offset.x(), mob->getPos().y() + offset.y(), mob->getSize().x(), 5);
	Graphics::SetColor(defaultHealthColor);
	Graphics::DrawRect(mob->getPos().x() + offset.x() + 1, mob->getPos().y() + offset.y() + 1,
		(mob->getSize().x() * mob->getHealth() / mob->getMaxHealth()) - 2, 3);
}
