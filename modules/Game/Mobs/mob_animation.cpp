#include "mob_animation.h"
#include "mob_controller.h"


TMob::Animation::Animation(const TMob::ClassId& classId) :
	parent_type()
{	
    const auto resources = std::move(MobsController::getParameter(classId, "resources").split(";"));
	for(auto it = resources.cbegin(); it != resources.cend(); ++it) {
		const TSceneResource& resource = MobsController::getResources().getResource(*it);
		if (resource.getType() != TSceneResource::Type::image) {
			continue;
		}
			
		image = resource.getObject<TImage*>();
		frameWidth = image->width;
		frameHeight = image->height;
		framesCount = image->getFramesCount();
		recognizeFrames(resource.getMetadata());
		break;
    }
}
