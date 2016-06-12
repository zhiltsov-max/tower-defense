#ifndef ABSTRACT_TEXT_BOX_H
#define ABSTRACT_TEXT_BOX_H

#include "abstracttextarea.h"



BEGIN_GUI

struct TAbstractTextBoxSource : TWidgetSource
{
    //Color
    TColor color;
    //Size
    TSize maxSize;
    TSize minSize;
    //Flags
    bool allowEdit;
    //Border
    float borderSize;
    TColor borderColor;
};

class TAbstractTextBox : public TWidget /*Abstract*/
{
public:
    ~TAbstractTextBox() = default;

    virtual const TextString& GetText() const;
    virtual void SetText(const TextString& value);

    virtual const TColor& GetColor() const;
    virtual void SetColor(const TColor& value);

    virtual bool IsResizable() const;
    virtual void SetMinSize(const TSize& value);
    virtual void SetMaxSize(const TSize& value);
    virtual const TSize& GetMinSize() const;
    virtual const TSize& GetMaxSize() const;
    virtual void SetSize(const TSize& value) override;

    virtual bool IsEditable() const;
    virtual void SetEditable(bool value);

    virtual float GetBorderSize() const;
    virtual void SetBorderSize(float value);

    virtual const TFont& GetFont() const;
    virtual void SetFont(const TFont& value);

private:
    typedef TWidget parent_type;


    TColor _currentColor() const;
    TColor _currentBorderColor() const;

protected:
    //Main
    typedef std::unique_ptr<TAbstractTextArea> Text;
    Text text;
    //Color
    TColor color;
    TColorModifier colorModifier;
    //Size
    TSize maxSize;
    TSize minSize;
    //Flags
    bool allowEdit;
    //Border
    float borderSize;
    TColor borderColor;


    TAbstractTextBox(const TAbstractTextBoxSource& source);
    TAbstractTextBox(const TAbstractTextBox& other) = delete;
    TAbstractTextBox& operator=(const TAbstractTextBox& other) = delete;

    /*
        Returns a list of signals that have to be created.
    */
    virtual list<Signal> _enumSignals() const override;

    virtual void _draw(TRenderTarget& target) override;

    virtual void _OnAllowingEdit();
    virtual void _OnDisallowingEdit();
    virtual void _OnTextChanged();
    virtual void _OnColorChanged();
};


END_GUI

#endif // ABSTRACT_TEXT_BOX_H
