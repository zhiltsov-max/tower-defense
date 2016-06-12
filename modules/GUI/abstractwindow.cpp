#include "abstractwindow.h"



BEGIN_GUI


TAbstractWindow::TAbstractWindow(const TAbstractWindowSource& source) :
    parent_type(source),
    allowMoving(source.allowMoving),
    headerHeight(source.headerHeight),
    headerColor(source.headerColor),
    color(source.color),
    colorModifier(),
    image(source.image),
    innerElementsPadding(source.innerElementsPadding),
    minSize(source.minSize),
    maxSize(source.maxSize),
    clickPosition(),
    clicked(false)
{
    if (source.enabled == true) {
        state = State::Normal;
    } else {
        state = State::Disabled;
    }

    if (HasHeader() == true) {
        headerText.reset(new TTextArea(source.headerText, this));
    }
}


bool TAbstractWindow::IsEnabled() const {
    return (state != State::Disabled);
}

void TAbstractWindow::SetEnabled(bool value) {
    if (IsEnabled() != value) {
        if (value == true) {
            state = State::Normal;
            _OnEnabled();
        } else {
            state = State::Disabled;
            _OnDisabled();
        }
    }
}

TAbstractWindow::State TAbstractWindow::_getState() const {
    return state;
}

void TAbstractWindow::Enable() {
    SetEnabled(true);
}

void TAbstractWindow::Disable() {
    SetEnabled(false);
}


bool TAbstractWindow::IsMoveable() const {
    return allowMoving;
}

void TAbstractWindow::SetMoveability(bool value) {
    if (value != allowMoving) {
        allowMoving = value;
        _OnMoveabilityChanged();
    }
}


bool TAbstractWindow::HasHeader() const {
    return (0.f < headerHeight);
}

float TAbstractWindow::GetHeaderHeight() const {
    return headerHeight;
}

void TAbstractWindow::SetHeaderHeight(float value) {
    if (value != headerHeight) {
        headerHeight = value;
        _OnHeaderChanged();
    }
}

const TextString& TAbstractWindow::GetTitle() const {
    return headerText->GetText();
}

void TAbstractWindow::SetTitle(const TextString& value) {
    headerText->SetText(value);
    _OnHeaderChanged();
}

const TFont& TAbstractWindow::GetTitleFont() const {
    return headerText->GetFont();
}

void TAbstractWindow::SetTitleFont(const TFont& value) {
    if (value != headerText->GetFont()) {
        headerText->SetFont(value);
        _OnHeaderChanged();
    }
}

const TColor& TAbstractWindow::GetTitleColor() const {
    return headerText->GetColor();
}

void TAbstractWindow::SetTitleColor(const TColor& value) {
    if (value != headerText->GetColor()) {
        headerText->SetColor(value);
        _OnHeaderChanged();
    }
}

const TColor& TAbstractWindow::GetHeaderColor() const {
    return headerColor;
}

void TAbstractWindow::SetHeaderColor(const TColor& value) {
    if (headerColor != value) {
        headerColor = value;
        _OnHeaderChanged();
    }
}


const TColor& TAbstractWindow::GetColor() const {
    return color;
}

void TAbstractWindow::SetColor(const TColor& value) {
    if (color != value) {
        color = value;
        _OnImageChanged();
    }
}

bool TAbstractWindow::HasImage() const {
    return (image.image != nullptr);
}

const TAbstractWindow::Image& TAbstractWindow::GetImage() const {
    return image;
}

void TAbstractWindow::SetImage(Image&& value) {
    if (image.image.get() != value.image.get()) {
        image = std::move(value);
        _OnImageChanged();
    }
}


const TPadding& TAbstractWindow::GetInnerPadding() const {
    return innerElementsPadding;
}

void TAbstractWindow::SetInnerPadding(const TPadding& value) {
    if (innerElementsPadding != value) {
        innerElementsPadding = value;
        _OnImageChanged();
    }
}

bool TAbstractWindow::IsResizable() const {
    return ((maxSize != TSize()) && (minSize == maxSize)) == false;
}

