#ifndef GUI_LUA_BINDING_H
#define GUI_LUA_BINDING_H

#include "Core/luawrapper.h"


#define BEGIN_GUI_LUA_BINDING BEGIN_GUI namespace lua_binding {
#define END_GUI_LUA_BINDING   }; END_GUI

/* Core export
 * Disabled by: GUI_LUA_NO_CORE_BINDING
*/
#if !defined(GUI_LUA_NO_CORE_BINDING)
    #include "gui_main.h"

BEGIN_GUI_LUA_BINDING
    using TPadding = GUI::TPadding;
    using TColor = GUI::TColor;
    using TFontStyle = int;
    using TFont = GUI::TFont;
    using TSize = GUI::TSize;
    using TCoordinate = GUI::TCoordinate;
    using TText = Graphics::TText;
    using TImage = GUI::TImageContainer*;
    using TImageSource = GUI::TImageSource;
    using TRect = GUI::TRect;

    void bindCore(lua::State& state);
END_GUI_LUA_BINDING

    LUAPP_ARG_CONVERT(wchar_t, { return (wchar_t)val.cast<uint>(); })
    LUAPP_RV_CONVERT (wchar_t, { return context.ret((uint)val); })
    LUAPP_USERDATA(wstring, "wstring")
    LUAPP_RV_CONVERT(std::vector<wstring>, {
        Table t(context);
        for (auto i = 0u, iend = val.size(); i != iend; ++i) {
            t[i] = std::move(val[i]);
        }
        return context.ret(t);
    })

    LUAPP_ARG_CONVERT(GUI::lua_binding::TImage, { return static_cast<GUI::lua_binding::TImage>(val.cast<LightUserData>()); })
    LUAPP_RV_CONVERT (GUI::lua_binding::TImage, { return context.ret((LightUserData)val); })

    LUAPP_ARG_CONVERT(TCustomFont::Style, { return static_cast<TCustomFont::Style>(val.cast<int>()); })
    LUAPP_RV_CONVERT(TCustomFont::Style, { return context.ret(static_cast<GUI::lua_binding::TFontStyle>(val)); })

    LUAPP_USERDATA(Vec2f, "Vec2f")
    //LUAPP_USERDATA(GUI::TSize, "Size")
    //LUAPP_USERDATA(GUI::TCoordinate, "Coordinate")
    LUAPP_USERDATA(GUI::lua_binding::TPadding, "Padding")
    LUAPP_USERDATA(GUI::lua_binding::TColor, "Color")
    LUAPP_USERDATA(GUI::lua_binding::TFont, "Font")


    LUAPP_ARG_CONVERT(sf::String, { return val.cast<TextString>(); })
    LUAPP_RV_CONVERT (sf::String, { return context.ret(TextString(val)); })
    LUAPP_USERDATA(sf::Transformable, "sfTransformable")
    LUAPP_USERDATA(sf::Drawable, "sfDrawable")
    LUAPP_USERDATA(GUI::lua_binding::TText, "Text")
#endif //GUI_LUA_NO_CORE_BINDING

/* Widget export
 * Disabled by: GUI_LUA_NO_WIDGET_BINDING
*/
#if !defined(GUI_LUA_NO_WIDGET_BINDING)
    #include "widget.h"

BEGIN_GUI_LUA_BINDING
    using TWidgetSignal = GUI::TWidget::Signal*;
    using TWidgetSlot = GUI::TWidget::Slot*;
    using TWidget = GUI::TWidgetRef;
    using TWidgetRef = GUI::TWidgetWeakRef;
    using SignalID = GUI::SignalID;
    using TWidgetSource = GUI::TWidgetSource;

    void bindWidget(lua::State& state);
END_GUI_LUA_BINDING

    LUAPP_USERDATA(GUI::lua_binding::TWidget, "Widget")
    LUAPP_USERDATA(GUI::lua_binding::TWidgetRef, "WidgetRef")
#endif //GUI_LUA_NO_WIDGET_BINDING

/* AbstractWindow export
 * Disabled by: GUI_LUA_NO_ABSTRACTWINDOW_BINDING
*/
#if !defined(GUI_LUA_NO_ABSTRACTWINDOW_BINDING)
    #include "abstractwindow.h"

BEGIN_GUI_LUA_BINDING
    using TAbstractWindow = std::shared_ptr<GUI::TAbstractWindow>;
    using TAbstractWindowSource = GUI::TAbstractWindowSource;

    void bindAbstractWindow(lua::State& state);
