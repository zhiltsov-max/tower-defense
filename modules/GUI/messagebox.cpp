#include "messagebox.h"

BEGIN_GUI

TMessageBox::TMessageBox(const TMessageBoxSource& source) :
    parent_type(source)
{}

void TMessageBox::Initialize(const TMessageBoxSource& source) {
    TRichTextBoxSource textBoxSource = source.textBoxSource;
    textBoxSource.name = "Text";
    AddChild(TWidgetRef(new TRichTextBox(textBoxSource)));
}

TMessageBox::Style TMessageBox::GetStyle() const {
    return Style::UserDefined;
}

const TRichTextBox& TMessageBox::GetTextBox() const {
    return *FindChild<TRichTextBox>("Text").lock();
}

void TMessageBox::SetText(const TextString& value) {
    GetTextBox().SetText(value);\
    _OnTextChanged();
    GetSignal(DefaultSignalID::ObjectTextChanged).Send();
}

const TextString& TMessageBox::GetText() const {
    return GetTextBox().GetText();
}

std::list<TWidget::Signal> TMessageBox::_enumSignals() const {
    std::list<Signal> signals = parent_type::_enumSignals();

    signals.emplace_back(DefaultSignalID::ObjectTextChanged);

    return signals;
}

TRichTextBox& TMessageBox::GetTextBox() {
    return *FindChild<TRichTextBox>("Text").lock();
}

void TMessageBox::_OnTextChanged() { needsRedraw = true; }

END_GUI
