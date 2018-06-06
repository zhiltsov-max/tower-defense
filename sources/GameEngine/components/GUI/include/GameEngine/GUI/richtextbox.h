#ifndef RICH_TEXT_BOX_H
#define RICH_TEXT_BOX_H

#include "gui_main.h"
#include "abstracttextbox.h"
#include "richtextarea.h"



BEGIN_GUI


struct TRichTextBoxSource;

class TRichTextBox : public TAbstractTextBox
{
public:
    static const std::initializer_list<TextString> DEFAULT_SEPARATORS();


    TRichTextBox(const TRichTextBoxSource& source);
    ~TRichTextBox() = default;

    virtual void SetMaxSize(const TSize& value) override;

private:
    typedef TAbstractTextBox parent_type;

    TRichTextArea& _textArea();
};


struct TRichTextBoxSource : TAbstractTextBoxSource {
    typedef TRichTextArea::Separators Separators;
    Separators separators;
    TRichTextAreaSource textArea;

    TRichTextBoxSource();
};


END_GUI

#endif // RICH_TEXT_BOX_H
