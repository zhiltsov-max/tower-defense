#ifndef TURRET_H
#define TURRET_H

#include "building.h"
#include "../Mobs/mob.h"


class TTurret : public TBuilding /*Abstract*/
{
public:	
	TTurret();
    void initialize(const Info& info);

	uint getTimer() const;
	uint getCooldown() const;
	uint getDamage() const;
	float getRange() const;
	
	bool isCharged() const;
	bool canDamageMob(TMob const* mob) const;

    void draw();

    static void InfoLoader(Info& info, std::istream& source);
protected:
	typedef TBuilding parent_type;
	class Animation;
	class Selection;	
	class Bullet;
	typedef std::list<std::shared_ptr<Bullet>> Bullets;

	int turretRotation;
	int turretMaxAngle;
	
	uint shotTimer;	
	uint cooldown; /* 60(FPS) * sec.*/
	uint damage; /* hp */
	float range; /* in tiles */
	
	float bulletAcceleration;
	float bulletSize;

	Bullets bullets;


    void loadAnimation(const Info& source);
    void loadSelection(const Info& source);

	virtual void seekEnemies();	
    const TMob* selectEnemy(std::list<TMob const*>& accessibleTargets) const;
    list<TMob const*> findEnemiesInRange() const;

	virtual void checkRotation() = 0;	
	virtual void setRotation(int angle = 361);

	virtual void shot(TMob const* target);

	void updateBehaviour();			
	void selectRotation();
	
    void updateParameters(const Info& source);
};


#endif //TURRET_H
