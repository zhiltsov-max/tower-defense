#ifndef CUSTOMFONT_H
#define CUSTOMFONT_H

#include "Core\core.h"



namespace GUI {


class TCustomFont
{
public:
    using Size = uchar;
    enum class Style {
        Regular = 0,
        Bold = 1,
        Italic = 2,
        Underlined = 4,
        Strikethrough = 8
    };

private:
    static const Style DEFAULT_FLAGS;
    static const Size  DEFAULT_SIZE;
    static const string DEFAULT_NAME;

public:
    TCustomFont(const string& filePath = DEFAULT_NAME,
        const Size& size = DEFAULT_SIZE,
        const Style& style = DEFAULT_FLAGS
    );

    bool operator==(const TCustomFont& other) const;
    bool operator!=(const TCustomFont& other) const;

    const string& GetName() const;
    const Size& GetSize() const;
    const Style& GetStyle() const;

    Graphics::TText CreateText(const TextString& text) const;
    Graphics::TText CreateText(TextString&& text) const;

    static float GetTextWidth(const TextString& text, const TCustomFont& font);
    static float GetTextHeight(const TextString& text, const TCustomFont& font);
    float GetTextWidth(const TextString& text) const;
    float GetTextHeight(const TextString& text) const;

private:
    Style flags;
    string filePath;
    Size size;

    typedef const Graphics::TFont* Font;
    Font font;

    const Graphics::TFont& getFont() const;
};


typedef Graphics::TText TText;


} // namespace GUI

#endif // CUSTOMFONT_H
