#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include "widget.h"
#include "abstractbutton.h"
#include <functional>


BEGIN_GUI

struct TPushButtonSource : TAbstractButtonSource
{
    using Callback = std::function<void (void**)>;
    Callback buttonClick;
};

class TPushButton : public TAbstractButton
{
public:
    using Callback = TPushButtonSource::Callback;

    TPushButton(const TPushButtonSource& source);
    TPushButton(const TPushButton& other) = delete;
    TPushButton& operator=(const TPushButton& other) = delete;
    ~TPushButton() = default;

private:
    typedef TAbstractButton parent_type;
protected:
    static const TColorModifier COLOR_MODIFIER_HOVER;
    static const TColorModifier COLOR_MODIFIER_NORMAL;
    static const TColorModifier COLOR_MODIFIER_DISABLED;


    Callback buttonClick_impl;


    virtual void _draw(TRenderTarget& target) override;

    virtual void _OnClick();
    virtual void _OnHover();
    virtual void _OnMouseLeave();
    virtual void _OnDisabled();
    virtual void _OnEnabled();
};

END_GUI

#endif // PUSHBUTTON_H
