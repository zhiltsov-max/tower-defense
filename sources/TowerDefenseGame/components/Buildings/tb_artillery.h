#ifndef TB_ARTILLERY_H
#define TB_ARTILLERY_H

#include "tb_rocket.h"


class TB_Artillery : public TB_Rocket
{
public:
	TB_Artillery() :
		parent_type(),
		bulletAcceleration(0.5),
		bulletSize(7)
	{}

	TBuilding* clone() const {
        return new TB_Artillery(*this);
	}

    ClassId getClass() const {
		return BuildingClass::Artillery;
	}
private:
	typedef TB_Rocket parent_type;
};

#endif //TB_ARTILLERY_H
