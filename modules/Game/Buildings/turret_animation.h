#ifndef __TURRETANIMATION_H__
#define __TURRETANIMATION_H__

#include "animation.h"
#include "turret.h"

class TTurret::Animation : public TBuilding::Animation
{
public:
	Animation() : parent_type() {}
	Animation(uint buildingClass) : parent_type(buildingClass) {}
	~Animation() {}
protected:
	typedef TBuilding::Animation parent_type;
};

#endif