#include "turretselection.h"


TTurret::Selection::Selection() :
	parent_type(),
	owner(nullptr)
{}

TTurret::Selection::Selection(TTurret const* owner) :
	parent_type(owner),
	owner(owner_)
{}

TTurret::Selection::~Selection()
{}

void TTurret::Selection::draw(const Point2ui& where_) {
	parent_type::_draw(where_);
	drawCooldownBar(where_);
}

virtual void TTurret::Selection::drawCooldownBar(const Point2ui&  where_) {		
	Graphics::SetColor(0x30000000);
	Graphics::DrawRect(owner->xAbs() - 8, owner->yAbs() + owner->getSize().y() * 0.5, 16, 5);
		
	Graphics::SetColor(0x8FFFCC00);
	float reloadingPercent = std::min(float(owner->getTimer()) / owner->getCooldown(), 1.0f);
	Graphics::DrawRect(owner->xAbs() - 7, owner->yAbs() + owner->getSize().y() * 0.5 + 1, 14 * reloadingPercent, 3);
}
