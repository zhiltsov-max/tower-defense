#ifndef SIMPLETEXT_H
#define SIMPLETEXT_H

#include "abstracttextbox.h"
#include "abstracttextarea.h"

BEGIN_GUI

struct TSimpleTextSource : TMenuObjectSource
{
    TextString text;
    TColor textColor;
    TFont font;

    float borderSize;
    TColor borderColor;
    TCoordinate borderOffset;

    TColor backgroundColor;
};

class TSimpleText : public TMenuObject
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
    void SetBackgroundColor(const TColor &value);
private:
    typedef TMenuObject parent_t;
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

    TColor _currentBorderColor() const;
    TColor _currentBackgroundColor() const;

    virtual void _OnTextChanged();
    virtual void _OnImageChanged();
};

END_GUI

#endif // SIMPLETEXT_H
