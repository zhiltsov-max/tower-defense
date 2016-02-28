#ifndef ABSTRACTTEXTBOX_H
#define ABSTRACTTEXTBOX_H

#include "gui_main.h"
#include "widget.h"
#include "abstracttextarea.h"

BEGIN_GUI

struct TAbstractTextBoxSource : TWidgetSource
{
    //Main
    TextString text;
    TColor textColor;
    TCoordinate textPosition;
    TFont font;
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
    TAbstractTextBox(const TAbstractTextBoxSource& source);
    TAbstractTextBox(const TAbstractTextBox& other) = delete;
    TAbstractTextBox& operator=(const TAbstractTextBox& other) = delete;
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
    virtual void SetFont(const TFont &value);
private:
    typedef TWidget parent_type;
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

    /*
        Returns a list of signals that have to be created.
    */
    virtual std::list<Signal> _enumSignals() const override;
    /*
        Returns a list of slots that have to be created.
    */
    virtual std::list<Slot> _enumSlots() const override;

    virtual void _draw(TRenderTarget& target) override;
    TColor _currentColor() const;
    TColor _currentBorderColor() const;

    virtual void _OnAllowingEdit();
    virtual void _OnDisallowingEdit();
    virtual void _OnTextChanged();
    virtual void _OnColorChanged();
};

END_GUI

#endif // ABSTRACTTEXTBOX_H
