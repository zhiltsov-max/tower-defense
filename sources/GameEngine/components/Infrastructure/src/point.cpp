#include "GameEngine/Infrastructure/point.h"


GE_BEGIN_ENGINE_NAMESPACE

namespace Graphics {

bool isPointInRect(int pointX, int pointY, int rectX1, int rectY1, int rectX2, int rectY2) {
    if (rectX2 < rectX1) { std::swap(rectX1, rectX2); }
    if (rectY2 < rectY1) { std::swap(rectY1, rectY2); }
    return ((rectX1 <= pointX) && (pointX <= rectX2) &&
        (rectY1 <= pointY) && (pointY <= rectY2));
}

} // namespace Graphics

GE_END_ENGINE_NAMESPACE