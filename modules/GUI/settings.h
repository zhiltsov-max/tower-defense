#ifndef SETTINGS_H
#define SETTINGS_H

class TGUISettings
{
public:
    static constexpr char DefaultKeySeparator = ':';
    static constexpr const char* DEFAULT_UIPARENT_NAME = "UIParent";
    static constexpr const char* DEFAULT_FONTS_FOLDER = "resources/";
    static constexpr const char* DEFAULT_FONT = "calibri.ttf";

    TGUISettings() = delete;
};

#endif // SETTINGS_H
