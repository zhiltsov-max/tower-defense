#include "customfont.h"
#include "gui_core.h"
#include "settings.h"
#include "customfonts_cache.h"



const TCustomFont::Style TCustomFont::DEFAULT_FLAGS = TCustomFont::Style::Regular;
const TCustomFont::Size  TCustomFont::DEFAULT_SIZE  = 14;
const char*              TCustomFont::DEFAULT_NAME  = TGUISettings::DEFAULT_FONT;

TCustomFont::TCustomFont(const string& name, const Size& size, const Style& style) :
    flags(style), name(name), size(size)
{
    font = TCustomFontsCache::GetInstance().Get(*this);
}

bool TCustomFont::operator==(const TCustomFont& other) const {
    return font == other.font;
}

bool TCustomFont::operator!=(const TCustomFont& other) const {
    return font != other.font;
}

const string& TCustomFont::GetName() const {
    return name;
}

const TCustomFont::Size& TCustomFont::GetSize() const {
    return size;
}

const TCustomFont::Style& TCustomFont::GetStyle() const {
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
    Graphics::TText textRepr = std::move(CreateText(text));
    return textRepr.getGlobalBounds().width;
}
float TCustomFont::GetTextHeight(const TextString& text) const {
    Graphics::TText textRepr = std::move(CreateText(text));
    return textRepr.getGlobalBounds().height;
}

Graphics::TText TCustomFont::CreateText(const TextString& text) const {
    Graphics::TText result(text, getFont(), size);
    result.setStyle(static_cast<uint>(flags));
    return result;
}

Graphics::TText TCustomFont::CreateText(TextString&& text) const {
    Graphics::TText result(std::move(text), getFont(), size);
    result.setStyle(static_cast<uint>(flags));
    return result;
}
