#include "gui_lua_binding.h"
#include "Application/application.h"
#include "Application/application_ui.h"



using namespace GUI::lua_binding;
using namespace lua;


#if !defined(GUI_LUA_NO_CORE_BINDING)
    wstring eWstring_create() {
        return wstring();
    }
    void   eWstring_destroy(wstring& self) {
        self.~basic_string();
    }
    bool   eWstring_equals(wstring& self, const wstring& other) {
        return self.compare(other) == 0;
    }
    wstring eWstring_add(const wstring& a, const wstring& b) {
        return a + b;
    }
    void   eWstring_write(wstring& self, size_t index, wchar_t chr) {
        self[index] = chr;
    }
    bool   eWstring_contains_from(const wstring& self, const wstring& needle, size_t start) {
        return self.find(needle, start) != self.npos;
    }
    bool   eWstring_contains(const wstring& self, const wstring& needle) {
        return self.find(needle) != self.npos;
    }
    int    eWstring_to_int(const wstring& self) {
        return std::stoi(self);
    }
    double eWstring_to_double(const wstring& self) {
        return std::stod(self);
    }
    int    eWstring_to_int_based(const wstring& self, size_t base) {
        return std::stoi(self, 0, base);
    }
    string eWstring_to_ansi(const wstring& self) {
        return sf::String(self);
    }
    Retval exportWstring(Context& ctx) {
        ctx.mt<wstring>() = Table::records(ctx);
        ctx.mt<wstring>()["create"] = eWstring_create;
        ctx.mt<wstring>()["at"]     = static_cast<const wchar_t& (wstring::*)(size_t) const>(wstring::at);
        ctx.mt<wstring>()["set"]    = eWstring_write;
        ctx.mt<wstring>()["__gc"]   = eWstring_destroy;
        ctx.mt<wstring>()["__len"]  = wstring::size;
        ctx.mt<wstring>()["__eq"]   = eWstring_equals;
        ctx.mt<wstring>()["compare"]= static_cast<int (wstring::*)(const wstring&) const>(wstring::compare);
        ctx.mt<wstring>()["resize"] = static_cast<void (wstring::*)(wstring::size_type)>(wstring::resize);
        ctx.mt<wstring>()["reserve"]= wstring::reserve;
        ctx.mt<wstring>()["empty"]  = wstring::empty;
        ctx.mt<wstring>()["__concat"]=eWstring_add;
        ctx.mt<wstring>()["append"] = static_cast<wstring& (wstring::*)(const wstring&)>(wstring::append);
        ctx.mt<wstring>()["clear"]  = wstring::clear;
        ctx.mt<wstring>()["capacity"]=wstring::capacity;
        ctx.mt<wstring>()["replace"]= static_cast<wstring& (wstring::*)(size_t, size_t, const wstring&)>(wstring::replace);
        ctx.mt<wstring>()["substr"] = wstring::substr;
        ctx.mt<wstring>()["find"]   = static_cast<wstring::size_type (wstring::*)(const wstring&, wstring::size_type) const>(wstring::find);
        ctx.mt<wstring>()["contains"]=eWstring_contains;
        ctx.mt<wstring>()["contains_from"]=eWstring_contains_from;
        ctx.mt<wstring>()["to_int"] = eWstring_to_int;
        ctx.mt<wstring>()["to_double"]=eWstring_to_double;
        ctx.mt<wstring>()["__tostring"]=eWstring_to_ansi;
        ctx.mt<wstring>()["from_number"]=static_cast<wstring (*)(double)>(std::to_wstring);
        ctx.mt<wstring>()["from_ansi"]=static_cast<wstring (*)(const string&)>(String::toWide);
        ctx.mt<wstring>()["split"]  = static_cast<std::vector<wstring> (*)(const wstring&, const wstring&)>(String::split);
        ctx.mt<wstring>()["__index"] = ctx.mt<wstring>();

        ctx.global["Wstr"] = static_cast<wstring (*)(const string&)>(String::toWide);
        ctx.global["TWideString"] = ctx.mt<wstring>();
        return ctx.ret();
    }


    Vec2f  eVec2f_create(float x, float y) {
        return Vec2f(x, y);
    }
    void   eVec2f_destroy(Vec2f& vec) {
        vec.~Vec2f();
    }
    bool   eVec2f_less(const Vec2f& v1, const Vec2f& v2) {
        return v1 < v2;
    }
    bool   eVec2f_lesserEqual(const Vec2f& v1, const Vec2f& v2) {
        return v1 <= v2;
    }
    double eVec2f_norm(const Vec2f& vec, uint normType) {
        return norm(vec, (NormType)normType);
    }
    float& eVec2f_write(Vec2f& self, size_t index, float value) {
        return self[index] = value;
    }
    float& eVec2f_x(Vec2f& self) {
        return self.x;
    }
    float& eVec2f_y(Vec2f& self) {
        return self.y;
    }
    float& eVec2f_setX(Vec2f& self, float value) {
        return self.x = value;
    }
    float& eVec2f_setY(Vec2f& self, float value) {
        return self.y = value;
    }
    size_t eVec2f_size(Vec2f&) {
        return 2;
    }
    Vec2f  eVec2f_mul_by_number(const Vec2f& self, float value) {
        return self * value;
    }
    void eVec2f_imul_by_number(Vec2f& self, float value) {
        self *= value;
    }
    Retval exportVec2f(Context& ctx) {
        ctx.mt<Vec2f>() = Table::records(ctx);
        ctx.mt<Vec2f>()["create"] = eVec2f_create;
        ctx.mt<Vec2f>()["__newindex"] = eVec2f_write;
        ctx.mt<Vec2f>()["x"] = eVec2f_x;
        ctx.mt<Vec2f>()["y"] = eVec2f_y;
        ctx.mt<Vec2f>()["setX"] = eVec2f_setX;
        ctx.mt<Vec2f>()["setY"] = eVec2f_setY;
        ctx.mt<Vec2f>()["__len"] = eVec2f_size;
        ctx.mt<Vec2f>()["__add"] = static_cast<Vec2f (*)(const Vec2f&, const Vec2f&)>(operator +);
        ctx.mt<Vec2f>()["__sub"] = static_cast<Vec2f (*)(const Vec2f&, const Vec2f&)>(operator -);
        ctx.mt<Vec2f>()["__mul"] = static_cast<Vec2f (*)(const Vec2f&, const double&)>(operator *);;
        ctx.mt<Vec2f>()["__lt"] = static_cast<bool (*)(const Vec2f&, const Vec2f&)>(operator <);
        ctx.mt<Vec2f>()["__le"] = static_cast<bool (*)(const Vec2f&, const Vec2f&)>(operator <=);
        ctx.mt<Vec2f>()["__eq"] = static_cast<bool (*)(const Vec2f&, const Vec2f&)>(operator ==);
        ctx.mt<Vec2f>()["__gc"] = eVec2f_destroy;
        ctx.mt<Vec2f>()["__tostring"] = static_cast<string (Vec2f::*)(void) const>(Vec2f::operator string);
        ctx.mt<Vec2f>()["isInRect"] = Vec2f::isInRect;
        ctx.mt<Vec2f>()["abs"] = static_cast<Vec2f (*)(const Vec2f&)>(abs);
        ctx.mt<Vec2f>()["norm"] = eVec2f_norm;
        ctx.mt<Vec2f>()["rescale"] = eVec2f_imul_by_number;
        ctx.mt<Vec2f>()["__index"] = ctx.mt<Vec2f>();

        ctx.global["Vec2f"] = eVec2f_create;
        ctx.global["TVec2f"] = ctx.mt<Vec2f>();
        return ctx.ret();
    }


    Retval exportTSize(Context& ctx) {
        ctx.global["Size"] = eVec2f_create;
        ctx.global["TSize"] = ctx.mt<Vec2f>();
        return ctx.ret();
    }


    Retval exportTCoordinate(Context& ctx) {
        ctx.global["Coordinate"] = eVec2f_create;
        ctx.global["TCoordinate"] = ctx.mt<Vec2f>();
        return ctx.ret();
    }


    TPadding eTPadding_create(float top, float bottom, float left, float right) {
        return TPadding(top, bottom, left, right);
    }
    void     eTPadding_destroy(TPadding& padding) {
        padding.~TPadding();
    }
    float&   eTPadding_top(TPadding& self) {
        return self.top;
    }
    float&   eTPadding_bottom(TPadding& self) {
        return self.bottom;
    }
    float&   eTPadding_left(TPadding& self) {
        return self.left;
    }
    float&   eTPadding_right(TPadding& self) {
        return self.right;
    }
    void     eTPadding_setTop(TPadding& self, float value) {
        self.top = value;
    }
    void     eTPadding_setBottom(TPadding& self, float value) {
        self.bottom = value;
    }
    void     eTPadding_setLeft(TPadding& self, float value) {
        self.left = value;
    }
    void     eTPadding_setRight(TPadding& self, float value) {
        self.right = value;
    }
    Retval exportTPadding(Context& ctx) {
        ctx.mt<TPadding>() = Table::records(ctx,
            "Create",       eTPadding_create,
            "top",          eTPadding_top,
            "bottom",       eTPadding_bottom,
            "left",         eTPadding_left,
            "right",        eTPadding_right,
            "SetTop",       eTPadding_setTop,
            "SetBottom",    eTPadding_setBottom,
            "SetLeft",      eTPadding_setLeft,
            "SetRight",     eTPadding_setRight,
            "__eq",         TPadding::operator ==,
            "__gc",         eTPadding_destroy
        );
        ctx.mt<TPadding>()["__index"] = ctx.mt<TPadding>();
        ctx.global["Padding"] = eTPadding_create;
        ctx.global["TPadding"] = ctx.mt<TPadding>();
        return ctx.ret();
    }


    TColor eTColor_create(uint r, uint g, uint b, uint a) {
        return TColor(r, g, b, a);
    }
    TColor eTColor_createARGB(uint argb) {
        return TColor(argb);
    }
    void   eTColor_destroy(TColor& self) {
        self.~TColor();
    }
    uint   eTColor_a(TColor& self) {
        return self.a;
    }
    uint   eTColor_r(TColor& self) {
        return self.r;
    }
    uint   eTColor_g(TColor& self) {
        return self.g;
    }
    uint   eTColor_b(TColor& self) {
        return self.b;
    }
    uint   eTColor_argb(TColor& self) {
        return static_cast<uint>(self);
    }
    void   eTColor_setA(TColor& self, uint value) {
        self.a = value;
    }
    void   eTColor_setR(TColor& self, uint value) {
        self.r = value;
    }
    void   eTColor_setG(TColor& self, uint value) {
        self.g = value;
    }
    void   eTColor_setB(TColor& self, uint value) {
        self.b = value;
    }
    void   eTColor_setARGB(TColor& self, uint value) {
        self = value;
    }
    string eTColor_tostring(TColor& self) {
        const size_t HEX_INT_CHAR_COUNT = 2/*0x*/ + 8/*00000000*/ + 1/*\0*/;
        char out[HEX_INT_CHAR_COUNT] = {0};
        std::snprintf(out, HEX_INT_CHAR_COUNT, "%#X", static_cast<uint>(self));
        return string(out);
    }
    Retval exportTColor(Context& ctx) {
        ctx.mt<TColor>() = Table::records(ctx,
            "Create",       eTColor_create,
            "FromARGB",     eTColor_createARGB,
            "a",            eTColor_a,
            "r",            eTColor_r,
            "g",            eTColor_g,
            "b",            eTColor_b,
            "argb",         eTColor_argb,
            "SetA",         eTColor_setA,
            "SetR",         eTColor_setR,
            "SetG",         eTColor_setG,
            "SetB",         eTColor_setB,
            "SetARGB",      eTColor_setARGB,
            "__tostring",   eTColor_tostring,
            "__eq",         TColor::operator ==,
            "__gc",         eTColor_destroy
        );
        ctx.mt<TColor>()["__index"] = ctx.mt<TColor>();
        ctx.global["Color"] = eTColor_create;
        ctx.global["ColorARGB"] = eTColor_createARGB;
        ctx.global["TColor"] = ctx.mt<TColor>();
        return ctx.ret();
    }


    TFont eTFont_create(const string& name, size_t size, TFontStyle style) {
        return TFont(name, size, static_cast<TCustomFont::Style>(style));
    }
    void  eTFont_destroy(TFont& self) {
        self.~TCustomFont();
    }
    Retval exportTFont(Context& ctx) {
        ctx.mt<TFont>() = Table::records(ctx,
            "Create",       eTFont_create,
            "name",         TFont::GetName,
            "size",         TFont::GetSize,
            "style",        TFont::GetStyle,
            "IsDefault",    TFont::isDefault,
            "CreateText",   static_cast<TText (TFont::*)(const TextString&) const>(TFont::CreateText),
            "GetTextWidth", static_cast<float (TFont::*)(const TextString&) const>(TFont::GetTextWidth),
            "GetTextHeight",static_cast<float (TFont::*)(const TextString&) const>(TFont::GetTextHeight),
            "__eq",         TFont::operator ==,
            "__gc",         eTFont_destroy
        );
        ctx.mt<TFont>()["__index"] = ctx.mt<TFont>();
        ctx.global["Font"] = eTFont_create;
        ctx.global["TFont"] = ctx.mt<TFont>();

        ctx.global["FontStyle"] = Table::records(ctx,
            "regular",      static_cast<TFontStyle>(TFont::Style::Regular),
            "bold",         static_cast<TFontStyle>(TFont::Style::Bold),
            "italic",       static_cast<TFontStyle>(TFont::Style::Italic),
            "strikethrough",static_cast<TFontStyle>(TFont::Style::Strikethrough),
            "underlined",   static_cast<TFontStyle>(TFont::Style::Underlined)
        );

        return ctx.ret();
    }


    TText eTText_create1(const TextString& text) {
        return TFont().CreateText(text);
    }
    TText eTText_create2(const TextString& text, const TFont& font) {
        return font.CreateText(text);
    }
    void  eTText_setColor(TText& self, TColor& color) {
        self.setColor(color);
    }
    TColor eTText_getColor(TText& self) {
        return TColor(self.getColor());
    }
    Vec2f eTText_getPosition(TText& self) {
        return Vec2f(self.getPosition());
    }
    Vec2f eTText_getScale(TText& self) {
        return Vec2f(self.getScale());
    }
    void  eTText_destroy(TText& self) {
        self.~TText();
    }
    Retval exportTText(Context& ctx) {
        ctx.mt<TText>() = Table::records(ctx);
        ctx.mt<TText>()["Create"] = eTText_create1;
        ctx.mt<TText>()["CreateCustom"] = eTText_create2;

        ctx.mt<TText>()["SetText"] = TText::setString;
        ctx.mt<TText>()["SetSize"] = TText::setCharacterSize;
        ctx.mt<TText>()["SetScale"] = static_cast<void (TText::*)(float, float)>(TText::setScale);
        ctx.mt<TText>()["SetPosition"] = static_cast<void (TText::*)(float, float)>(TText::setPosition);
        ctx.mt<TText>()["SetRotation"] = TText::setRotation;
        ctx.mt<TText>()["SetColor"] = eTText_setColor;
        ctx.mt<TText>()["SetStyle"] = TText::setStyle;

        ctx.mt<TText>()["GetText"] = TText::getString;
        ctx.mt<TText>()["GetStyle"] = TText::getStyle;
        ctx.mt<TText>()["GetPosition"] = eTText_getPosition;
        ctx.mt<TText>()["GetRotation"] = TText::getRotation;
        ctx.mt<TText>()["GetScale"] = eTText_getScale;
        ctx.mt<TText>()["GetColor"] = eTText_getColor;
        ctx.mt<TText>()["GetSize"] = TText::getCharacterSize;

        ctx.mt<TText>()["Move"] = static_cast<void (TText::*)(float, float)>(TText::move);
        ctx.mt<TText>()["Rotate"] = TText::rotate;
        ctx.mt<TText>()["Scale"] = static_cast<void (TText::*)(float, float)>(TText::scale);

        ctx.mt<TText>()["__gc"] = eTText_destroy;
        ctx.mt<TText>()["__index"] = ctx.mt<TText>();

        ctx.global["Text"] = eTText_create1;
        ctx.global["CustomText"] = eTText_create2;
        return ctx.ret();
    }


    Retval eTRect_create(Context& ctx) {
        if ((ctx.checkArgs<Table>(1) == false) && (ctx.args.size() != 0)) {
            throw exception("Wrong arguments: table or nil is expected.");
        }
        Table table = (ctx.checkArgs<Table>(1)) ? Table(ctx.args[0]) : Table(ctx);
        table["__index"] = table;
        table.mt() = ctx.global["TRect"];
        return ctx.ret(table);
    }
    void sTRect_get(Valref ref, TRect& rect) {
        if (ref.is<Table>() == false) {
            return;
        }
        Table table = ref;
        rect.height = table["height"].cast<int>();
        rect.left = table["left"].cast<int>();
        rect.top = table["top"].cast<int>();
        rect.width = table["width"].cast<int>();
    }
    Retval exportTRect(Context& ctx) {
        ctx.global["TRect"] = Table::records(ctx,
            "Create",       mkcf<eTRect_create>,

            "left",         0.f,            
            "top",          0.f,
            "width",        0.f,
            "height",       0.f
        );
        ctx.global["TRect"]["__index"] = ctx.global["TRect"];
        ctx.global["Rect"] = mkcf<eTRect_create>;
        return ctx.ret();
    }


    Retval eTImageSource_create(Context& ctx) {
        if ((ctx.checkArgs<Table>(1) == false) && (ctx.args.size() != 0)) {
            throw exception("Wrong arguments: table or nil is expected.");
        }
        Table table = (ctx.checkArgs<Table>(1)) ? Table(ctx.args[0]) : Table(ctx);
        table["__index"] = table;
        table.mt() = ctx.global["TImageSource"];
        return ctx.ret(table);
    }
    void sTImageSource_get(Valref ref, TImageSource& source) {
        if (ref.is<Table>() == false) {
            return;
        }
        Table table = ref;
        sTRect_get(Table(table["boundary"]), source.boundary);
        source.frame = table["frame"].cast<uint>();
        source.frameCount = table["frameCount"].cast<uint>();
        source.path = table["path"].cast<string>();
    }
    Retval exportTImageSource(Context& ctx) {
        ctx.global["TImageSource"] = Table::records(ctx,
            "Create",       mkcf<eTImageSource_create>,

            "path",         string(),
            "frame",        0u,
            "frameCount",   1u
        );
        ctx.global["TImageSource"]["__index"] = ctx.global["TImageSource"];
        ctx.runString("TImageSource.boundary = Rect()");
        ctx.global["ImageSource"] = mkcf<eTImageSource_create>;
        return ctx.ret();
    }


    LUAPP_ARG_CONVERT(::LogMessageImportance, { return (::LogMessageImportance)val.to<uint>(); })

    Retval exportDebugTools(Context& ctx) {
        ctx.global["LogMessageImportance"] = Table::records(ctx,
            "Undefined",    (uint)::LogMessageImportance::undefined,
            "Unimportant",  (uint)::LogMessageImportance::Unimportant,
            "Usual",        (uint)::LogMessageImportance::Usual,
            "Important",    (uint)::LogMessageImportance::Important,
            "Warning",      (uint)::LogMessageImportance::Warning,
            "Error",        (uint)::LogMessageImportance::Error,
            "Critical",     (uint)::LogMessageImportance::Critical
        );

        ctx.global["e_print"] = static_cast<
            void (*)(const TextString&,
                const TextString&,
                ::LogMessageImportance
            )>(GUI::Debug::logMessage);
        return ctx.ret();
    }


    void GUI::lua_binding::bindCore(State& state) {
        state.call(mkcf<exportDebugTools>);

        state.call(mkcf<exportWstring>);
        state.call(mkcf<exportVec2f>);
        state.call(mkcf<exportTSize>);
        state.call(mkcf<exportTCoordinate>);
        state.call(mkcf<exportTPadding>);
        state.call(mkcf<exportTColor>);
        state.call(mkcf<exportTFont>);
        state.call(mkcf<exportTText>);
        state.call(mkcf<exportTRect>);
        state.call(mkcf<exportTImageSource>);
    }
