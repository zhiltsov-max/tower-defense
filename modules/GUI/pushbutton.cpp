#include "pushbutton.h"
#include "Application/application_ui.h"


BEGIN_GUI

const TColorModifier TPushButton::COLOR_MODIFIER_HOVER    { 0.7, 0.7, 0.7 };
const TColorModifier TPushButton::COLOR_MODIFIER_NORMAL   { 1.0, 1.0, 1.0 };
const TColorModifier TPushButton::COLOR_MODIFIER_DISABLED { 0.5, 0.5, 0.5 };


TPushButton::TPushButton(const TPushButtonSource& source) :
    parent_type(source),
    buttonClick_impl(source.buttonClick)
{}

void TPushButton::_draw(TRenderTarget& target) {
    if (needsRedraw == true) {
        TRenderTarget& localTarget = renderImage.getRenderTarget();
        localTarget.clear(_currentColor());
        if (image.drawingObject != nullptr) {
            if (image.image != nullptr) {
                sf::Sprite* sprite = image.drawingObject.get();
                if (sprite != nullptr) {
                    sprite->setColor(_currentColor());
                }
            }
            localTarget.draw(*image.drawingObject);
        }

        if (textArea.GetText().empty() == false) {
            textArea.Draw(localTarget);
        }

        renderImage.createDrawingObject();
        needsRedraw = false;
    }

    TCoordinate position = GetScreenPosition();
    if (clicked == true) {
        position += TCoordinate(1.f, 1.f);
    }
    renderImage.getDrawingObject().setPosition(position.x, position.y);
    target.draw(renderImage.getDrawingObject());

#if defined(_DEBUG)
    if (Debug::show_frames() == true) {
        sf::RectangleShape boundingRect( sf::Vector2f(size.x, size.y) );
        boundingRect.setFillColor(sf::Color(0, 0, 0, 0));
        boundingRect.setOutlineColor(sf::Color(0, 255 - 55 * mouseOver, 0, 128));
        boundingRect.setOutlineThickness(2.f);
        boundingRect.setPosition(position.x, position.y);
        target.draw(boundingRect);

        sf::Text rectText = TFont().CreateText(String::toWide(name));
        rectText.setPosition(position.x, position.y);
        target.draw(rectText);
    }
#endif
}

void TPushButton::_OnClick() {
    if (buttonClick_impl != nullptr) {
        buttonClick_impl(nullptr);
    }
}

void TPushButton::_OnHover() {
    colorModifier = COLOR_MODIFIER_HOVER;
}

void TPushButton::_OnMouseLeave() {
    colorModifier = COLOR_MODIFIER_NORMAL;
}

void TPushButton::_OnDisabled() {
    colorModifier = COLOR_MODIFIER_DISABLED;
}

void TPushButton::_OnEnabled() {
    colorModifier = COLOR_MODIFIER_NORMAL;
}

END_GUI
