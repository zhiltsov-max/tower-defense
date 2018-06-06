#ifndef MOB_FLYER_H
#define MOB_FLYER_H

#include "mob.h"


class TFlyerMob : public TMob
{
public:
    Appearance getAppearance() const;
protected:
	typedef TMob parent_type;
};

#endif //MOB_FLYER_H