#endif //GUI_LUA_NO_CORE_BINDING


#if !defined(GUI_LUA_NO_WIDGET_BINDING)
    LUAPP_ARG_CONVERT(TWidgetSignal, { return static_cast<TWidgetSignal>(val.cast<LightUserData>()); })
    LUAPP_RV_CONVERT (TWidgetSignal, { return context.ret((LightUserData)val); })

    LUAPP_ARG_CONVERT(TWidgetSlot, { return static_cast<TWidgetSlot>(val.cast<LightUserData>()); })
    LUAPP_RV_CONVERT (TWidgetSlot, { return context.ret((LightUserData)val); })


    TWidgetRef eTWidgetRef_create(const TWidget& source) {
        return TWidgetRef(source);
    }
    void eTWidgetRef_destroy(TWidgetRef& self) {
        self.~__weak_ptr();
    }
    bool eTWidgetRef_expired(TWidgetRef& self) {
        return self.expired();
    }
    Retval exportTWidgetRef(Context& ctx) {
        ctx.mt<TWidgetRef>() = Table::records(ctx,
            "expired",      eTWidgetRef_expired,
            "FromObject",   eTWidgetRef_create,
            "ToObject",     TWidgetRef::lock,
            "__gc",         eTWidgetRef_destroy
        );
        ctx.mt<TWidgetRef>()["__index"] = ctx.mt<TWidgetRef>();
        return ctx.ret();
    }


    void eTWidget_destroy(TWidget& self) {
        self.~__shared_ptr();
    }  
    bool eTWidget_hasSignal(const TWidget& self, const SignalID& signal) {
        return self->HasSignal(signal);
    }
    bool eTWidget_hasSlot(const TWidget& self, const SignalID& slot) {
        return self->HasSlot(slot);
    }
    TWidgetSignal eTWidget_getSignal(TWidget& self, const SignalID& name) {
        return &self->GetSignal(name);
    }
    TWidgetSlot eTWidget_getSlot(TWidget& self, const SignalID& name) {
        return &self->GetSlot(name);
    }
    void eTWidget_connect(const TWidget& signalOwner, TWidgetSignal signal, const TWidget& slotOwner, const TWidgetSlot slot) {
        GUI::TWidget::Connect(signalOwner, *signal, slotOwner, *slot);
    }
    void eTWidget_disconnect(const TWidget& signalOwner, TWidgetSignal signal, const TWidget& slotOwner, const TWidgetSlot slot) {
        GUI::TWidget::Disconnect(signalOwner, *signal, slotOwner, *slot);
    }
    TWidgetRef eTWidget_getParent(TWidget& self) {
        return self->GetParent();
    }
    TWidget& eTWidget_setParent(TWidget& self, TWidgetRef& parent) {
        self->SetParent(parent);
        return self;
    }
    TWidgetRef eTWidget_findChild(TWidget& self, const GUI::TWidget::Name& key) {
        return self->FindChild(key);
    }
    TWidget eTWidget_removeChild(TWidget& self, const string& name) {
        return self->RemoveChild(name);
    }
    bool eTWidget_hasChild(const TWidget& self, const string& name) {
        return self->HasChild(name);
    }
    bool eTWidget_hasThisChild(const TWidget& self, const TWidget& child) {
        return self->HasChild(child);
    }
    void eTWidget_addChild(TWidget& self, TWidget& value) {
        self->AddChild(value);
    }
    bool eTWidget_hasChildren(const TWidget& self) {
        return self->HasChildren();
    }
    void eTWidget_removeChildren(TWidget& self) {
        self->RemoveChildren();
    }
    bool eTWidget_isVisible(const TWidget& self) {
        return self->IsVisible();
    }
    bool eTWidget_isShown(const TWidget& self) {
        return self->IsShown();
    }
    TWidget& eTWidget_show(TWidget& self) {
        self->Show();
        return self;
    }
    TWidget& eTWidget_hide(TWidget& self) {
        self->Hide();
        return self;
    }
    TWidget& eTWidget_setVisibility(TWidget& self, bool value) {
        self->SetVisibility(value);
        return self;
    }
    bool eTWidget_isMouseOver(const TWidget& self) {
        return self->IsMouseOver();
    }
    TSize eTWidget_getSize(const TWidget& self) {
        return self->GetSize();
    }
    TWidget& eTWidget_setSize(TWidget& self, const TSize& value) {
        self->SetSize(value);
        return self;
    }
    const TSize& eTWidget_getOwnSize(const TWidget& self) {
        return self->GetOwnSize();
    }
    TWidget& eTWidget_setPosition(TWidget& self, float x, float y) {
        self->SetPosition(x, y);
        return self;
    }
    const TCoordinate& eTWidget_getPosition(TWidget& self) {
        return self->GetPosition();
    }
    TWidget& eTWidget_setMargin(TWidget& self, const TPadding& value) {
        self->SetMargin(value);
        return self;
    }
    const TPadding& eTWidget_getMargin(const TWidget& self) {
        return self->GetMargin();
    }
    TPadding eTWidget_getInnerBorder(const TWidget& self) {
        return self->GetInnerBorder();
    }
    const string& eTWidget_getName(const TWidget& self) {
        return self->GetName();
    }
    Retval exportTWidget(Context& ctx) {
        ctx.mt<TWidget>() = Table::records(ctx);
        ctx.mt<TWidget>()["exists"] = static_cast<bool (TWidget::*)(void) const>(TWidget::operator bool);
        ctx.mt<TWidget>()["keySep"] = string { GUI::TWidget::keySep() };

        ctx.mt<TWidget>()["HasSignal"] = eTWidget_hasSignal;
        ctx.mt<TWidget>()["HasSlot"] = eTWidget_hasSlot;
        ctx.mt<TWidget>()["GetSignal"] = eTWidget_getSignal;
        ctx.mt<TWidget>()["GetSlot"] = eTWidget_getSlot;
        ctx.mt<TWidget>()["Connect"] = eTWidget_connect;
        ctx.mt<TWidget>()["Disconnect"] = eTWidget_disconnect;

        ctx.mt<TWidget>()["GetParent"] = eTWidget_getParent;
        ctx.mt<TWidget>()["SetParent"] = eTWidget_setParent;

        ctx.mt<TWidget>()["FindChild"] = eTWidget_findChild;
        ctx.mt<TWidget>()["AddChild"] = eTWidget_addChild;
        ctx.mt<TWidget>()["RemoveChild"] = eTWidget_removeChild;
        ctx.mt<TWidget>()["HasChild"] = eTWidget_hasChild;
        ctx.mt<TWidget>()["HasThisChild"] = eTWidget_hasThisChild;

        ctx.mt<TWidget>()["HasChildren"] = eTWidget_hasChildren;
        ctx.mt<TWidget>()["RemoveChildren"] = eTWidget_removeChildren;

        ctx.mt<TWidget>()["IsVisible"] = eTWidget_isVisible;
        ctx.mt<TWidget>()["Show"] = eTWidget_show;
        ctx.mt<TWidget>()["Hide"] = eTWidget_hide;
        ctx.mt<TWidget>()["SetVisibility"] = eTWidget_setVisibility;
        ctx.mt<TWidget>()["IsShown"] = eTWidget_isShown;

        ctx.mt<TWidget>()["IsMouseOver"] = eTWidget_isMouseOver;

        ctx.mt<TWidget>()["GetSize"] = eTWidget_getSize;
        ctx.mt<TWidget>()["GetOwnSize"] = eTWidget_getOwnSize;
        ctx.mt<TWidget>()["SetSize"] = eTWidget_setSize;

        ctx.mt<TWidget>()["SetPosition"] = eTWidget_setPosition;
        ctx.mt<TWidget>()["GetPosition"] = eTWidget_getPosition;

        ctx.mt<TWidget>()["SetMargin"] = eTWidget_setMargin;
        ctx.mt<TWidget>()["GetMargin"] = eTWidget_getMargin;
        ctx.mt<TWidget>()["GetInnerBorder"] = eTWidget_getInnerBorder;

        ctx.mt<TWidget>()["GetName"] = eTWidget_getName;

        ctx.mt<TWidget>()["GetRef"] = eTWidgetRef_create;

        ctx.mt<TWidget>()["__gc"] = eTWidget_destroy;
        ctx.mt<TWidget>()["__index"] = ctx.mt<TWidget>();

        ctx.global["TWidget"] = ctx.mt<TWidget>();
        return ctx.ret();
    }


    Retval exportTWidgetSignals(Context& ctx) {
        ctx.global["SignalID"] = Table::records(ctx,
            "ObjectVisibilityChanged", GUI::DefaultSignalID::ObjectVisibilityChanged,
            "ObjectShown",          GUI::DefaultSignalID::ObjectShown,
            "ObjectHidden",         GUI::DefaultSignalID::ObjectHidden,

            "ObjectTextChanged",    GUI::DefaultSignalID::ObjectTextChanged,
            "ObjectPositionChanged",GUI::DefaultSignalID::ObjectPositionChanged,
            "ObjectSizeChanged",    GUI::DefaultSignalID::ObjectSizeChanged,

            "ObjectEnabled",        GUI::DefaultSignalID::ObjectEnabled,
            "ObjectDisabled",       GUI::DefaultSignalID::ObjectDisabled,

            "MouseEntered", GUI::DefaultSignalID::MouseEntered,
            "MouseLeave",   GUI::DefaultSignalID::MouseLeave,
            "MouseClick",   GUI::DefaultSignalID::MouseClick,
            "MouseDown",    GUI::DefaultSignalID::MouseDown,
            "MouseUp",      GUI::DefaultSignalID::MouseUp
        );
        return ctx.ret();
    }


    Retval eTWidgetSource_create(Context& ctx) {
        if ((ctx.checkArgs<Table>(1) == false) && (ctx.args.size() != 0)) {
            throw exception("Wrong arguments: table or nil is expected.");
        }
        Table table = (ctx.checkArgs<Table>(1)) ? Table(ctx.args[0]) : Table(ctx);
        table["__index"] = table;
        table.mt() = ctx.global["TWidgetSource"];
        return ctx.ret(table);
    }
    void sTWidgetSource_get(Value ref, TWidgetSource& source) {
        if (ref.is<Table>() == false) {
            return;
        }
        Table table = ref;
        source.margin = table["margin"].cast<TPadding>();
        source.name = table["name"].cast<string>();
        source.position = table["position"].cast<TCoordinate>();
        source.show = table["show"].cast<bool>();
        source.size = table["size"].cast<TSize>();
    }
    Retval exportTWidgetSource(Context& ctx) {        
        ctx.global["TWidgetSource"] = Table::records(ctx,
            "create",       mkcf<eTWidgetSource_create>,

            "name",         string(),
            "position",     TCoordinate(),
            "size",         TSize(),
            "margin",       TPadding(),
            "show",         false
        );
        ctx.global["TWidgetSource"]["__index"] = ctx.global["TWidgetSource"];
        ctx.global["WidgetSource"] = mkcf<eTWidgetSource_create>;
        return ctx.ret();
    }

    void GUI::lua_binding::bindWidget(State& state) {
        state.call(mkcf<exportTWidgetSource>);
        state.call(mkcf<exportTWidget>);
        state.call(mkcf<exportTWidgetRef>);
        state.call(mkcf<exportTWidgetSignals>);
    }
