#ifndef UIPARENT_H
#define UIPARENT_H

#include "gui_main.h"
#include "widget.h"

BEGIN_GUI

struct TUIParentSource : TWidgetSource
{
    TUIParentSource() :        
        TWidgetSource()
    {
        name = TGUISettings::DEFAULT_UIPARENT_NAME;
    }
};

class TUIParent : public TWidget
{
public:
    TUIParent(const TUIParentSource& source);
    TUIParent(const TUIParent& other) = delete;
    TUIParent& operator=(const TUIParent& other) = delete;
    ~TUIParent() = default;

    virtual bool IsVisible() const override;

    virtual void SetParent(const TWidgetWeakRef& value) override;

    void SetChildrenVisibility(bool value) const;
    void ShowChildren();
    void HideChildren();

    virtual bool IsMouseOver() const override;

    void SendEvent(const TEvent& event);

private:
    typedef TWidget parent_type;

protected:
    virtual void _draw(TRenderTarget& target) override;
    virtual void _update() override;

    virtual void _handleEvent(const TEvent& event, bool& consume) override;
};

END_GUI

#endif // UIPARENT_H
