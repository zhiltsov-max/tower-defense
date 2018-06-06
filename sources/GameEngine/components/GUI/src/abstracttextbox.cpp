#include "abstracttextbox.h"



BEGIN_GUI


TAbstractTextBox::TAbstractTextBox(const TAbstractTextBoxSource& source) :
    parent_type(source),    
    color(source.color),
    colorModifier(),
    maxSize(source.maxSize),
    minSize(source.minSize),
    allowEdit(source.allowEdit),
    borderSize(source.borderSize),
    borderColor(source.borderColor),
    text()
{}

list<TAbstractTextBox::Signal> TAbstractTextBox::_enumSignals() const {
    auto signals = parent_type::_enumSignals();

    signals.emplace_back(DefaultSignalID::ObjectTextChanged);

    return signals;
}

void TAbstractTextBox::_draw(TRenderTarget& target) {
    if (needsRedraw == true) {
        TRenderTarget& localTarget = renderImage.getRenderTarget();
        localTarget.clear();

        sf::RectangleShape innerBorder( sf::Vector2f(size.x, size.y) );
        innerBorder.setFillColor(_currentColor());

        if (0.f < borderSize) {
            innerBorder.setOutlineColor(_currentBorderColor());
            innerBorder.setOutlineThickness(borderSize);
        }
        localTarget.draw(innerBorder);

        if (text->GetText().empty() == false) {
            text->Draw(localTarget, TCoordinate(borderSize, borderSize));
        }

        renderImage.createDrawingObject();
        needsRedraw = false;
    }

    const TCoordinate position = GetScreenPosition();
    renderImage.getDrawingObject().setPosition(position.x, position.y);
    target.draw(renderImage.getDrawingObject());

#if defined(_DEBUG)
    if (Debug::show_frames() == true) {
        sf::RectangleShape boundingRect( sf::Vector2f(size.x, size.y) );
        boundingRect.setFillColor(sf::Color(0, 255 - 55 * mouseOver, 0, 128));
        boundingRect.setPosition(position.x, position.y);
        target.draw(boundingRect);

        sf::Text rectText;
        rectText.setString(name);
        rectText.setPosition(position.x, position.y);
        target.draw(rectText);
    }
#endif
}

TColor TAbstractTextBox::_currentColor() const {
    return colorModifier.modify(color);
}

TColor TAbstractTextBox::_currentBorderColor() const {
    return colorModifier.modify(borderColor);
}


void TAbstractTextBox::_OnAllowingEdit() { /*none*/ }
void TAbstractTextBox::_OnDisallowingEdit() { /*none*/ }
void TAbstractTextBox::_OnTextChanged() { needsRedraw = true; }
void TAbstractTextBox::_OnColorChanged() { needsRedraw = true; }


const TextString& TAbstractTextBox::GetText() const {
    return text->GetText();
}

void TAbstractTextBox::SetText(const TextString& value) {
    if (text->GetText() != value) {
        text->SetText(value);
        _OnTextChanged();
        GetSignal(DefaultSignalID::ObjectTextChanged).Send();
    }
}

void TAbstractTextBox::SetColor(const TColor& value) {
    if (color != value) {
        color = value;
        _OnColorChanged();
    }
}

const TColor& TAbstractTextBox::GetColor() const {
    return color;
}

bool TAbstractTextBox::IsResizable() const {
    return ((maxSize != TSize()) && (minSize == maxSize)) == false;
}

void TAbstractTextBox::SetMinSize(const TSize& value) {
    if (maxSize != value) {
        maxSize.x = std::max(minSize.x, value.x);
        maxSize.y = std::max(minSize.y, value.y);
        if (size < maxSize) {
            SetSize(maxSize);
        }
    }
}

void TAbstractTextBox::SetMaxSize(const TSize& value) {
    if (minSize != value) {
        minSize.x = std::min(value.x, maxSize.x);
        minSize.y = std::min(value.y, maxSize.y);
        if (size < minSize) {
            SetSize(minSize);
        }
    }
}

const TSize& TAbstractTextBox::GetMinSize() const {
    return minSize;
}

const TSize& TAbstractTextBox::GetMaxSize() const {
    return maxSize;
}

void TAbstractTextBox::SetSize(const TSize& value) {
    if ((IsResizable() == true) &&
       ((maxSize != TSize()) && (value <= maxSize) && (minSize <= value)))
    {
        parent_type::SetSize(value);
    }
}


bool TAbstractTextBox::IsEditable() const {
    return allowEdit;
}

void TAbstractTextBox::SetEditable(bool value) {
    if (value != allowEdit) {
        allowEdit = value;

        if (value == true) {
            _OnAllowingEdit();
        } else {
            _OnDisallowingEdit();
        }
    }
}


float TAbstractTextBox::GetBorderSize() const {
    return borderSize;
}

void TAbstractTextBox::SetBorderSize(float value) {
    if (borderSize != value) {
        borderSize = value;
        _OnResized();
    }
}


const TFont& TAbstractTextBox::GetFont() const {
    return text->GetFont();
}

void TAbstractTextBox::SetFont(const TFont& value) {
    if (text->GetFont() != value) {
        text->SetFont(value);
        _OnTextChanged();
    }
}


END_GUI
