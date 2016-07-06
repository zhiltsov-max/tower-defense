#include "td_application.h"
#include "Application/debug.h"
#include "Game/Application/application_task_game.h"
#include "Game/Application/application_task_menu.h"


namespace TD {

TTowerDefenseApplication& TTowerDefenseApplication::Create(
    const TApplicationInfo& info)
{
    new TTowerDefenseApplication(info); // _instance is set in parent constructor
    return *GetInstance();
}

TTowerDefenseApplication* TTowerDefenseApplication::GetInstance() {
    return dynamic_cast<TTowerDefenseApplication*>(_instance.get());
}


TTowerDefenseApplication::TTowerDefenseApplication(const TApplicationInfo& info) :
    parent_type(info),
    task(nullptr),
    state(TDAppState::Exit)
{}

const ApplicationState& TTowerDefenseApplication::GetState() const {
    return state;
}

void TTowerDefenseApplication::SetState(const ApplicationState& value) {
    if (value == state) {
        return;
    }

    switch (value) {
    case TDAppState::Game:
        task.reset(new TGame(this));
        state = value;
        break;

    case TDAppState::Menu:
        task.reset(new TMainMenu(this));
        state = value;
        break;

    case TDAppState::Exit:
        state = value;
        exit();
        return;

    default:
        THROW("Attempt to set an unexpected state to TD application.");
    }
}

const TTowerDefenseApplication::Settings&
TTowerDefenseApplication::GetSettings() const {
    return settings;
}

TTowerDefenseApplication::Settings&
TTowerDefenseApplication::GetSettings() {
    return settings;
}

void TTowerDefenseApplication::initialize(const TApplicationInfo& info_) {
    // TODO: loading application preferences
    // e.g. graphics, sound and keybindings
    // info = loadSettings(info);
    auto info = info_;
    info.appTitle = TEXT("Tower Defense");
    info.windowWidth = 1024;
    info.windowHeight = 768;
    info.style = sf::Style::Default;

    parent_type::initialize(info);
    SetState(TDAppState::Menu);
}

void TTowerDefenseApplication::update() {
    if (state == TDAppState::Exit) {
        return;
    }

    parent_type::update();
    task->Update();

    window->clear();
    task->Draw(*window);
    window->display();
}

void TTowerDefenseApplication::release() {
    parent_type::release();
    task.reset();
}

void TTowerDefenseApplication::handleEvent(const Event& event) {
    parent_type::handleEvent(event);
    if (task != nullptr) {
        task->HandleEvent(event);
    }
}


TTowerDefenseApplication* TDapp() {
    return TTowerDefenseApplication::GetInstance();
}

} // namespace TD
