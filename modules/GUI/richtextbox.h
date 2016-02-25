#ifndef RICHTEXTBOX_H
#define RICHTEXTBOX_H

#include "gui_main.h"
#include "abstracttextbox.h"
#include "richtextarea.h"

BEGIN_GUI

struct TRichTextBoxSource : TAbstractTextBoxSource
{
    typedef TRichTextArea::Separators Separators;
    Separators separators;

    TRichTextBoxSource();
};

class TRichTextBox : public TAbstractTextBox
{
public:
    TRichTextBox(const TRichTextBoxSource& source);
    TRichTextBox(const TRichTextBox& other) = delete;
    TRichTextBox& operator=(const TRichTextBox& other) = delete;
    ~TRichTextBox() = default;

    static const std::initializer_list<TextString> DEFAULT_SEPARATORS();

    virtual void SetMaxSize(const TSize& value) override;
private:
    typedef TAbstractTextBox parent_t;
};

END_GUI

#endif // RICHTEXTBOX_H
