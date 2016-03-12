#include "abstractbutton.h"



BEGIN_GUI


TAbstractButton::TAbstractButton(const TAbstractButtonSource& source) :
    parent_type(source),
    color(source.color),
    image(source.image),
    textArea(source.textArea, this)
{
    if (source.enabled == true) {
        state = State::Normal;
    } else {
        state = State::Disabled;
    }
}

TAbstractButton::TAbstractButton(TAbstractButton&& other) :
    parent_type(std::move(other)),
    state(other.state),
    color(other.color),
    colorModifier(std::move(other.colorModifier)),
    image(std::move(other.image)),
    textArea(std::move(other.textArea))
{
    textArea.SetParent(this);
}


TAbstractButton::State TAbstractButton::_getState() const {
    return state;
}

void TAbstractButton::SetState(State value) {
    if (state != value) {
        if (value == State::Disabled) {
            _OnDisabled();
            GetSignal(DefaultSignalID::ObjectDisabled).Send();
        } else if (state == State::Normal) {
            _OnEnabled();
            GetSignal(DefaultSignalID::ObjectEnabled).Send();
        } else {
            /*none*/
        }

        state = value;
    }
}

bool TAbstractButton::IsEnabled() const {
    return state != State::Disabled;
}

void TAbstractButton::Enable() {
    SetState(State::Normal);
}
void TAbstractButton::Disable() {
    SetState(State::Disabled);
}


const TColor& TAbstractButton::GetColor() const {
    return color;
}

void TAbstractButton::SetColor(const TColor& value) {
    if (color != value) {
        color = value;
        _OnImageChanged();
    }
}

bool TAbstractButton::HasImage() const {
    return image.image != nullptr;
}

const TAbstractButton::Image& TAbstractButton::GetImage() const {
    return image;
}

void TAbstractButton::SetImage(Image&& value) {
    if (image != value) {
        image = std::move(value);
        _OnImageChanged();
    }
}


const TextString& TAbstractButton::GetText() const {
    return textArea.GetText();
}

void TAbstractButton::SetText(const TextString& value) {
    textArea.SetText(value);
    _OnTextChanged();
    GetSignal(DefaultSignalID::ObjectTextChanged).Send();
}

const TFont& TAbstractButton::GetFont() const {
    return textArea.GetFont();
}

void TAbstractButton::SetFont(const TFont& value) {
    if (value != textArea.GetFont()) {
        textArea.SetFont(value);
        _OnImageChanged();
    }
}

const TColor& TAbstractButton::GetFontColor() const {
    return textArea.GetColor();
}

void TAbstractButton::SetFontColor(const TColor& value) {
    if (textArea.GetColor() != value) {
        textArea.SetColor(value);
        _OnImageChanged();
    }
}

std::list<TAbstractButton::Signal> TAbstractButton::_enumSignals() const {
    std::list<Signal> signals = std::move(parent_type::_enumSignals());

    signals.emplace_back(DefaultSignalID::ObjectEnabled);
    signals.emplace_back(DefaultSignalID::ObjectDisabled);
    signals.emplace_back(DefaultSignalID::ObjectTextChanged);

    return signals;
}

std::list<TAbstractButton::Slot> TAbstractButton::_enumSlots() const {
    std::list<Slot> slots = std::move(parent_type::_enumSlots());
    return slots;
}

void TAbstractButton::_OnEnabled() { /*none*/ }
void TAbstractButton::_OnDisabled() { /*none*/ }
void TAbstractButton::_OnTextChanged() { needsRedraw = true; }
void TAbstractButton::_OnImageChanged() { needsRedraw = true; }

void TAbstractButton::_updateMouse() {
    if (IsEnabled() == false) {
        return;
    }
    parent_type::_updateMouse();
}

TColor TAbstractButton::_currentColor() const {
    return colorModifier.modify(color);
}


END_GUI
