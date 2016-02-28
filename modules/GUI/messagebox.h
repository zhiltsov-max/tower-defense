#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include "window.h"
#include "pushbutton.h"
#include "richtextbox.h"

BEGIN_GUI

struct TMessageBoxSource : TWindowSource
{
    uchar style;
    TPushButtonSource buttonsSource;
    TRichTextBoxSource textBoxSource;
};

class TMessageBox : public TWindow
{
public:
    enum class Style : uchar {
        undefined = 0,
        OkDialog = 1,
        YesNoDialog = 2,
        YesNoCancelDialog = 3,
        UserDefined = 4
    };

    TMessageBox(const TMessageBoxSource& source);
    void Initialize(const TMessageBoxSource& source);

    virtual Style GetStyle() const;

    virtual const TRichTextBox& GetTextBox() const;
    virtual void SetText(const TextString& value);
    virtual const TextString& GetText() const;
private:
    typedef TWindow parent_type;
protected:
    virtual std::list<Signal> _enumSignals() const override;

    virtual TRichTextBox& GetTextBox();

    virtual void _OnTextChanged();
};

END_GUI

#endif // MESSAGEBOX_H
