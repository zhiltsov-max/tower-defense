#ifndef TB_BASE_H
#define TB_BASE_H

#include "building_turret.h"


class TB_Base : public TTurret
{
public:
	TB_Base() : 
		parent_type(),
		bulletAcceleration(1),
		bulletSize(1)
	{}

    TBuilding* clone() {
        return new TB_Base(*this);
	}

    ClassId getClass() const {
		return BuildingClass::Base;
	}

	void draw() {
		parent_type::draw();

		Graphics::SetRotation(turretRotation);
		Graphics::DrawLine(xAbs(), yAbs(), xAbs() + 25, yAbs());
		Graphics::SetRotation(0);
	}
private:
	typedef TTurret parent_type;
protected:
	static const int baseRotationPerFrame = 5;
	

	void checkRotation() {
		baseRotation = baseRotation % 360;
		turretRotation = turretRotation % 360;
		
		if (baseRotation + turretMaxAngle < turretRotation) {
			turretRotation = baseRotation + turretMaxAngle;
			baseRotation += baseRotationPerFrame;
		} else if (turretRotation < baseRotation - turretMaxAngle) {
			turretRotation = baseRotation - turretMaxAngle;
			baseRotation -= baseRotationPerFrame;
		}
	}
};

#endif //TB_BASE_H
