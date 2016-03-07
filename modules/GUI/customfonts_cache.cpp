#include "customfonts_cache.h"
#include "settings.h"



std::unique_ptr<TCustomFontsCache> TCustomFontsCache::_instance(nullptr);

TCustomFontsCache::TCustomFontsCache() {
    if (_instance != nullptr) {
         GUI_THROW("Can not create multiple instances of TCustomFontsCache.");
    }
}

TCustomFontsCache& TCustomFontsCache::GetInstance() {
    if (_instance == nullptr) {
        _instance.reset(new TCustomFontsCache);
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
    string fontPath = TGUISettings::DEFAULT_FONTS_FOLDER + std::move(String::toLower(font_.GetName()));
    if (font->loadFromFile(fontPath) == false) {
#if defined(_DEBUG)
        GUI_THROW("Font file '" + fontPath + "' not found");
#else
        // TO DO: ...
#endif
    }
    return font.get();
}

const Graphics::TFont* TCustomFontsCache::Get(const TCustomFont& font) {
    const Key key = makeKey(font);
    if (isLoaded(key) == true) {
        return loadedFonts.at(key).get();
    } else {
        return load(font);
    }
}

TCustomFontsCache::Key TCustomFontsCache::makeKey(const TCustomFont& font) {
    return font.GetName();
}

bool TCustomFontsCache::isLoaded(const Key& key) const {
    return loadedFonts.count(key) != 0;
}