#endif //GUI_LUA_NO_WIDGET_BINDING

#if !defined(GUI_LUA_NO_ABSTRACTWINDOW_BINDING)
    bool eTAbstractWindow_isEnabled(const TAbstractWindow& self) {
        return self->IsEnabled();
    }
    TAbstractWindow eTAbstractWindow_setEnabled(TAbstractWindow self, bool value) {
        self->SetEnabled(value);
        return self;
    }
    TAbstractWindow eTAbstractWindow_enable(TAbstractWindow self) {
        self->Enable();
        return self;
    }
    TAbstractWindow eTAbstractWindow_disable(TAbstractWindow self) {
        self->Disable();
        return self;
    }
    bool eTAbstractWindow_isMoveable(const TAbstractWindow& self) {
        return self->IsMoveable();
    }
    TAbstractWindow eTAbstractWindow_setMoveability(TAbstractWindow self, bool value) {
        self->SetMoveability(value);
        return self;
    }
    bool eTAbstractWindow_hasHeader(const TAbstractWindow& self) {
        return self->HasHeader();
    }
    float eTAbstractWindow_getHeaderHeight(const TAbstractWindow& self) {
        return self->GetHeaderHeight();
    }
    TAbstractWindow eTAbstractWindow_setHeaderHeight(TAbstractWindow self, float value) {
        self->SetHeaderHeight(value);
        return self;
    }
    const TextString& eTAbstractWindow_getTitle(const TAbstractWindow& self) {
        return self->GetTitle();
    }
    TAbstractWindow eTAbstractWindow_setTitle(TAbstractWindow self, const TextString& value) {
        self->SetTitle(value);
        return self;
    }
    const TFont& eTAbstractWindow_getTitleFont(const TAbstractWindow& self) {
        return self->GetTitleFont();
    }
    TAbstractWindow eTAbstractWindow_setTitleFont(TAbstractWindow self, const TFont& value) {
        self->SetTitleFont(value);
        return self;
    }
    const TColor& eTAbstractWindow_getTitleColor(const TAbstractWindow& self) {
        return self->GetTitleColor();
    }
    TAbstractWindow eTAbstractWindow_setTitleColor(TAbstractWindow self, const TColor& value) {
        self->SetTitleColor(value);
        return self;
    }
    const TColor& eTAbstractWindow_getHeaderColor(const TAbstractWindow& self) {
        return self->GetHeaderColor();
    }
    TAbstractWindow eTAbstractWindow_setHeaderColor(TAbstractWindow self, const TColor& value) {
        self->SetHeaderColor(value);
        return self;
    }
    const TColor& eTAbstractWindow_getColor(const TAbstractWindow& self) {
        return self->GetColor();
    }
    TAbstractWindow eTAbstractWindow_setColor(TAbstractWindow self, const TColor& value) {
        self->SetColor(value);
        return self;
    }
    bool eTAbstractWindow_hasImage(const TAbstractWindow& self) {
        return self->HasImage();
    }
    TAbstractWindow eTAbstractWindow_setImage(TAbstractWindow self, TImage value) {
        self->SetImage(std::move(*value));
        return self;
    }
    const TPadding& eTAbstractWindow_getInnerPadding(const TAbstractWindow& self) {
        return self->GetInnerPadding();
    }
    TAbstractWindow eTAbstractWindow_setInnerPadding(TAbstractWindow self, const TPadding& value) {
        self->SetInnerPadding(value);
        return self;
    }
    bool eTAbstractWindow_isResizable(const TAbstractWindow& self) {
        return self->IsResizable();
    }
    TAbstractWindow eTAbstractWindow_setMinSize(TAbstractWindow self, const TSize& value) {
        self->SetMinSize(value);
        return self;
    }
    TAbstractWindow eTAbstractWindow_setMaxSize(TAbstractWindow self, const TSize& value) {
        self->SetMaxSize(value);
        return self;
    }
    const TSize& eTAbstractWindow_getMinSize(const TAbstractWindow& self) {
        return self->GetMinSize();
    }
    const TSize& eTAbstractWindow_getMaxSize(const TAbstractWindow& self) {
        return self->GetMaxSize();
    }
    Retval exportTAbstractWindow(Context& ctx) {
        ctx.global["TAbstractWindow"] = Table::records(ctx);
        ctx.global["TAbstractWindow"]["IsEnabled"] = eTAbstractWindow_isEnabled;
        ctx.global["TAbstractWindow"]["SetEnabled"] = eTAbstractWindow_setEnabled;
        ctx.global["TAbstractWindow"]["Enable"] = eTAbstractWindow_enable;
        ctx.global["TAbstractWindow"]["Disable"] = eTAbstractWindow_disable;

        ctx.global["TAbstractWindow"]["IsMoveable"] = eTAbstractWindow_isMoveable;
        ctx.global["TAbstractWindow"]["SetMoveability"] = eTAbstractWindow_setMoveability;

        ctx.global["TAbstractWindow"]["HasHeader"] = eTAbstractWindow_hasHeader;
        ctx.global["TAbstractWindow"]["GetHeaderHeight"] = eTAbstractWindow_getHeaderHeight;
        ctx.global["TAbstractWindow"]["SetHeaderHeight"] = eTAbstractWindow_setHeaderHeight;
        ctx.global["TAbstractWindow"]["GetHeaderColor"] = eTAbstractWindow_getHeaderColor;
        ctx.global["TAbstractWindow"]["SetHeaderColor"] = eTAbstractWindow_setHeaderColor;
        ctx.global["TAbstractWindow"]["GetTitle"] = eTAbstractWindow_getTitle;
        ctx.global["TAbstractWindow"]["SetTitle"] = eTAbstractWindow_setTitle;
        ctx.global["TAbstractWindow"]["GetTitleFont"] = eTAbstractWindow_getTitleFont;
        ctx.global["TAbstractWindow"]["SetTitleFont"] = eTAbstractWindow_setTitleFont;
        ctx.global["TAbstractWindow"]["GetTitleColor"] = eTAbstractWindow_getTitleColor;
        ctx.global["TAbstractWindow"]["SetTitleColor"] = eTAbstractWindow_setTitleColor;

        ctx.global["TAbstractWindow"]["HasImage"] = eTAbstractWindow_hasImage;
        ctx.global["TAbstractWindow"]["SetImage"] = eTAbstractWindow_setImage;
        ctx.global["TAbstractWindow"]["GetColor"] = eTAbstractWindow_getColor;
        ctx.global["TAbstractWindow"]["SetColor"] = eTAbstractWindow_setColor;

        ctx.global["TAbstractWindow"]["GetInnerPadding"] = eTAbstractWindow_getInnerPadding;
        ctx.global["TAbstractWindow"]["SetInnerPadding"] = eTAbstractWindow_setInnerPadding;

        ctx.global["TAbstractWindow"]["IsResizable"] = eTAbstractWindow_isResizable;
        ctx.global["TAbstractWindow"]["GetMinSize"] = eTAbstractWindow_getMinSize;
        ctx.global["TAbstractWindow"]["SetMinSize"] = eTAbstractWindow_setMinSize;
        ctx.global["TAbstractWindow"]["GetMaxSize"] = eTAbstractWindow_getMaxSize;
        ctx.global["TAbstractWindow"]["SetMaxSize"] = eTAbstractWindow_setMaxSize;
        ctx.global["TAbstractWindow"]["__index"] = ctx.global["TAbstractWindow"];
        ctx.global["TAbstractWindow"].mt() = ctx.global["TWidget"];
        return ctx.ret();
    }

    Retval eTAbstractWindowSource_create(Context& ctx) {
        if ((ctx.checkArgs<Table>(1) == false) && (ctx.args.size() != 0)) {
            throw exception("Wrong arguments: table or nil is expected.");
        }
        Table table = (ctx.checkArgs<Table>(1)) ? Table(ctx.args[0]) : Table(ctx);
        table["__index"] = table;
        table.mt() = ctx.global["TAbstractWindowSource"];
        return ctx.ret(table);
    }
    void sTAbstractWindowSource_get(Valref ref, TAbstractWindowSource& source) {
        if (ref.is<Table>() == false) {
            return;
        }

        sTWidgetSource_get(ref, source);

        Table table = ref;
        source.enabled = table["enabled"].cast<bool>();
        source.allowMoving = table["allowMoving"].cast<bool>();

        source.headerHeight = table["headerHeight"].cast<float>();
        source.headerColor = table["headerColor"].cast<TColor>();
        source.headerText = table["headerText"].cast<TextString>();
        source.headerTextColor = table["headerTextColor"].cast<TColor>();

        source.color = table["color"].cast<TColor>();
        sTImageSource_get(Value(table["image"]), source.image);

        source.innerElementsPadding = table["innerElementsPadding"].cast<TPadding>();
        source.minSize = table["minSize"].cast<TSize>();
        source.maxSize = table["maxSize"].cast<TSize>();
    }
    Retval exportTAbstractWindowSource(Context& ctx) {
        ctx.global["TAbstractWindowSource"] = Table::records(ctx,
            "create",           mkcf<eTAbstractWindowSource_create>,

            "enabled",          true,
            "allowMoving",      false,

            "headerHeight",     0.f,
            "headerColor",		TColor(),
            "headerText",		TextString(),
            "headerTextColor",	TColor(),

            "color",            TColor(),

            "innerElementsPadding",TPadding(),
            "minSize",          TSize(),
            "maxSize",          TSize()
        );
        ctx.global["TAbstractWindowSource"]["__index"] = ctx.global["TAbstractWindowSource"];
        ctx.runString("TAbstractWindowSource.image = ImageSource()");
        ctx.global["TAbstractWindowSource"].mt() = ctx.global["TWidgetSource"];
        ctx.global["AbstractWindowSource"] = mkcf<eTAbstractWindowSource_create>;
        return ctx.ret();
    }

    void GUI::lua_binding::bindAbstractWindow(State& state) {
        state.call(mkcf<exportTAbstractWindowSource>);
        state.call(mkcf<exportTAbstractWindow>);
    }
