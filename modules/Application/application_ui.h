#ifndef APPLICATION_UI_H
#define APPLICATION_UI_H

#include <memory>



namespace GUI {
class TUIParent;
}

struct TApplicationInfo;

class TApplicationUI 
{
public:
    TApplicationUI(const TApplicationInfo& info);

    std::shared_ptr<const GUI::TUIParent> getUIParent() const;
    std::shared_ptr<GUI::TUIParent> getUIParent();

    void update();
    void draw();

private:
    using UIParent = std::shared_ptr<GUI::TUIParent>;
    UIParent uiParent;
};

#endif //APPLICATION_UI_H
