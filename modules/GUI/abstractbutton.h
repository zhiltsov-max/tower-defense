#ifndef ABSTRACT_BUTTON_H
#define ABSTRACT_BUTTON_H

#include "textarea.h"



BEGIN_GUI


struct TAbstractButtonSource : TWidgetSource {
    bool enabled;
    TTextAreaSource textArea;
    TColor color;
    TImageSource image;
};

class TAbstractButton : public TWidget /*Abstract*/
{
public:
    typedef TImageContainer Image;


    ~TAbstractButton() = default;

    virtual bool IsEnabled() const;
    virtual void Enable();
    virtual void Disable();

    virtual const TColor& GetColor() const;
    virtual void SetColor(const TColor& value);

    virtual bool HasImage() const;
    virtual const Image& GetImage() const;
    virtual void SetImage(Image&& value);

    virtual const TextString& GetText() const;
    virtual void SetText(const TextString& value);

    virtual const TFont& GetFont() const;
    virtual void SetFont(const TFont& value);

    virtual const TColor& GetFontColor() const;
    virtual void SetFontColor(const TColor& value);

private:
    typedef TWidget parent_type;

protected:
    enum class State : uchar {
        _min = 0,

        undefined = 0,
        Normal,
        Hover,
        Pressed,
        Disabled,

        _max = Disabled
    };
    State state;

    TColor color;
    TColorModifier colorModifier;

    Image image;

    TTextArea textArea;


    TAbstractButton(const TAbstractButtonSource& source);
    TAbstractButton(TAbstractButton&& other);

    virtual State _getState() const;
    virtual void SetState(State value);

    virtual std::list<Signal> _enumSignals() const override;
    virtual std::list<Slot> _enumSlots() const override;

    virtual void _OnEnabled();
    virtual void _OnDisabled();
    virtual void _OnTextChanged();
    virtual void _OnImageChanged();

    virtual void _updateMouse() override;
    virtual TColor _currentColor() const;
};


END_GUI

#endif // ABSTRACT_BUTTON_H