#endif //GUI_LUA_NO_ABSTRACTWINDOW_BINDING

#if !defined(GUI_LUA_NO_WINDOW_BINDING)
    void sTWindowSource_get(Valref ref, TWindowSource& source) {
        if (ref.is<Table>() == false) {
            return;
        }
        sTAbstractWindowSource_get(ref, source);
    }


    Retval eTWindow_create(Context& ctx) {
        if (ctx.checkArgs<Table>(1) == false) {
            throw exception("Wrong arguments.");
        }
        TWindowSource source;
        sTWindowSource_get(ctx.args[0], source);
        TWidget window = std::make_shared<GUI::TWindow>(source);
        window->Initialize();
        return ctx.ret(window);
    }
    Retval exportTWindow(Context& ctx) {
        ctx.global["TWindow"] = Table::records(ctx,
            "create",       mkcf<eTWindow_create>
        );
        ctx.global["TWindow"]["__index"] = ctx.global["TWindow"];
        ctx.global["TWindow"].mt() = ctx.global["TAbstractWindow"];
        ctx.global["Window"] = eTWindow_create;
        return ctx.ret();
    }


    Retval eTWindowSource_create(Context& ctx) {
        if ((ctx.checkArgs<Table>(1) == false) && (ctx.args.size() != 0)) {
            throw exception("Wrong arguments: table or nil is expected.");
        }
        Table table = (ctx.checkArgs<Table>(1)) ? Table(ctx.args[0]) : Table(ctx);
        table["__index"] = table;
        table.mt() = ctx.global["TWindowSource"];
        return ctx.ret(table);
    }
    Retval exportTWindowSource(Context& ctx) {
        ctx.global["TWindowSource"] = Table::records(ctx,
            "create",       mkcf<eTWindowSource_create>
        );
        ctx.global["TWindowSource"]["__index"] = ctx.global["TWindowSource"];
        ctx.global["TWindowSource"].mt() = ctx.global["TAbstractWindowSource"];
        ctx.global["WindowSource"] = mkcf<eTWindowSource_create>;
        return ctx.ret();
    }

    void GUI::lua_binding::bindWindow(State &state) {
        state.call(mkcf<exportTWindowSource>);
        state.call(mkcf<exportTWindow>);
    }
