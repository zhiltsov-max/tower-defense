#include "simpletextbox.h"
#include "textarea.h"

BEGIN_GUI

TSimpleTextBox::TSimpleTextBox(const TSimpleTextBoxSource& source) :
    parent_type(source)
{
    text.reset(new TTextArea(source.text, source.textPosition, this));
    text->SetFont(source.font);
    text->SetColor(source.textColor);
}

void TSimpleTextBox::SetEditable(bool value) {
    UNUSED(value)
}

END_GUI
