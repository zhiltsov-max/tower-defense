#ifndef MOB_WALKER_H
#define MOB_WALKER_H

#include "mob.h"


class TMob_Walker : public TMob
{
public:
    Appearance getAppearance() const;
	uint getBoilingConditionTime() const;	
	
	bool isBoiling() const;
		
	void setBoiling(bool value);
	
	void draw();
protected:
	typedef TMob parent_type;
	uint boilingTime;

	void updatePosition();	
	void updateBoiling();

	void hurtAround();
};

#endif //MOB_WALKER_H
