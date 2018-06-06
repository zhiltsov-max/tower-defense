#ifndef APPLICATION_TASK_MENU_H
#define APPLICATION_TASK_MENU_H

#include "GameEngine/Utility/luawrapper.h"
#include "Game/Application/application_task.h"


namespace TD {

class TMainMenuBackground
{
public:
    TMainMenuBackground();
	
	void update();	
    void draw(Graphics::TRenderTarget& target);
private:
    static constexpr Graphics::ARGB DEFAULT_COLOR = 0xffffffff;
    Graphics::ARGB color;
    sf::RectangleShape drawable;
};


class TMainMenu : public TTDApplicationTask
{
public:
    TMainMenu(TTowerDefenseApplication* app);
    virtual ~TMainMenu();

    virtual const TDAppState& GetCode() const;

    virtual void Update() override;
    virtual void Draw(Graphics::TRenderTarget& target) override;
    virtual void HandleEvent(const TApplication::Event& event) override;

private:
    typedef TTDApplicationTask parent_type;

    TMainMenuBackground background;
    lua::State luaState;
};

} // namespace TD

#endif //APPLICATION_TASK_MENU_H