END_GUI_LUA_BINDING

    LUAPP_ARG_CONVERT(GUI::lua_binding::TAbstractWindow, { return std::dynamic_pointer_cast<GUI::TAbstractWindow>(val.cast<GUI::lua_binding::TWidget>()); })
    LUAPP_RV_CONVERT (GUI::lua_binding::TAbstractWindow, { return context.ret(GUI::lua_binding::TWidget(val)); })
#endif //GUI_LUA_NO_ABSTRACTWINDOW_BINDING

/* Window binding
 * Disabled by: GUI_LUA_NO_WINDOW_BINDING
*/
#if !defined(GUI_LUA_NO_WINDOW_BINDING)
    #include "window.h"

BEGIN_GUI_LUA_BINDING
    using TWindow = std::shared_ptr<GUI::TWindow>;
    using TWindowSource = GUI::TWindowSource;

    void bindWindow(lua::State& state);
END_GUI_LUA_BINDING

    LUAPP_ARG_CONVERT(GUI::lua_binding::TWindow, { return std::dynamic_pointer_cast<GUI::TWindow>(val.cast<GUI::lua_binding::TWidget>()); })
    LUAPP_RV_CONVERT (GUI::lua_binding::TWindow, { return context.ret(GUI::lua_binding::TWidget(val)); })
#endif //GUI_LUA_NO_WINDOW_BINDING

/* TransparentWindow binding
 * Disabled by: GUI_LUA_NO_TRANSPARENTWINDOW_BINDING
*/
#if !defined(GUI_LUA_NO_TRANSPARENTWINDOW_BINDING)
    #include "transparentwindow.h"

BEGIN_GUI_LUA_BINDING
    using TTransparentWindow = std::shared_ptr<GUI::TTransparentWindow>;
    using TTransparentWindowSource = GUI::TTransparentWindowSource;

    void bindTransparentWindow(lua::State& state);
END_GUI_LUA_BINDING

    LUAPP_ARG_CONVERT(GUI::lua_binding::TTransparentWindow, { return std::dynamic_pointer_cast<GUI::TTransparentWindow>(val.cast<GUI::lua_binding::TWidget>()); })
    LUAPP_RV_CONVERT (GUI::lua_binding::TTransparentWindow, { return context.ret(GUI::lua_binding::TWidget(val)); })
#endif

/* UIParent binding
 * Disable by: GUI_LUA_NO_UIPARENT_BINDING
*/
#if !defined(GUI_LUA_NO_UIPARENT_BINDING)
    #include "uiparent.h"

BEGIN_GUI_LUA_BINDING
    using TUIParent = std::shared_ptr<GUI::TUIParent>;

    void bindUIParent(lua::State& state);
END_GUI_LUA_BINDING

    LUAPP_ARG_CONVERT(GUI::lua_binding::TUIParent, { return std::dynamic_pointer_cast<GUI::TUIParent>(val.cast<GUI::lua_binding::TWidget>()); })
    LUAPP_RV_CONVERT (GUI::lua_binding::TUIParent, { return context.ret(GUI::lua_binding::TWidget(val)); })
#endif //GUI_LUA_NO_UIPARENT_BINDING

/* AbstractButton binding
 * Disabled by: GUI_LUA_NO_ABSTRACTBUTTON_BINDING
*/
#if !defined(GUI_LUA_NO_ABSTRACTBUTTON_BINDING)
    #include "abstractbutton.h"

BEGIN_GUI_LUA_BINDING
    using TAbstractButton = std::shared_ptr<GUI::TAbstractButton>;
    using TAbstractButtonSource = GUI::TAbstractButtonSource;

    void bindAbstractButton(lua::State& state);
END_GUI_LUA_BINDING

    LUAPP_ARG_CONVERT(GUI::lua_binding::TAbstractButton, { return std::dynamic_pointer_cast<GUI::TAbstractButton>(val.cast<GUI::lua_binding::TWidget>()); })
    LUAPP_RV_CONVERT (GUI::lua_binding::TAbstractButton, { return context.ret(GUI::lua_binding::TWidget(val)); })
#endif //GUI_LUA_NO_ABSTRACTBUTTON_BINDING


/* PushButton binding
 * Disabled by: GUI_LUA_NO_PUSHBUTTON_BINDING
*/
#if !defined(GUI_LUA_NO_PUSHBUTTON_BINDING)
    #include "pushbutton.h"

BEGIN_GUI_LUA_BINDING
    using TPushButton = std::shared_ptr<GUI::TPushButton>;
    using TPushButtonSource = GUI::TPushButtonSource;

    void bindPushButton(lua::State& state);
