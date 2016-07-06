#include "application_task_menu.h"
#include "Application/application_ui.h"
#include "GUI/gui_lua_binding.h"
#include "Game/Application/td_application.h"


namespace TD {

TMainMenuBackground::TMainMenuBackground() :
    color(DEFAULT_COLOR)
{
    drawable = sf::RectangleShape(
        sf::Vector2f(app()->getWindowWidth(), app()->getWindowHeight())
    );
    drawable.setFillColor(color);
}

void TMainMenuBackground::update() { /*none*/ }

void TMainMenuBackground::draw(Graphics::TRenderTarget& target) {
    target.draw(drawable);
}



TMainMenu::TMainMenu(TTowerDefenseApplication* app) :
    parent_type(app),
    background(),
    luaState(),
    fpsCounter()
{
    try {
        app->getDebugTools().log("MainMenu initialization...");

        initLUA();

        app->getDebugTools().log("done.");
    } catch (const exception& e) {
        THROW(e.what())
    }
}

TMainMenu::~TMainMenu() {
    UIParent()->RemoveChildren();
}

const AppState& TMainMenu::GetCode() const {
    return AppState::Menu;
}

void TMainMenu::initLUA() {
    app->getDebugTools().log("MainMenu LUA init...");

    GUI::lua_binding::bindToLUA(luaState);
    luaState.runFile("initialize_common.lua");
    luaState.runFile("mainmenu.lua");

    app->getDebugTools().log("done.");
}
		
void TMainMenu::Update() {
    background.update();
    fpsCounter.update();
}

void TMainMenu::Draw(Graphics::TRenderTarget& target) {
    background.draw(target);
    if (app->getDebugTools().isDebugEnabled() == true) {
        fpsCounter.draw(target);
    }
    app->getUI().draw();
}

void TMainMenu::HandleEvent(const TApplication::Event& event) {
    switch (event.type) {
    case TApplication::Event::KeyReleased:
        switch (event.key.code) {
        case sf::Keyboard::Escape: {
            app->SetState(AppState::Exit);
            break;

        case sf::Keyboard::F1:
            app->getDebugTools().setTechInfoVisibility(
                !app->getDebugTools().isTechInfoVisible()
            );
            break;

        case sf::Keyboard::F2:
            GUI::Debug::show_frames() = !GUI::Debug::show_frames();
            break;

            default: {/*none*/}
        }
        break;

    default: {/*none*/}
    }
}

} // namespace TD
