#ifndef __TURRETSELECTION_H__
#define __TURRETSELECTION_H__

#include "selection.h"
#include "turret.h"

class TTurret::Selection : public TBuilding::Selection
{
public:
	Selection();
	Selection(TTurret const* owner);
	~Selection();

	void draw(const Point2ui& where_);
protected:
	typedef TBuilding::Selection parent_type;
	TTurret* owner;

	virtual void drawCooldownBar(const Point2ui&  where_);
};

#endif