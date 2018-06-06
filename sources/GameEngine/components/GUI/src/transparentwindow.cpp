#include "transparentwindow.h"

BEGIN_GUI

TTransparentWindow::TTransparentWindow(const TTransparentWindowSource& source) :
    parent_type(source),
    thresholdOpacity(source.thresholdOpacity),
    minOpacity(source.minOpacity),
    maxOpacity(source.maxOpacity),
    opacityChangingSpeed(source.opacityChangingSpeed)
{}

void TTransparentWindow::SetThresholdOpacity(double value) {
    thresholdOpacity = value;
}

double TTransparentWindow::GetThresholdOpacity() const {
    return thresholdOpacity;
}

void TTransparentWindow::SetMinOpacity(double value) {
    minOpacity = std::min(maxOpacity, value);
}

void TTransparentWindow::SetMaxOpacity(double value) {
    maxOpacity = std::max(minOpacity, value);
}

double TTransparentWindow::GetMinOpacity() const {
    return minOpacity;
}

double TTransparentWindow::GetMaxOpacity() const {
    return maxOpacity;
}

void TTransparentWindow::_update() {
    if (IsVisible() == false) {
        return;
    }
    parent_type::_update();
    _updateOpacity();
}

void TTransparentWindow::_updateOpacity() {
    const TCoordinate position = GetScreenPosition();
    const bool isOver = IO::IsCursorInRect(position, position + size);

    double currentOpacity = colorModifier.aMod * color.a;

    if (isOver == true) {
        if (currentOpacity < maxOpacity) {
            currentOpacity += (maxOpacity - currentOpacity) * opacityChangingSpeed;
            colorModifier.aMod = currentOpacity / color.a;
        }
    } else {
        if (minOpacity <= currentOpacity) {
            currentOpacity -= (currentOpacity - minOpacity) * opacityChangingSpeed;
            colorModifier.aMod = currentOpacity / color.a;
        }
    }
}

void TTransparentWindow::_drawChildren(TRenderTarget& target) {
    if (thresholdOpacity < colorModifier.aMod * color.a) {
        parent_type::_drawChildren(target);
    }
}

END_GUI
