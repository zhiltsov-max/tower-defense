#include "building_selection.h"
#include "buildings_info.h"



namespace TD {


TBuilding::Selection::Selection(const TBuildingInfo& info) {
    const auto resources = String::split(info[owner->getClass()]["resources"].asString, ';');
	for(auto it = resources.cbegin(); it != resources.cend(); ++it) {
        if (String::endsWith(*it, "Sector") == true) {
			image = Image(BuildingsController::getResources().getResource(*it).getObject<TImage>());
			break;
		}
	}
}

				
int TBuilding::Selection::getZIndex() const {
	return GraphicsZIndex::BuildingEffects;
}

void TBuilding::Selection::draw(const Point2ui& where_, const float baseRotation) {
	Graphics::SetColor(0xFFFFFFFF);
	Graphics::SetRotation(baseRotation);
	Graphics::DrawImage(image, where_.x() + offset.x(), where_.y() + offset.y());
	Graphics::SetRotation(0);
}


} // namespace TD
