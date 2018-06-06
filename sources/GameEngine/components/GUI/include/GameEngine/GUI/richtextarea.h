#ifndef RICH_TEXT_AREA_H
#define RICH_TEXT_AREA_H

#include "abstracttextarea.h"



BEGIN_GUI

struct TRichTextAreaSource;

class TRichTextArea : public TAbstractTextArea
{
public:
    typedef std::vector<TextString> Separators;


    TRichTextArea(const TRichTextAreaSource& source, const Parent& parent);

    virtual void SetSeparators(const Separators& value);
    virtual const Separators& GetSeparators() const;

    virtual void SetLineSpacing(float value);
    virtual float GetLineSpacing() const;

    /*
        Set maximum size.
        Values <= 0 is equivalent to unlimited size.
    */
    virtual void SetMaxSize(const TSize& value);
    virtual const TSize& GetMaxSize() const;

    virtual void SetText(const TextString& value) override;

    virtual void SetFont(const TFont& value) override;

    virtual void Draw(TRenderTarget& target,
        const TCoordinate& offset = TCoordinate()) override;

private:
    typedef TAbstractTextArea parent_type;

protected:
    static constexpr float DEFAULT_LINE_HEIGHT = 20.f;


    typedef std::vector<TextString> Lines;
    Lines lines;
    float lineSpacing;

    Separators separators;
    TSize maxSize;


    virtual void _splitTextByLines();
    virtual void _update();
};


struct TRichTextAreaSource : TAbstractTextAreaSource {
    static constexpr float DEFAULT_SPACING_BETWEEN_LINES = 5.f;


    TRichTextArea::Separators separators;
    float lineSpacing = DEFAULT_SPACING_BETWEEN_LINES;
    TSize maxSize;
};


END_GUI

#endif // RICH_TEXT_AREA_H