END_GUI_LUA_BINDING

    LUAPP_ARG_CONVERT(GUI::lua_binding::TPushButton, { return std::dynamic_pointer_cast<GUI::TPushButton>(val.cast<GUI::lua_binding::TWidget>()); })
    LUAPP_RV_CONVERT (GUI::lua_binding::TPushButton, { return context.ret(GUI::lua_binding::TWidget(val)); })
#endif

/* AbstractTextBox binding
 * Disabled by: GUI_LUA_NO_ABSTRACTTEXTBOX_BINDING
*/
#if !defined(GUI_LUA_NO_ABSTRACTTEXTBOX_BINDING)
    #include "abstracttextbox.h"

BEGIN_GUI_LUA_BINDING
    using TAbstractTextBox = std::shared_ptr<GUI::TAbstractTextBox>;
    using TAbstractTextBoxSource = GUI::TAbstractTextBoxSource;

    void bindAbstractTextBox(lua::State& state);
END_GUI_LUA_BINDING

    LUAPP_ARG_CONVERT(GUI::lua_binding::TAbstractTextBox, { return std::dynamic_pointer_cast<GUI::TAbstractTextBox>(val.cast<GUI::lua_binding::TWidget>()); })
    LUAPP_RV_CONVERT (GUI::lua_binding::TAbstractTextBox, { return context.ret(GUI::lua_binding::TWidget(val)); })
#endif

/* SimpleTextBox binding
 * Disabled by: GUI_LUA_NO_SIMPLETEXTBOX_BINDING
*/
#if !defined(GUI_LUA_NO_SIMPLETEXTBOX_BINDING)
    #include "simpletextbox.h"

BEGIN_GUI_LUA_BINDING
    using TSimpleTextBox = std::shared_ptr<GUI::TSimpleTextBox>;
    using TSimpleTextBoxSource = GUI::TSimpleTextBoxSource;

    void bindSimpleTextBox(lua::State& state);
END_GUI_LUA_BINDING

    LUAPP_ARG_CONVERT(GUI::lua_binding::TSimpleTextBox, { return std::dynamic_pointer_cast<GUI::TSimpleTextBox>(val.cast<GUI::lua_binding::TWidget>()); })
    LUAPP_RV_CONVERT (GUI::lua_binding::TSimpleTextBox, { return context.ret(GUI::lua_binding::TWidget(val)); })
#endif

/* RichTextBox binding
 * Disabled by: GUI_LUA_NO_SIMPLETEXTBOX_BINDING
*/
#if !defined(GUI_LUA_NO_SIMPLETEXTBOX_BINDING)
    #include "richtextbox.h"

BEGIN_GUI_LUA_BINDING
    using TRichTextBox = std::shared_ptr<GUI::TRichTextBox>;
    using TRichTextBoxSource = GUI::TRichTextBoxSource;
    using TRichTextBoxSeparators = GUI::TRichTextBoxSource::Separators;

    void bindRichTextBox(lua::State& state);
END_GUI_LUA_BINDING

    LUAPP_ARG_CONVERT(GUI::lua_binding::TRichTextBox, { return std::dynamic_pointer_cast<GUI::TRichTextBox>(val.cast<GUI::lua_binding::TWidget>()); })
    LUAPP_RV_CONVERT (GUI::lua_binding::TRichTextBox, { return context.ret(GUI::lua_binding::TWidget(val)); })
#endif

/* ImageBox binding
 * Disabled by: GUI_LUA_NO_IMAGEBOX_BINDING
*/
#if !defined(GUI_LUA_NO_IMAGEBOX_BINDING)
    #include "imagebox.h"

BEGIN_GUI_LUA_BINDING
    using TImageBox = std::shared_ptr<GUI::TImageBox>;
    using TImageBoxSource = GUI::TImageBoxSource;

    void bindImageBox(lua::State& state);
END_GUI_LUA_BINDING

    LUAPP_ARG_CONVERT(GUI::lua_binding::TImageBox, { return std::dynamic_pointer_cast<GUI::TImageBox>(val.cast<GUI::lua_binding::TWidget>()); })
    LUAPP_RV_CONVERT (GUI::lua_binding::TImageBox, { return context.ret(GUI::lua_binding::TWidget(val)); })
#endif


BEGIN_GUI_LUA_BINDING
    void bindToLUA(lua::State& state);
END_GUI_LUA_BINDING


#endif // GUI_LUA_BINDING_H
