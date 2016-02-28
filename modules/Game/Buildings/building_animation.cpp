#include "building_animation.h"
#include "buildings_controller.h"



namespace TD {


TBuildingAnimation::TBuildingAnimation(const TBuildingInfo& info) :
	parent_type()
{
    const auto resources = std::move(BuildingsController::getParameter(classId, "resources").split(";"));
	for(auto it = resources.cbegin(); it != resources.cend(); ++it) {
		const TSceneResource& resource = BuildingsController::getResources().getResource(*it);
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


} // namespace TD
