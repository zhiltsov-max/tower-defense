#include "map_trigger.h"


void TMapTrigger::setPos(const Point2ui& value) {
	pos = value;
}	
const Point2ui& TMapTrigger::getPos() const {
	return pos;
}
		
void TMapTrigger::setSize(const Point2ui& value) {
	size = value;
}
const Point2ui& TMapTrigger::getSize() const {
	return size;
}
	
#if _DEBUG_
void TMapTrigger::draw() {
	if (DebugTools::isDebugEnabled() == true) {
		Graphics::SetColor(color);
		Graphics::DrawRect(pos[0], pos[1], size[0], size[1]);
	}
}
#endif
