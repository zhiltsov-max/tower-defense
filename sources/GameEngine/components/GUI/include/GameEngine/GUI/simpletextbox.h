#ifndef SIMPLE_TEXT_BOX_H
#define SIMPLE_TEXT_BOX_H

#include "abstracttextbox.h"
#include "textarea.h"



BEGIN_GUI


struct TSimpleTextBoxSource : TAbstractTextBoxSource {
    TTextAreaSource textArea;
};

class TSimpleTextBox : public TAbstractTextBox
{
public:
    TSimpleTextBox(const TSimpleTextBoxSource& source);
    TSimpleTextBox(const TSimpleTextBox& other) = delete;
    TSimpleTextBox& operator=(const TSimpleTextBox& other) = delete;
    ~TSimpleTextBox() = default;
private:
    typedef TAbstractTextBox parent_type;
};


END_GUI

#endif // SIMPLE_TEXT_BOX_H
