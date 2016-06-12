#include "customfont.h"
#include "gui_core.h"
#include "customfonts_cache.h"



namespace GUI {


const TCustomFont::Style TCustomFont::DEFAULT_FLAGS = TCustomFont::Style::Regular;
const TCustomFont::Size  TCustomFont::DEFAULT_SIZE  = 14;

#if defined(_DEBUG)
const string TCustomFont::DEFAULT_NAME = "defaultfont.ttf";
#else
const string TCustomFont::DEFAULT_NAME = "";
#endif


TCustomFont::TCustomFont(const string& filePath,
    const Size& size, const Style& style
) :
    flags(style), filePath(filePath), size(size)
{
    if (filePath.empty() == false) {
        font = TCustomFontsCache::GetInstance().Get(*this);
    }
}

bool TCustomFont::operator==(const TCustomFont& other) const {
    return font == other.font;
}

bool TCustomFont::operator!=(const TCustomFont& other) const {
    return font != other.font;
}

const string& TCustomFont::GetName() const {
    return filePath;
}

const TCustomFont::Size& TCustomFont::GetSize() const {
    return size;
}

const TCustomFont::Style& TCustomFont::GetStyle() const {
    return flags;
}

const Graphics::TFont& TCustomFont::getFont() const {
#if defined(_DEBUG)
    GUI_ASSERT(font != nullptr, "Attempt to use an uninitialized font")
#endif // _DEBUG
    return *font;
}

float TCustomFont::GetTextWidth(const TextString& text, const TCustomFont& font) {
    return GetTextWidth(text, font);
}

float TCustomFont::GetTextHeight(const TextString& text, const TCustomFont& font) {
    return GetTextHeight(text, font);
}

float TCustomFont::GetTextWidth(const TextString& text) const {
    Graphics::TText textRepr = CreateText(text);
    return textRepr.getGlobalBounds().width;
}
float TCustomFont::GetTextHeight(const TextString& text) const {
    Graphics::TText textRepr = CreateText(text);
    return textRepr.getGlobalBounds().height;
}

Graphics::TText TCustomFont::CreateText(const TextString& text) const {
    Graphics::TText result(text, getFont(), size);
    result.setStyle(static_cast<uint>(flags));
    return result;
}

Graphics::TText TCustomFont::CreateText(TextString&& text) const {
    Graphics::TText result(std::forward<TextString>(text), getFont(), size);
    result.setStyle(static_cast<uint>(flags));
    return result;
}


} // namespace GUI