void TAbstractWindow::SetMinSize(const TSize& value) {
    if (minSize != value) {
        minSize.x = std::min(value.x, maxSize.x);
        minSize.y = std::min(value.y, maxSize.y);
        if (size < minSize) {
            SetSize(minSize);
        }
    }
}

void TAbstractWindow::SetMaxSize(const TSize& value) {
    if (maxSize != value) {
        maxSize.x = std::max(minSize.x, value.x);
        maxSize.y = std::max(minSize.y, value.y);
        if (size < maxSize) {
            SetSize(maxSize);
        }
    }
}

const TSize& TAbstractWindow::GetMinSize() const {
    return minSize;
}

const TSize& TAbstractWindow::GetMaxSize() const {
    return maxSize;
}

void TAbstractWindow::SetSize(const TSize& value) {
    if ((IsResizable() == true) &&
       ((maxSize != TSize()) && (value <= maxSize) && (minSize <= value)))
    {
        parent_type::SetSize(value);
    }
}

TPadding TAbstractWindow::GetInnerBorder() const {
    return innerElementsPadding;
}

TColor TAbstractWindow::_currentColor() const {
    return colorModifier.modify(color);
}

TColor TAbstractWindow::_currentHeaderColor() const {
    return colorModifier.modify(headerColor);
}

void TAbstractWindow::_update() {
    if (IsEnabled() == false) {
        return;
    }
    parent_type::_update();
}

void TAbstractWindow::_updateChildren() {
    if (IsEnabled() == false) {
        return;
    }
    parent_type::_updateChildren();
}


bool TAbstractWindow::_isMouseOverHeader() const {
    if (HasHeader() == false) {
        return false;
    }

    const TCoordinate position = GetScreenPosition();
    return IO::IsCursorInRect(position.x, position.y,
        position.x + size.x, position.y + headerHeight);
}

void TAbstractWindow::_draw(TRenderTarget& target) {
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

        if (HasHeader() == true) {
            sf::RectangleShape headerRect( sf::Vector2f(size.x, headerHeight) );
            headerRect.setFillColor(_currentHeaderColor());
            localTarget.draw(headerRect);
        }

        if (headerText->GetText().empty() == false) {
            headerText->Draw(localTarget);
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
        boundingRect.setFillColor(sf::Color(0, 0, 0, 0));
        boundingRect.setOutlineColor(sf::Color(0, 255 - 55 * mouseOver, 0, 128));
        boundingRect.setOutlineThickness(2.f);
        boundingRect.setPosition(position.x, position.y);
        target.draw(boundingRect);

        sf::Text rectText = TFont().CreateText(String::toWide(name));
        rectText.setPosition(position.x, position.y);
        target.draw(rectText);
    }
#endif // _DEBUG
}

void TAbstractWindow::_handle_mouseButtonPressed(
    const TEvent_MouseClick& event, bool& consume
) {
    if ((IsMoveable() == true) && (_isMouseOverHeader() == true)) {
        clickPosition.x = event.x - GetScreenPosition().x;
        clickPosition.y = event.y - GetScreenPosition().y;
        state = State::Moving;
    }

    consume = false;
}

void TAbstractWindow::_handle_mouseButtonReleased(
    const TEvent_MouseClick& event, bool& consume
) {
    if ((IsMoveable() == true) && (state == State::Moving)) {
        SetPosition(event.x - clickPosition.x,
                    event.y - clickPosition.y);
        state = State::Normal;
    }

    consume = false;
}

void TAbstractWindow::_handle_mouseMove(
    const TEvent_MouseMoved& event, bool& consume
) {
    if ((IsMoveable() == true) && (state == State::Moving)) {
        SetPosition(event.x - clickPosition.x,
                    event.y - clickPosition.y);
    }

    consume = false;
}

void TAbstractWindow::_OnMoveabilityChanged() { /*none*/ }
void TAbstractWindow::_OnEnabled() { needsRedraw = true; }
void TAbstractWindow::_OnDisabled() { needsRedraw = true; }
void TAbstractWindow::_OnHeaderChanged() { needsRedraw = true; }
void TAbstractWindow::_OnImageChanged() { needsRedraw = true; }


END_GUI
