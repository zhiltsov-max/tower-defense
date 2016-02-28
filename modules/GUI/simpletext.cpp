#include "simpletext.h"
#include "textarea.h"

BEGIN_GUI

TSimpleText::TSimpleText(const TSimpleTextSource& source) :
    parent_type(source),
    borderSize(source.borderSize),
    borderColor(source.borderColor),
    borderOffset(source.borderOffset),
    backgroundColor(source.backgroundColor)
{
    text.reset(new TTextArea(source.text, TCoordinate(0.f, 0.f), this));
    text->SetFont(source.font);
    text->SetColor(source.textColor);
}

void TSimpleText::_draw(TRenderTarget& target) {
    if (text->GetText().empty() == true) {
        return;
    }

    if (needsRedraw == true) {
        TRenderTarget& localTarget = renderImage.getRenderTarget();
        localTarget.clear(_currentBackgroundColor());
        if (0.f < borderSize) {
            const TColor& originalTextColor = text->GetColor();
            text->SetColor(_currentBorderColor());
            text->Draw(localTarget, borderOffset - TCoordinate(borderSize, borderSize));
            text->SetColor(originalTextColor);
        }

        const TColor originalTextColor = text->GetColor();
        TColor color = originalTextColor;
        color.a = (uchar) (color.a * colorModifier.aMod);
        text->SetColor(color);
        text->Draw(localTarget);
        text->SetColor(originalTextColor);

        renderImage.createDrawingObject();
        needsRedraw = false;
    }

    const TCoordinate position = std::move(GetScreenPosition());
    renderImage.getDrawingObject().setPosition(position.x, position.y);
    target.draw(renderImage.getDrawingObject());
}

void TSimpleText::_update() {
    /*none*/
}

TColor TSimpleText::_currentBorderColor() const {
    return colorModifier.modify(borderColor);
}

TColor TSimpleText::_currentBackgroundColor() const {
    return colorModifier.modify(backgroundColor);
}

std::list<TWidget::Signal> TSimpleText::_enumSignals() const {
    auto signals = parent_type::_enumSignals();

    signals.emplace_back(DefaultSignalID::ObjectTextChanged);

    return signals;
}

const TextString& TSimpleText::GetText() const {
    return text->GetText();
}

void TSimpleText::SetText(const TextString& value) {
    if (text->GetText() != value) {
        text->SetText(value);
        _OnTextChanged();
        GetSignal(DefaultSignalID::ObjectTextChanged).Send();
    }
}

const TFont& TSimpleText::GetFont() const {
    return text->GetFont();
}

void TSimpleText::SetFont(const TFont& value) {
    if (text->GetFont() != value) {
        text->SetFont(value);
        _OnImageChanged();
    }
}


void TSimpleText::SetBorderSize(float value) {
    if (borderSize != value) {
        borderSize = value;
        _OnResized();
    }
}

float TSimpleText::GetBorderSize() const {
    return borderSize;
}

void TSimpleText::SetBorderColor(const TColor& value) {
    if (borderColor != value) {
        borderColor = value;
        _OnImageChanged();
    }
}

const TColor& TSimpleText::GetBorderColor() const {
    return borderColor;
}

void TSimpleText::SetBorderOffset(const TCoordinate& value) {
    if (borderOffset != value) {
        borderOffset = value;
        _OnResized();
    }
}

const TCoordinate& TSimpleText::GetBorderOffset() const {
    return borderOffset;
}

const TColor& TSimpleText::GetBackgroundColor() const {
    return backgroundColor;
}

void TSimpleText::SetBackgroundColor(const TColor& value) {
    if (backgroundColor != value) {
        backgroundColor = value;
        _OnImageChanged();
    }
}

void TSimpleText::_OnTextChanged() { needsRedraw = true; }
void TSimpleText::_OnImageChanged() { needsRedraw = true; }

END_GUI
