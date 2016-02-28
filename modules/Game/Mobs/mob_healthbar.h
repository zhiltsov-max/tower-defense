#ifndef MOB_HEALTHBAR_H
#define MOB_HEALTHBAR_H

#include "mob.h"


class TMob::HealthBar
{
public:
	HealthBar(TMob const* owner_, Point2ui& offset_);

	Graphics::ZIndex getZIndex() const;
	void setZIndex(int value);
	void setOffset(const Point2ui& value);

	void draw(const Point2ui& where_);	
protected:
	TMob* owner;
	Point2ui offset;
	
	static const Graphics::ARGB defaultColor = 0xFF010101;
	static const Graphics::ARGB defaultHealthColor = 0xFF33FF33;
	Graphics::ARGB color;
};

#endif //MOB_HEALTHBAR_H
