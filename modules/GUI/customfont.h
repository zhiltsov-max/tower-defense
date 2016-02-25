#ifndef CUSTOMFONT_H
#define CUSTOMFONT_H

#include "Core\core.h"

class TCustomFont
{
public:
    typedef uchar Size;
    struct FontStyle { enum {
        REGULAR = 0,
        BOLDFONT = 1,
        ITALICFONT = 2,
        UNDERLINED = 4,
        STRIKETHROUGH = 8
    }; };
    typedef uchar Style;

    static const Style DEFAULT_FLAGS;
    static const Size  DEFAULT_SIZE;
    static const char* DEFAULT_NAME;

    TCustomFont(const string& name_ = DEFAULT_NAME, Size size_ = DEFAULT_SIZE, Style style_ = DEFAULT_FLAGS);
    ~TCustomFont() = default;

    bool operator==(const TCustomFont& other) const;
    bool operator!=(const TCustomFont& other) const;

    const string& getName() const;
    Size getSize() const;
    Style getStyle() const;

    Graphics::TText createText(const TextString& text) const;
    Graphics::TText createText(TextString&& text) const;

    static float GetTextWidth(const TextString& text, const TCustomFont& font);
    static float GetTextHeight(const TextString& text, const TCustomFont& font);
    float GetTextWidth(const TextString& text) const;
    float GetTextHeight(const TextString& text) const;

    bool isDefault() const;
private:
    Style flags;
    string name;
    Size size;

    typedef const Graphics::TFont* Font;
    Font font;

    const Graphics::TFont& getFont() const;
};

typedef TCustomFont TFont;
typedef Graphics::TText TText;

class TCustomFontsCache
{
public:
    static TCustomFontsCache& getInstance();

    const Graphics::TFont* get(const TCustomFont& font);
private:
    static TCustomFontsCache* _instance;
    TCustomFontsCache();
    ~TCustomFontsCache() = default;

    typedef string Key;
    typedef std::unique_ptr<Graphics::TFont> Entry;

    std::map<Key, Entry> loadedFonts;

    bool isLoaded(const Key& key) const;
    static Key makeKey(const TCustomFont& font);
    const Graphics::TFont* load(const TCustomFont& font);
};

#endif // CUSTOMFONT_H