#endif //GUI_LUA_NO_WINDOW_BINDING

#if !defined(GUI_LUA_NO_TRANSPARENTWINDOW_BINDING)
    void sTTransparentWindowSource_get(Valref ref, TTransparentWindowSource& source) {
        if (ref.is<Table>() == false) {
            return;
        }
        sTWindowSource_get(ref, source);

        Table table = ref;
        source.thresholdOpacity = table["thresholdOpacity"].cast<double>();
        source.minOpacity = table["minOpacity"].cast<double>();
        source.maxOpacity = table["maxOpacity"].cast<double>();
        source.opacityChangingSpeed = table["opacityChangingSpeed"].cast<double>();
    }


    Retval eTTransparentWindow_create(Context& ctx) {
        if (ctx.checkArgs<Table>(1) == false) {
            throw exception("Wrong arguments.");
        }
        TTransparentWindowSource source;
        sTTransparentWindowSource_get(ctx.args[0], source);
        TWidget widget = std::make_shared<GUI::TTransparentWindow>(source);
        widget->Initialize();
        return ctx.ret(widget);
    }
    TTransparentWindow eTTransparentWindow_setThresholdOpacity(TTransparentWindow self, double value) {
        self->SetThresholdOpacity(value);
        return self;
    }
    double eTTransparentWindow_GetThresholdOpacity(const TTransparentWindow& self) {
        return self->GetThresholdOpacity();
    }
    TTransparentWindow eTTransparentWindow_SetMinOpacity(TTransparentWindow self, double value) {
        self->SetMinOpacity(value);
        return self;
    }
    TTransparentWindow eTTransparentWindow_SetMaxOpacity(TTransparentWindow self, double value) {
        self->SetMaxOpacity(value);
        return self;
    }
    double eTTransparentWindow_GetMinOpacity(const TTransparentWindow& self) {
        return self->GetMinOpacity();
    }
    double eTTransparentWindow_GetMaxOpacity(const TTransparentWindow& self) {
        return self->GetMaxOpacity();
    }
    Retval exportTTransparentWindow(Context& ctx) {
        ctx.global["TTransparentWindow"] = Table::records(ctx,
            "create",       mkcf<eTTransparentWindow_create>,
            "SetThresholdOpacity", eTTransparentWindow_setThresholdOpacity,
            "GetThresholdOpacity", eTTransparentWindow_GetThresholdOpacity,
            "SetMinOpacity",eTTransparentWindow_SetMinOpacity,
            "GetMinOpacity",eTTransparentWindow_GetMinOpacity,
            "SetMaxOpacity",eTTransparentWindow_SetMaxOpacity,
            "GetMaxOpacity",eTTransparentWindow_GetMaxOpacity
        );
        ctx.global["TTransparentWindow"]["__index"] = ctx.global["TTransparentWindow"];
        ctx.global["TTransparentWindow"].mt() = ctx.global["TWindow"];
        ctx.global["TransparentWindow"] = eTTransparentWindow_create;
        return ctx.ret();
    }


    Retval eTTransparentWindowSource_create(Context& ctx) {
        if ((ctx.checkArgs<Table>(1) == false) && (ctx.args.size() != 0)) {
            throw exception("Wrong arguments: table or nil is expected.");
        }
        Table table = (ctx.checkArgs<Table>(1)) ? Table(ctx.args[0]) : Table(ctx);
        table["__index"] = table;
        table.mt() = ctx.global["TTransparentWindowSource"];
        return ctx.ret(table);
    }
    Retval exportTTransparentWindowSource(Context& ctx) {
        ctx.global["TTransparentWindowSource"] = Table::records(ctx,
            "create",       mkcf<eTTransparentWindowSource_create>,
            "minOpacity",   0.3,
            "maxOpacity",   1.0,
            "opacityChangingSpeed", 0.1,
            "thresholdOpacity", 0.5
        );
        ctx.global["TTransparentWindowSource"]["__index"] = ctx.global["TTransparentWindowSource"];
        ctx.global["TTransparentWindowSource"].mt() = ctx.global["TWindowSource"];
        ctx.global["TransparentWindowSource"] = mkcf<eTTransparentWindowSource_create>;
        return ctx.ret();
    }

    void GUI::lua_binding::bindTransparentWindow(State &state) {
        state.call(mkcf<exportTTransparentWindowSource>);
        state.call(mkcf<exportTTransparentWindow>);
    }
