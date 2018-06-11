#include "point.h"


bool isPointInRect(int pointX, int pointY, int rectX1, int rectY1, int rectX2, int rectY2) {
    if (rectX2 < rectX1) { std::swap(rectX1, rectX2); }
    if (rectY2 < rectY1) { std::swap(rectY1, rectY2); }
    return ((rectX1 <= pointX) && (pointX <= rectX2) &&
        (rectY1 <= pointY) && (pointY <= rectY2));
}
