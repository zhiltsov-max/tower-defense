#ifndef CUSTOMFONTS_CACHE_H
#define CUSTOMFONTS_CACHE_H

#include "gui_core.h"
#include "customfont.h"



namespace GUI {


/*
Class represents loading cache for fonts subsystem.
*/
class TCustomFontsCache
{
public:
    static TCustomFontsCache& GetInstance();


    ~TCustomFontsCache() = default;

    const Graphics::TFont* Get(const TCustomFont& font);

private:
    static std::unique_ptr<TCustomFontsCache> _instance;


    using Key = string;
    using Entry = std::unique_ptr<Graphics::TFont>;

    std::map<Key, Entry> loadedFonts;

    TCustomFontsCache();

    bool isLoaded(const Key& key) const;
    const Graphics::TFont* load(const TCustomFont& font);

    static Key makeKey(const TCustomFont& font);
};


} // namespace GUI

#endif // CUSTOMFONTS_CACHE_H