#endif //GUI_LUA_NO_WINDOW_BINDING

#if !defined(GUI_LUA_NO_UIPARENT_BINDING)
    TUIParent eGetUIParent() {
        return app()->getUI().getUIParent();
    }
    TUIParent eTUIParent_setChildrenVisibility(TUIParent self, bool value) {
        self->SetChildrenVisibility(value);
        return self;
    }
    void eTUIParent_showChildren(TUIParent self) {
        self->ShowChildren();
    }
    void eTUIParent_hideChildren(TUIParent self) {
        self->HideChildren();
    }
    Retval exportTUIParent(Context& ctx) {
        ctx.global["UIParent"] = eGetUIParent;
        ctx.global["TUIParent"] = Table::records(ctx,
            "SetChildrenVisibility",    eTUIParent_setChildrenVisibility,
            "ShowChildren",             eTUIParent_showChildren,
            "HideChildren",             eTUIParent_hideChildren
        );
        ctx.global["TUIParent"]["__index"] = ctx.global["TUIParent"];
        ctx.global["TUIParent"].mt() = ctx.global["TWidget"];
        return ctx.ret();
    }

    void GUI::lua_binding::bindUIParent(State& state) {
        state.call(mkcf<exportTUIParent>);
    }
#endif //GUI_LUA_NO_UIPARENT_BINDING

#if !defined(GUI_LUA_NO_ABSTRACTBUTTON_BINDING)
    bool eTAbstractButton_isEnabled(const TAbstractButton& self) {
        return self->IsEnabled();
    }
    TAbstractButton eTAbstractButton_enable(TAbstractButton self) { 
        self->Enable();
        return self;
    }
    TAbstractButton eTAbstractButton_disable(TAbstractButton self) { 
        self->Disable();
        return self;
    }
    const TColor& eTAbstractButton_getColor(const TAbstractButton& self) {
        return self->GetColor();
    }
    TAbstractButton eTAbstractButton_setColor(TAbstractButton self, const TColor& value) {
        self->SetColor(value);
        return self; 
    }
    bool eTAbstractButton_hasImage(const TAbstractButton& self) {
        return self->HasImage();
    }
    TAbstractButton eTAbstractButton_setImage(TAbstractButton self, TImage value) { 
        self->SetImage(std::move(*value));
        return self;
    }
    const TextString& eTAbstractButton_getText(const TAbstractButton& self) {
        return self->GetText();
    }
    TAbstractButton  eTAbstractButton_setText(TAbstractButton self, const TextString& value) { 
        self->SetText(value);
        return self;
    }
    const TFont& eTAbstractButton_getFont(const TAbstractButton& self) {
        return self->GetFont();
    }
    TAbstractButton  eTAbstractButton_setFont(TAbstractButton self, const TFont& value) { 
        self->SetFont(value);
        return self;
    }
    const TColor& eTAbstractButton_getFontColor(const TAbstractButton& self) {
        return self->GetFontColor(); 
    }
    TAbstractButton  eTAbstractButton_setFontColor(TAbstractButton self, const TColor& value) { 
        self->SetFontColor(value);
        return self;
    }
    Retval exportTAbstractButton(Context& ctx) {
        ctx.global["TAbstractButton"] = Table::records(ctx);
        ctx.global["TAbstractButton"]["__index"] = ctx.global["TAbstractButton"];
        ctx.global["TAbstractButton"].mt() = ctx.global["TWidget"];
        ctx.global["TAbstractButton"]["IsEnabled"] = eTAbstractButton_isEnabled;
        ctx.global["TAbstractButton"]["Enable"] = eTAbstractButton_enable;
        ctx.global["TAbstractButton"]["Disable"] = eTAbstractButton_disable;

        ctx.global["TAbstractButton"]["GetColor"] = eTAbstractButton_getColor;
        ctx.global["TAbstractButton"]["SetColor"] = eTAbstractButton_setColor;

        ctx.global["TAbstractButton"]["HasImage"] = eTAbstractButton_hasImage;
        ctx.global["TAbstractButton"]["SetImage"] = eTAbstractButton_setImage;

        ctx.global["TAbstractButton"]["GetText"] = eTAbstractButton_getText;
        ctx.global["TAbstractButton"]["SetText"] = eTAbstractButton_setText;

        ctx.global["TAbstractButton"]["GetFont"] = eTAbstractButton_getFont;
        ctx.global["TAbstractButton"]["SetFont"] = eTAbstractButton_setFont;

        ctx.global["TAbstractButton"]["GetFontColor"] = eTAbstractButton_getFontColor;
        ctx.global["TAbstractButton"]["SetFontColor"] = eTAbstractButton_setFontColor;

        return ctx.ret();
    }


    Retval eTAbstractButtonSource_create(Context& ctx) {
        if ((ctx.checkArgs<Table>(1) == false) && (ctx.args.size() != 0)) {
            throw exception("Wrong arguments: table or nil is expected.");
        }
        Table table = (ctx.checkArgs<Table>(1)) ? Table(ctx.args[0]) : Table(ctx);
        table["__index"] = table;
        table.mt() = ctx.global["TAbstractButtonSource"];
        return ctx.ret(table);
    }
    void sTAbstractButtonSource_get(Valref ref, TAbstractButtonSource& source) {
        if (ref.is<Table>() == false) {
            return;
        }

        sTWidgetSource_get(ref, source);

        Table table = ref;

        source.enabled = table["enabled"].cast<bool>();
        source.text = table["text"].cast<TextString>();
        source.textPosition = table["textPosition"].cast<TCoordinate>();
        source.textColor = table["textColor"].cast<TColor>();
        source.font = table["font"].cast<TFont>();
        source.color = table["color"].cast<TColor>();
        sTImageSource_get(Value(table["image"]), source.image);
    }
    Retval exportTAbstractButtonSource(Context& ctx) {
        ctx.global["TAbstractButtonSource"] = Table::records(ctx,
            "create",           mkcf<eTAbstractButtonSource_create>,
            "enabled",          false,
            "text",             TextString(),
            "textPosition",     TCoordinate(),
            "textColor",        TColor(),
            "font",             TFont(),
            "color",            TColor()
        );
        ctx.global["TAbstractButtonSource"]["__index"] = ctx.global["TAbstractButtonSource"];
        ctx.runString("TAbstractButtonSource.image = ImageSource()");
        ctx.global["TAbstractButtonSource"].mt() = ctx.global["TWidgetSource"];
        ctx.global["AbstractButtonSource"] = mkcf<eTAbstractButtonSource_create>;
        return ctx.ret();
    }


    void GUI::lua_binding::bindAbstractButton(State& state) {
        state.call(mkcf<exportTAbstractButtonSource>);
        state.call(mkcf<exportTAbstractButton>);
    }
#endif //GUI_LUA_NO_ABSTRACTBUTTON_BINDING

