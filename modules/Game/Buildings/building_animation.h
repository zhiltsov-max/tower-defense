#ifndef BUILDING_ANIMATION_H
#define BUILDING_ANIMATION_H

#include "Game/Components/animation.h"



namespace TD {


enum class BuildingAnimationGroup {
	undefined = 0,	
	Normal,
	Explode
};

class TBuildingAnimation : public TAnimation
{
public:
    TBuildingAnimation(const TBuildingInfo& info);
private:
	typedef TAnimation parent_type;
};


} // namespace TD

#endif //BUILDING_ANIMATION_H
