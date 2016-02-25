#include "richtextbox.h"

BEGIN_GUI

TRichTextBoxSource::TRichTextBoxSource() :
    separators(TRichTextBox::DEFAULT_SEPARATORS())
{}

TRichTextBox::TRichTextBox(const TRichTextBoxSource& source) :
    parent_t(source)
{
    text.reset(new TRichTextArea(source.text, source.textPosition, this));
    text->SetFont(source.font);
    text->SetColor(source.textColor);
    static_cast<TRichTextArea*>(text.get())->SetSeparators(source.separators.cbegin(), source.separators.cend());
    static_cast<TRichTextArea*>(text.get())->SetMaxSize(source.maxSize);
}


const std::initializer_list<TextString> TRichTextBox::DEFAULT_SEPARATORS() {
    return {TEXT("\n"), TEXT("\r")};
}

void TRichTextBox::SetMaxSize(const TSize& value) {
    parent_t::SetMaxSize(value);
    static_cast<TRichTextArea*>(text.get())->SetMaxSize(value);
}

END_GUI