#if !defined(GUI_LUA_NO_PUSHBUTTON_BINDING)
    void sTPushButtonSource_get(Valref ref, TPushButtonSource& source) {
        if (ref.is<Table>() == false) {
            return;
        }
        sTAbstractButtonSource_get(ref, source);

        Table table = ref;
        //source.buttonClick = table["callback"].cast<string>();
    }


    Retval eTPushButton_create(Context& ctx) {
        if (ctx.checkArgs<Table>(1) == false) {
            throw exception("Wrong arguments.");
        }
        TPushButtonSource source;
        sTPushButtonSource_get(ctx.args[0], source);
        TWidget widget = std::make_shared<GUI::TPushButton>(source);
        widget->Initialize();
        return ctx.ret(widget);
    }
    Retval exportTPushButton(Context& ctx) {
        ctx.global["TPushButton"] = Table::records(ctx,
            "create",       mkcf<eTPushButton_create>
        );
        ctx.global["TPushButton"]["__index"] = ctx.global["TPushButton"];
        ctx.global["TPushButton"].mt() = ctx.global["TAbstractButton"];
        ctx.global["PushButton"] = eTPushButton_create;
        return ctx.ret();
    }


    Retval eTPushButtonSource_create(Context& ctx) {
        if ((ctx.checkArgs<Table>(1) == false) && (ctx.args.size() != 0)) {
            throw exception("Wrong arguments: table or nil is expected.");
        }
        Table table = (ctx.checkArgs<Table>(1)) ? Table(ctx.args[0]) : Table(ctx);
        table["__index"] = table;
        table.mt() = ctx.global["TPushButtonSource"];
        return ctx.ret(table);
    }
    Retval exportTPushButtonSource(Context& ctx) {
        ctx.global["TPushButtonSource"] = Table::records(ctx,
            "create",       mkcf<eTPushButtonSource_create>,
            "callback",     string()
        );
        ctx.global["TPushButtonSource"]["__index"] = ctx.global["TPushButtonSource"];
        ctx.global["TPushButtonSource"].mt() = ctx.global["TAbstractButtonSource"];
        ctx.global["PushButtonSource"] = mkcf<eTPushButtonSource_create>;
        return ctx.ret();
    }

    void GUI::lua_binding::bindPushButton(State &state) {
        state.call(mkcf<exportTPushButtonSource>);
        state.call(mkcf<exportTPushButton>);
    }    
#endif //GUI_LUA_NO_PUSHBUTTON_BINDING

#if !defined(GUI_LUA_NO_ABSTRACTTEXTBOX_BINDING)
    const TextString& eTAbstractTextBox_getText(const TAbstractTextBox& self) {
        return self->GetText();
    }
    TAbstractTextBox eTAbstractTextBox_setText(TAbstractTextBox self, const TextString& value) {
        self->SetText(value);
        return self;
    }
    const TColor& eTAbstractTextBox_getColor(const TAbstractTextBox& self) {
        return self->GetColor();
    }
    TAbstractTextBox eTAbstractTextBox_setColor(TAbstractTextBox self, const TColor& value) {
        self->SetColor(value);
        return self;
    }
    bool eTAbstractTextBox_isResizable(const TAbstractTextBox& self) {
        return self->IsResizable();
    }
    TAbstractTextBox eTAbstractTextBox_setMinSize(TAbstractTextBox self, const TSize& value) {
        self->SetMinSize(value);
        return self;
    }
    TAbstractTextBox eTAbstractTextBox_setMaxSize(TAbstractTextBox self, const TSize& value) {
        self->SetMaxSize(value);
        return self;
    }
    const TSize& eTAbstractTextBox_getMinSize(const TAbstractTextBox& self) {
        return self->GetMinSize();
    }
    const TSize& eTAbstractTextBox_getMaxSize(const TAbstractTextBox& self) {
        return self->GetMaxSize();
    } 
    bool eTAbstractTextBox_isEditable(const TAbstractTextBox& self) {
        return self->IsEditable();
    }
    TAbstractTextBox eTAbstractTextBox_setEditable(TAbstractTextBox self, bool value) {
        self->SetEditable(value);
        return self;
    }
    float eTAbstractTextBox_getBorderSize(const TAbstractTextBox& self) {
        return self->GetBorderSize();
    }
    TAbstractTextBox eTAbstractTextBox_setBorderSize(TAbstractTextBox self, float value) {
        self->SetBorderSize(value);
        return self;
    }
    const TFont& eTAbstractTextBox_getFont(const TAbstractTextBox& self) {
        return self->GetFont();
    }
    TAbstractTextBox eTAbstractTextBox_setFont(TAbstractTextBox self, const TFont& value) {
        self->SetFont(value);
        return self;
    }
    Retval exportTAbstractTextBox(Context& ctx) {
        ctx.global["TAbstractTextBox"] = Table::records(ctx);
        ctx.global["TAbstractTextBox"]["__index"] = ctx.global["TAbstractTextBox"];
        ctx.global["TAbstractTextBox"].mt() = ctx.global["TWidget"];

        ctx.global["TAbstractTextBox"]["GetText"] = eTAbstractTextBox_getText;
        ctx.global["TAbstractTextBox"]["SetText"] = eTAbstractTextBox_setText;

        ctx.global["TAbstractTextBox"]["GetColor"] = eTAbstractTextBox_getColor;
        ctx.global["TAbstractTextBox"]["SetColor"] = eTAbstractTextBox_setColor;

        ctx.global["TAbstractTextBox"]["IsResizable"] = eTAbstractTextBox_isResizable;
        ctx.global["TAbstractTextBox"]["SetMinSize"] = eTAbstractTextBox_setMinSize;
        ctx.global["TAbstractTextBox"]["SetMaxSize"] = eTAbstractTextBox_setMaxSize;
        ctx.global["TAbstractTextBox"]["GetMinSize"] = eTAbstractTextBox_getMinSize;
        ctx.global["TAbstractTextBox"]["GetMaxSize"] = eTAbstractTextBox_getMaxSize;

        ctx.global["TAbstractTextBox"]["IsEditable"] = eTAbstractTextBox_isEditable;
        ctx.global["TAbstractTextBox"]["SetEditable"] = eTAbstractTextBox_setEditable;

        ctx.global["TAbstractTextBox"]["GetBorderSize"] = eTAbstractTextBox_getBorderSize;
        ctx.global["TAbstractTextBox"]["SetBorderSize"] = eTAbstractTextBox_setBorderSize;

        ctx.global["TAbstractTextBox"]["GetFont"] = eTAbstractTextBox_getFont;
        ctx.global["TAbstractTextBox"]["SetFont"] = eTAbstractTextBox_setFont;
        return ctx.ret();
    }


    Retval eTAbstractTextBoxSource_create(Context& ctx) {
        if ((ctx.checkArgs<Table>(1) == false) && (ctx.args.size() != 0)) {
            throw exception("Wrong arguments: table or nil is expected.");
        }
        Table table = (ctx.checkArgs<Table>(1)) ? Table(ctx.args[0]) : Table(ctx);
        table["__index"] = table;
        table.mt() = ctx.global["TAbstractTextBoxSource"];
        return ctx.ret(table);
    }
    void sTAbstractTextBoxSource_get(Valref ref, TAbstractTextBoxSource& source) {
        if (ref.is<Table>() == false) {
            return;
        }

        sTWidgetSource_get(ref, source);

        Table table = ref;
        source.text = table["text"].cast<TextString>();
        source.textPosition = table["textPosition"].cast<TCoordinate>();
        source.textColor = table["textColor"].cast<TColor>();
        source.font = table["font"].cast<TFont>();
        source.color = table["color"].cast<TColor>();
        source.maxSize = table["maxSize"].cast<TSize>();
        source.minSize = table["minSize"].cast<TSize>();
        source.allowEdit = table["editable"].cast<bool>();
        source.borderSize = table["borderSize"].cast<float>();
        source.borderColor = table["borderColor"].cast<TColor>();
    }
    Retval exportTAbstractTextBoxSource(Context& ctx) {
        ctx.global["TAbstractTextBoxSource"] = Table::records(ctx,
            "create",           mkcf<eTAbstractTextBoxSource_create>,
            "text",             TextString(),
            "textPosition",     TCoordinate(),
            "textColor",        TColor(),
            "font",             TFont(),
            "color",            TColor(),
            "minSize",          TSize(),
            "maxSize",          TSize(),
            "editable",         false,
            "borderSize",       0.f,
            "borderColor",      TColor()
        );
        ctx.global["TAbstractTextBoxSource"]["__index"] = ctx.global["TAbstractTextBoxSource"];
        ctx.global["TAbstractTextBoxSource"].mt() = ctx.global["TWidgetSource"];
        ctx.global["AbstractTextBoxSource"] = mkcf<eTAbstractTextBoxSource_create>;
        return ctx.ret();
    }


    void GUI::lua_binding::bindAbstractTextBox(State& state) {
        state.call(mkcf<exportTAbstractTextBoxSource>);
        state.call(mkcf<exportTAbstractTextBox>);
    }
#endif //GUI_LUA_NO_ABSTRACTTEXTBOX_BINDING

