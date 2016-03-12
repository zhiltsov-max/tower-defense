#ifndef ABSTRACT_TEXT_AREA_H
#define ABSTRACT_TEXT_AREA_H

#include "widget.h"



BEGIN_GUI


struct TAbstractTextAreaSource;

enum class DefaultMessageColor : uint {
    exclamation = 0xffff0000,
    information = 0xffffd700
};

class TAbstractTextArea /*Abstract*/
{
public:
    using Parent = TWidget *;


    ~TAbstractTextArea() = default;

    virtual const Parent& GetParent() const;
    virtual void SetParent(const Parent& value);

    virtual const TCoordinate& GetPosition() const;
    virtual TCoordinate GetScreenPosition() const;
    virtual void SetPosition(TCoordinate value);
    virtual void SetPosition(float x, float y);

    virtual float GetWidth() const;
    virtual float GetHeight() const;
    virtual TSize GetSize() const;

    virtual void SetText(const TextString& value) ;
    virtual const TextString& GetText() const;

    virtual void SetColor(const TColor& value);
    virtual const TColor& GetColor() const;

    virtual void SetFont(const TFont& value);
    virtual const TFont& GetFont() const;

    virtual void Draw(TRenderTarget& target,
        const TCoordinate& offset = TCoordinate());

protected:
    Parent parent;

    TCoordinate position;

    TextString text;
    TColor color;

    TFont font;


    TAbstractTextArea(const TAbstractTextAreaSource& source, const Parent& parent);
    TAbstractTextArea(const TAbstractTextArea& other) = default;
    TAbstractTextArea& operator=(const TAbstractTextArea& other) = default;

    virtual bool _parentExists() const;
    virtual void _checkBorders();
};


struct TAbstractTextAreaSource {
    TCoordinate position;
    TextString text;
    TColor color;
    TFont font;
};


END_GUI

#endif // ABSTRACT_TEXT_AREA_H
