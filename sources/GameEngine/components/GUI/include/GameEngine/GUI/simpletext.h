#ifndef SIMPLE_TEXT_H
#define SIMPLE_TEXT_H

#include "abstracttextbox.h"
#include "abstracttextarea.h"



BEGIN_GUI


struct TSimpleTextSource : TWidgetSource
{
    TextString text;
    TColor textColor;
    TFont font;

    float borderSize;
    TColor borderColor;
    TCoordinate borderOffset;

    TColor backgroundColor;
};

class TSimpleText : public TWidget
{
public:
    TSimpleText(const TSimpleTextSource& source);
    TSimpleText(const TSimpleText& other) = delete;
    TSimpleText& operator=(const TSimpleText& other) = delete;
    ~TSimpleText() = default;

    const TextString& GetText() const;
    void SetText(const TextString& value);

    const TFont& GetFont() const;
    void SetFont(const TFont& value);

    void SetBorderSize(float value);
    float GetBorderSize() const;
    void SetBorderColor(const TColor& value);
    const TColor& GetBorderColor() const;
    void SetBorderOffset(const TCoordinate& value);
    const TCoordinate& GetBorderOffset() const;

    const TColor& GetBackgroundColor() const;
    void SetBackgroundColor(const TColor& value);

private:
    typedef TWidget parent_type;

protected:
    //Main
    typedef std::unique_ptr<TAbstractTextArea> Text;
    Text text;
    //Color
    TColor backgroundColor;
    TColorModifier colorModifier;
    //Border
    float borderSize;
    TColor borderColor;
    TCoordinate borderOffset;


    std::list<Signal> _enumSignals() const;

    void _draw(TRenderTarget& target);
    void _update();

    virtual TColor _currentBorderColor() const;
    virtual TColor _currentBackgroundColor() const;

    virtual void _OnTextChanged();
    virtual void _OnImageChanged();
};


END_GUI

#endif // SIMPLE_TEXT_H
