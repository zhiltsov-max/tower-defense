#ifndef RICHTEXTAREA_H
#define RICHTEXTAREA_H

#include "abstracttextarea.h"

BEGIN_GUI

class TRichTextArea : public TAbstractTextArea
{
public:
    typedef std::vector<TextString> Separators;

    TRichTextArea(const TextString& text, const TCoordinate& position, TMenuObject* parent);

    template< class InpIt >
    void SetSeparators(InpIt begin_, InpIt end_);

    const Separators& GetSeparators() const;

    void SetSpacingBetweenLines(float value);
    float GetSpacingBetweenLines() const;


    void SetMaxSize(const TSize& value);
    const TSize& GetMaxSize() const;
    /*
        Returns full width with margin.
    */
    float GetWidth() const;
    /*
        Returns full height with margin.
    */
    float GetHeight() const;

    void SetText(const TextString& value);

    void SetFont(const TFont& value);

    void Draw(TRenderTarget& target, const TCoordinate& position = TCoordinate());
private:
    typedef TAbstractTextArea parent_t;
protected:
    static constexpr float DEFAULT_LINE_HEIGHT = 20.f;
    static constexpr float DEFAULT_SPACING_BETWEEN_LINES = 5.f;

    float spacingBetweenLines;

    typedef std::vector<TextString> Lines;
    Lines lines;

    Separators separators;
    TSize maxSize;

    Lines _splitStringBySeparators(const TextString& text, const Separators& separators) const;
    Lines _splitStringByLength(const TextString& text, size_t length) const;
    void _splitTextByLines();

    void _update();
};

template< class InpIt >
void TRichTextArea::SetSeparators(InpIt begin_, InpIt end_) {
    separators = Separators(begin_, end_);
    _update();
}

END_GUI

#endif // RICHTEXTAREA_H
