#ifndef MOB_ANIMATION_H
#define MOB_AINMATION_H

#include "../../../GameEngine/Scene/animation.h"
#include "mob.h"


enum class MobAnimationGroup {
	undefined = 0,
	Walking
};

class TMob::Animation : public TAnimation
{
public:
    Animation(const TMob::ClassId& classId);
protected:
	typedef TAnimation parent_type;
};

#endif //MOB_AINMATION_H
