#ifndef TB_ROCKET_H
#define TB_ROCKET_H

#include "buildings_list.h"


class TB_Rocket : public TTurret
{
public:
	TB_Rocket() :
		parent_type(),
		bulletAcceleration(0.25f),
		bulletSize(2)
	{}

	TBuilding* clone() const {
        return new TB_Rocket(*this);
	}

    ClassId getClass() const {
		return BuildingClass::Rocket;
	}
private:
	typedef TTurret parent_type;
protected:
	void checkRotation() {
		int tBaseRot = baseRotation;
		int tTurrRot = turretRotation;
		if (360 < std::abs(tBaseRot)) {
			tBaseRot = tBaseRot % 360;
		}
		if (360 < std::abs(tTurrRot)) {
			tTurrRot = tTurrRot % 360;
		}

		if (tBaseRot + turretMaxAngle < tTurrRot) {
			turretRotation = baseRotation + turretMaxAngle;
		} else if (tTurrRot < tBaseRot - turretMaxAngle) {
			turretRotation = baseRotation - turretMaxAngle;
		}
	}
	
    list<TMob const*> findEnemiesInRange() const {
        auto enemies = parent_type::findEnemiesInRange();
		for(auto it = enemies.begin(); it != enemies.end(); ++it) {
			if (canSeeTarget(*it) == false) {
				enemies.erase(it);
			}
		}
		return enemies;
	}
	
	bool canSeeTarget(TMob const* target) const {
		int tBaseRot = baseRotation;
		int targetRot = std::atan2(target->getPos().y() - yAbs(), target->getPos().x() - xAbs());
		if (targetRot < 0) { targetRot = 360 + targetRot; }
		if (360 < std::abs(tBaseRot)) {
			tBaseRot = tBaseRot % 360;
		}
		if (360 < std::abs(targetRot)) {
			targetRot = targetRot % 360;
		}
		if ((targetRot <= tBaseRot + turretMaxAngle) && (tBaseRot - turretMaxAngle <= targetRot)) {
			return true;
		}
		return false;
	}
};

#endif //TB_ROCKET_H
