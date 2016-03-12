#include "simpletextbox.h"



BEGIN_GUI


TSimpleTextBox::TSimpleTextBox(const TSimpleTextBoxSource& source) :
    parent_type(source)
{
    text.reset(new TTextArea(source.textArea, this));
}


END_GUI
