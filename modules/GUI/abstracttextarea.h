#ifndef ABSTRACTTEXTAREA_H
#define ABSTRACTTEXTAREA_H

#include "menuobject.h"

BEGIN_GUI

enum class DefaultMessageColor : uint {
    exclamation = 0xffff0000,
    information = 0xffffd700
};

class TAbstractTextArea /*Abstract*/
{
public:
    typedef TMenuObject* Parent;

    TAbstractTextArea(const TextString& text_ = TextString(), const TCoordinate& position_ = TCoordinate(), const Parent& parent_ = Parent(nullptr));
    TAbstractTextArea(const TAbstractTextArea& other) = default;
    TAbstractTextArea& operator=(const TAbstractTextArea& other) = default;
    ~TAbstractTextArea() = default;

    virtual const Parent& GetParent() const;
    virtual void SetParent(const Parent& value);

    virtual const TCoordinate& GetPosition() const;
    virtual TCoordinate GetScreenPosition() const;
    virtual void SetPosition(TCoordinate value);
    virtual void SetPosition(float x, float y);

    /*
        Returns full width with margin.
    */
    virtual float GetWidth() const;
    /*
        Returns full height with margin.
    */
    virtual float GetHeight() const;
    /*
        Return full fize with margin.
    */
    virtual TSize GetSize() const;

    virtual const TPadding& GetMargin() const;
    virtual void SetMargin(const TPadding& value);

    virtual void SetText(const TextString& value) ;
    virtual const TextString& GetText() const;

    virtual void SetColor(const TColor& value);
    virtual const TColor& GetColor() const;

    virtual void SetFont(const TFont& value);
    virtual const TFont& GetFont() const;

    virtual void Draw(TRenderTarget& target, const TCoordinate& position = TCoordinate());
protected:
    Parent parent;

    TCoordinate position;
    TPadding margin;

    TextString text;
    TColor color;

    TFont font;

    bool _parentExists() const;
    virtual void _checkBorders();
};

END_GUI

#endif // ABSTRACTTEXTAREA_H
