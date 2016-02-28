#ifndef BUILDING_SELECTION_H
#define BUILDING_SELECTION_H

#include "Core/core.h"


namespace TD {


class TBuildingSelection
{
public:
    Selection() = default;
    Selection(const Info& info);
    virtual ~Selection() = default;
				
	int getZIndex() const;

	virtual void draw(const Point2ui& screenPos, const float baseRotation);
protected:
    static constexpr Graphics::ARGB zoneColor = 0x998BFF32;


    using Image = std::shared_ptr<TImage>;
	Image image;
	Point2ui offset;
};


} // namespace TD

#endif //BUILDING_SELECTION_H
