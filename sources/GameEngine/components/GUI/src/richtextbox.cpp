#include "richtextbox.h"



BEGIN_GUI


const std::initializer_list<TextString>
TRichTextBox::DEFAULT_SEPARATORS() {
    return {TEXT("\n"), TEXT("\r")};
}

TRichTextBoxSource::TRichTextBoxSource() :
    separators(TRichTextBox::DEFAULT_SEPARATORS())
{}

TRichTextBox::TRichTextBox(const TRichTextBoxSource& source_) :
    parent_type(source_)
{
    auto source = source_;
    source.textArea.maxSize.x = std::min(
        source.textArea.maxSize.x, source.maxSize.x);
    source.textArea.maxSize.y = std::min(
        source.textArea.maxSize.y, source.maxSize.y);
    text.reset(new TRichTextArea(source.textArea, this));
}

void TRichTextBox::SetMaxSize(const TSize& value) {
    parent_type::SetMaxSize(value);
    _textArea().SetMaxSize(value);
}

TRichTextArea& TRichTextBox::_textArea() {
    return *static_cast<TRichTextArea*>(text.get());
}


END_GUI
