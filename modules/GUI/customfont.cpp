#include "gui_core.h"
#include "customfont.h"
#include "settings.h"

const TCustomFont::Style TCustomFont::DEFAULT_FLAGS = TCustomFont::FontStyle::REGULAR;
const TCustomFont::Size  TCustomFont::DEFAULT_SIZE  = 14;
const char*              TCustomFont::DEFAULT_NAME  = TGUISettings::DEFAULT_FONT;

TCustomFont::TCustomFont(const string& name_, Size size_, Style style_) :
    flags(style_), name(name_), size(size_)
{
    font = TCustomFontsCache::getInstance().get(*this);
}

bool TCustomFont::operator==(const TCustomFont& other) const {
    return font == other.font;
}

bool TCustomFont::operator!=(const TCustomFont& other) const {
    return font != other.font;
}

const string& TCustomFont::getName() const {
    return name;
}

TCustomFont::Size TCustomFont::getSize() const {
    return size;
}

TCustomFont::Style TCustomFont::getStyle() const {
    return flags;
}

const Graphics::TFont& TCustomFont::getFont() const {
    return *font;
}

bool TCustomFont::isDefault() const {
    return (name.compare(DEFAULT_NAME) == 0) && (flags == DEFAULT_FLAGS) && (size == DEFAULT_SIZE);
}

float TCustomFont::GetTextWidth(const TextString& text, const TCustomFont& font) {
    return GetTextWidth(text, font);
}

float TCustomFont::GetTextHeight(const TextString& text, const TCustomFont& font) {
    return GetTextHeight(text, font);
}

float TCustomFont::GetTextWidth(const TextString& text) const {
    Graphics::TText textRepr = std::move(createText(text));
    return textRepr.getGlobalBounds().width;
}
float TCustomFont::GetTextHeight(const TextString& text) const {
    Graphics::TText textRepr = std::move(createText(text));
    return textRepr.getGlobalBounds().height;
}

Graphics::TText TCustomFont::createText(const TextString& text) const {
    Graphics::TText result(text, getFont(), size);
    result.setStyle(flags);
    return result;
}

Graphics::TText TCustomFont::createText(TextString&& text) const {
    Graphics::TText result(std::move(text), getFont(), size);
    result.setStyle(flags);
    return result;
}


TCustomFontsCache* TCustomFontsCache::_instance = nullptr;

TCustomFontsCache::TCustomFontsCache()
{
    if (_instance != nullptr) {
         throw exception("Can not create multiple instances of TCustomFontsCache.");
    }
    _instance = this;
}

TCustomFontsCache& TCustomFontsCache::getInstance() {
    if (_instance == nullptr) {
        _instance = new TCustomFontsCache;
    }
    return *_instance;
}

const Graphics::TFont* TCustomFontsCache::load(const TCustomFont& font_) {
    const Key key = makeKey(font_);
    if (isLoaded(key) == true) {
        return loadedFonts.at(key).get();
    }

    Entry& font = loadedFonts[key];
    font.reset(new Graphics::TFont());
    string fontPath = TGUISettings::DEFAULT_FONTS_FOLDER + std::move(String::toLower(font_.getName()));
    if (font->loadFromFile(fontPath) == false) {
#if defined(_DEBUG)
        GUI_THROW("Font file '" + fontPath + "' not found");
#else
        // TO DO: ...
#endif
    }
    return font.get();
}

const Graphics::TFont* TCustomFontsCache::get(const TCustomFont& font) {
    const Key key = makeKey(font);
    if (isLoaded(key) == true) {
        return loadedFonts.at(key).get();
    } else {
        return load(font);
    }
}

TCustomFontsCache::Key TCustomFontsCache::makeKey(const TCustomFont& font) {
    return font.getName();
}

bool TCustomFontsCache::isLoaded(const Key& key) const {
    return loadedFonts.count(key) != 0;
}
