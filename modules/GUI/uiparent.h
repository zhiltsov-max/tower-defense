#ifndef UIPARENT_H
#define UIPARENT_H

#include "gui_main.h"
#include "menuobject.h"

BEGIN_GUI

struct TUIParentSource : TMenuObjectSource
{
    TUIParentSource() :        
        TMenuObjectSource()
    {
        name = TGUISettings::DEFAULT_UIPARENT_NAME;
    }
};

class TUIParent : public TMenuObject
{
public:
    TUIParent(const TUIParentSource& source);
    TUIParent(const TUIParent& other) = delete;
    TUIParent& operator=(const TUIParent& other) = delete;
    ~TUIParent() = default;

    virtual bool IsVisible() const override;

    virtual void SetParent(const TMenuObjectWeakRef& value) override;

    void SetChildrenVisibility(bool value) const;
    void ShowChildren();
    void HideChildren();

    virtual bool IsMouseOver() const override;
private:
    typedef TMenuObject parent_t;
protected:
    virtual void _draw(TRenderTarget& target) override;
    virtual void _update() override;
};

END_GUI

#endif // UIPARENT_H
