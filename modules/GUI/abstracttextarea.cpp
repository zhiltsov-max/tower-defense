#include "abstracttextarea.h"
#include <limits>



BEGIN_GUI


TAbstractTextArea::TAbstractTextArea(
    const TAbstractTextAreaSource& source, const Parent& parent
) :
    parent(parent),
    position(source.position),
    text(source.text),
    color(source.color),
    font(source.font)
{}

bool TAbstractTextArea::_parentExists() const {
    return parent != nullptr;
}

void TAbstractTextArea::_checkBorders() {
    float left = 0;
    float right = std::numeric_limits<float>::max();
    float top = 0;
    float bottom = std::numeric_limits<float>::max();
    if (_parentExists() == true) {
        const TPadding parentBorder = parent->GetInnerBorder();
        left = 0;
        right = std::max(
            parent->GetOwnSize().x - parentBorder.right - GetWidth(), 0.f);
        top = 0;
        bottom = std::max(
            parent->GetOwnSize().y - parentBorder.bottom - GetHeight(), 0.f);
    }

    position.x = std::max(left, std::min(right, position.x));
    position.y = std::max(top, std::min(bottom, position.y));
}

const TAbstractTextArea::Parent& TAbstractTextArea::GetParent() const {
    return parent;
}
void TAbstractTextArea::SetParent(const Parent& value) {
    parent = value;
}

const TCoordinate& TAbstractTextArea::GetPosition() const {
    return position;
}

TCoordinate TAbstractTextArea::GetScreenPosition() const {
    if (_parentExists() == true) {
        TPadding innerBorder = parent->GetInnerBorder();
        return position + parent->GetScreenPosition() +
            TCoordinate(innerBorder.left, innerBorder.top);
    } else {
        return position;
    }
}

void TAbstractTextArea::SetPosition(TCoordinate value) {
    value.x = std::max(0.f, value.x);
    value.y = std::max(0.f, value.y);

    if (position != value) {
        position = std::move(value);
        _checkBorders();
    }
}

void TAbstractTextArea::SetPosition(float x, float y) {
    SetPosition(TCoordinate(x, y));
}


float TAbstractTextArea::GetWidth() const {
    float width = font.GetTextWidth(text);
    return width;
}

float TAbstractTextArea::GetHeight() const {
    float height = font.GetTextHeight(text);
    return height;
}

TSize TAbstractTextArea::GetSize() const {
    return TSize(GetWidth(), GetHeight());
}

void TAbstractTextArea::SetText(const TextString& value) {
    text = value;
}

const TextString& TAbstractTextArea::GetText() const {
    return text;
}


void TAbstractTextArea::SetColor(const TColor& value) {
    color = value;
}

const TColor& TAbstractTextArea::GetColor() const {
    return color;
}

void TAbstractTextArea::SetFont(const TFont& value) {
    font = value;
}

const TFont& TAbstractTextArea::GetFont() const {
    return font;
}

void TAbstractTextArea::Draw(TRenderTarget& target,
    const TCoordinate& offset)
{
    const auto drawingPosition = offset + position;
    auto textShape = font.CreateText(text);
    textShape.setColor(color);
    textShape.setPosition(drawingPosition);

    target.draw(textShape);
}


END_GUI