#if !defined(GUI_LUA_NO_SIMPLETEXTBOX_BINDING)
    void sTSimpleTextBoxSource_get(Valref ref, TSimpleTextBoxSource& source) {
        if (ref.is<Table>() == false) {
            return;
        }
        sTAbstractTextBoxSource_get(ref, source);
    }


    Retval eTSimpleTextBox_create(Context& ctx) {
        if (ctx.checkArgs<Table>(1) == false) {
            throw exception("Wrong arguments.");
        }
        TSimpleTextBoxSource source;
        sTSimpleTextBoxSource_get(ctx.args[0], source);
        TWidget widget = std::make_shared<GUI::TSimpleTextBox>(source);
        widget->Initialize();
        return ctx.ret(widget);
    }
    Retval exportTSimpleTextBox(Context& ctx) {
        ctx.global["TSimpleTextBox"] = Table::records(ctx,
            "create",       mkcf<eTSimpleTextBox_create>
        );
        ctx.global["TSimpleTextBox"]["__index"] = ctx.global["TSimpleTextBox"];
        ctx.global["TSimpleTextBox"].mt() = ctx.global["TAbstractTextBox"];
        ctx.global["SimpleTextBox"] = eTSimpleTextBox_create;
        return ctx.ret();
    }


    Retval eTSimpleTextBoxSource_create(Context& ctx) {
        if ((ctx.checkArgs<Table>(1) == false) && (ctx.args.size() != 0)) {
            throw exception("Wrong arguments: table or nil is expected.");
        }
        Table table = (ctx.checkArgs<Table>(1)) ? Table(ctx.args[0]) : Table(ctx);
        table["__index"] = table;
        table.mt() = ctx.global["TSimpleTextBoxSource"];
        return ctx.ret(table);
    }
    Retval exportTSimpleTextBoxSource(Context& ctx) {
        ctx.global["TSimpleTextBoxSource"] = Table::records(ctx,
            "create",       mkcf<eTSimpleTextBoxSource_create>
        );
        ctx.global["TSimpleTextBoxSource"]["__index"] = ctx.global["TSimpleTextBoxSource"];
        ctx.global["TSimpleTextBoxSource"].mt() = ctx.global["TAbstractTextBoxSource"];
        ctx.global["SimpleTextBoxSource"] = mkcf<eTSimpleTextBoxSource_create>;
        return ctx.ret();
    }

    void GUI::lua_binding::bindSimpleTextBox(State &state) {
        state.call(mkcf<exportTSimpleTextBoxSource>);
        state.call(mkcf<exportTSimpleTextBox>);
    }
#endif //GUI_LUA_NO_SIMPLETEXTBOX_BINDING

#if !defined(GUI_LUA_NO_RICHTEXTBOX_BINDING)
    void sTRichTextBoxSeparators_get(Valref ref, TRichTextBoxSeparators& source) {
        if (ref.is<Table>() == false) {
            return;
        }

        Table table = ref;
        for (auto i = 0u, iend = table.len().cast<uint>(); i != iend; ++i) {
            source.emplace_back(std::move(table[i].cast<TextString>()));
        }
    }
    void sTRichTextBoxSource_get(Valref ref, TRichTextBoxSource& source) {
        if (ref.is<Table>() == false) {
            return;
        }
        sTAbstractTextBoxSource_get(ref, source);

        Table table = ref;
        sTRichTextBoxSeparators_get(Table(table["separators"]), source.separators);
    }


    Retval eTRichTextBox_create(Context& ctx) {
        if (ctx.checkArgs<Table>(1) == false) {
            throw exception("Wrong arguments.");
        }
        TRichTextBoxSource source;
        sTRichTextBoxSource_get(ctx.args[0], source);
        TWidget widget = std::make_shared<GUI::TRichTextBox>(source);
        widget->Initialize();
        return ctx.ret(widget);
    }
    Retval exportTRichTextBox(Context& ctx) {
        ctx.global["TRichTextBox"] = Table::records(ctx,
            "create",       mkcf<eTRichTextBox_create>
        );
        ctx.global["TRichTextBox"]["__index"] = ctx.global["TRichTextBox"];
        ctx.global["TRichTextBox"].mt() = ctx.global["TAbstractTextBox"];
        ctx.global["RichTextBox"] = eTRichTextBox_create;
        return ctx.ret();
    }


    Retval eTRichTextBoxSource_create(Context& ctx) {
        if ((ctx.checkArgs<Table>(1) == false) && (ctx.args.size() != 0)) {
            throw exception("Wrong arguments: table or nil is expected.");
        }
        Table table = (ctx.checkArgs<Table>(1)) ? Table(ctx.args[0]) : Table(ctx);
        table["__index"] = table;
        table.mt() = ctx.global["TRichTextBoxSource"];
        return ctx.ret(table);
    }
    Retval exportTRichTextBoxSource(Context& ctx) {
        ctx.global["TRichTextBoxSource"] = Table::records(ctx,
            "create",       mkcf<eTRichTextBoxSource_create>
        );
        ctx.global["TRichTextBoxSource"]["separators"] = Table::records(ctx);
        ctx.global["TRichTextBoxSource"]["__index"] = ctx.global["TRichTextBoxSource"];        
        ctx.global["TRichTextBoxSource"].mt() = ctx.global["TAbstractTextBoxSource"];
        ctx.global["RichTextBoxSource"] = mkcf<eTRichTextBoxSource_create>;
        return ctx.ret();
    }

    void GUI::lua_binding::bindRichTextBox(State &state) {
        state.call(mkcf<exportTRichTextBoxSource>);
        state.call(mkcf<exportTRichTextBox>);
    }
#endif //GUI_LUA_NO_RICHTEXTBOX_BINDING

#if !defined(GUI_LUA_NO_IMAGEBOX_BINDING)
    void sTImageBoxSource_get(Valref ref, TImageBoxSource& source) {
        if (ref.is<Table>() == false) {
            return;
        }
        sTWidgetSource_get(ref, source);

        Table table = ref;
        source.color = table["color"].cast<TColor>();
        sTImageSource_get(Table(table["imageSource"]), source.image);
    }

    const TColor& eTImageBox_getColor(const TImageBox& self) {
        return self->GetColor();
    }
    TImageBox eTImageBox_setColor(TImageBox self, const TColor& value) {
        self->SetColor(value);
        return self;
    }
    bool eTImageBox_hasImage(const TImageBox& self) {
        return self->HasImage();
    }
    TImageBox eTImageBox_setImage(TImageBox self, TImage value) {
        self->SetImage(std::move(*value));
        return self;
    }
    Retval eTImageBox_create(Context& ctx) {
        if (ctx.checkArgs<Table>(1) == false) {
            throw exception("Wrong arguments.");
        }
        TImageBoxSource source;
        sTImageBoxSource_get(ctx.args[0], source);
        TWidget widget = std::make_shared<GUI::TImageBox>(source);
        widget->Initialize();
        return ctx.ret(widget);
    }
    Retval exportTImageBox(Context& ctx) {
        ctx.global["TImageBox"] = Table::records(ctx,
            "create",       mkcf<eTImageBox_create>
        );
        ctx.global["TImageBox"]["__index"] = ctx.global["TImageBox"];
        ctx.global["TImageBox"].mt() = ctx.global["TWidget"];

        ctx.global["TImageBox"]["GetColor"] = eTImageBox_getColor;
        ctx.global["TImageBox"]["SetColor"] = eTImageBox_setColor;

        ctx.global["TImageBox"]["HasImage"] = eTImageBox_hasImage;
        ctx.global["TImageBox"]["SetImage"] = eTImageBox_setImage;

        ctx.global["ImageBox"] = eTImageBox_create;
        return ctx.ret();
    }


    Retval eTImageBoxSource_create(Context& ctx) {
        if ((ctx.checkArgs<Table>(1) == false) && (ctx.args.size() != 0)) {
            throw exception("Wrong arguments: table or nil is expected.");
        }
        Table table = (ctx.checkArgs<Table>(1)) ? Table(ctx.args[0]) : Table(ctx);
        table["__index"] = table;
        table.mt() = ctx.global["TImageBoxSource"];
        return ctx.ret(table);
    }
    Retval exportTImageBoxSource(Context& ctx) {
        ctx.global["TImageBoxSource"] = Table::records(ctx,
            "create",       mkcf<eTImageBoxSource_create>,
            "color",        TColor()
        );
        ctx.global["TImageBoxSource"]["__index"] = ctx.global["TImageBoxSource"];
        ctx.runString("TImageBoxSource.imageSource = ImageSource()");
        ctx.global["TImageBoxSource"].mt() = ctx.global["TWidgetSource"];
        ctx.global["ImageBoxSource"] = mkcf<eTImageBoxSource_create>;
        return ctx.ret();
    }

    void GUI::lua_binding::bindImageBox(State &state) {
        state.call(mkcf<exportTImageBoxSource>);
        state.call(mkcf<exportTImageBox>);
    }
#endif


void GUI::lua_binding::bindToLUA(State& state) {
    GUI::lua_binding::bindCore(state);
    GUI::lua_binding::bindWidget(state);
    GUI::lua_binding::bindUIParent(state);
    
    GUI::lua_binding::bindAbstractWindow(state);
    GUI::lua_binding::bindWindow(state);
    GUI::lua_binding::bindTransparentWindow(state);

    GUI::lua_binding::bindAbstractButton(state);
    GUI::lua_binding::bindPushButton(state);

    GUI::lua_binding::bindAbstractTextBox(state);
    GUI::lua_binding::bindSimpleTextBox(state);
    GUI::lua_binding::bindRichTextBox(state);

    GUI::lua_binding::bindImageBox(state);
}
