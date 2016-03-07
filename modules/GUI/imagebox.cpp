#include "imagebox.h"

BEGIN_GUI

TImageBox::TImageBox(const TImageBoxSource& source) :
    parent_type(source),
    color(source.color),
    image(source.image)
{}

const TColor& TImageBox::GetColor() const {
    return color;
}

void TImageBox::SetColor(const TColor& value) {
    if (color != value) {
        color = value;
        _OnImageChanged();
    }
}

bool TImageBox::HasImage() const {
    return image.image != nullptr;
}

const TImageBox::Image& TImageBox::GetImage() const {
    return image;
}

void TImageBox::SetImage(Image&& value) {
    if (image != value) {
        image = std::move(value);
        _OnImageChanged();
    }
}

TColor TImageBox::_currentColor() const {
    return colorModifier.modify(color);
}

void TImageBox::_draw(TRenderTarget& target) {
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

        renderImage.createDrawingObject();
        needsRedraw = false;
    }

    const TCoordinate position = std::move(GetScreenPosition());
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

void TImageBox::_OnImageChanged() { needsRedraw = true; }

END_GUI
