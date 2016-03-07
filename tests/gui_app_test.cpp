#include "Application/application.h"
#include "Application/application_ui.h"
#include "GUI/gui_main.h"
#include "GUI/gui_lua_binding.h"



class TTestApplication : public TApplication
{
public:
    static TTestApplication& Create(const TApplicationInfo& info) {
        _instance.reset(new TTestApplication(info));
        return *GetInstance();
    }

    static TTestApplication* GetInstance() {
        return dynamic_cast<TTestApplication*>(_instance.get());
    }

protected:
    TTestApplication(const TApplicationInfo& info) :
        TApplication(info)
    {
        GUI::IO::SetGraphicsDevice(
            dynamic_cast< ::IO::TSFMLGraphicsDevice* >(
                controller->getGraphicsDevice()));
    }

    virtual void update() override {
        TApplication::update();
        window->clear();
        ui->draw();
        window->display();
    }
};


void loadInterface() {
    try {
        lua::State state;
        GUI::lua_binding::bindToLUA(state);
        state.runFile("resources/InterfaceClasses.lua");
        std::cout << "Interface loaded successfully." << std::endl;
        GUI::Debug::show_frames() = true;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}


int main(int argc, char** argv) {
    TApplicationInfo info;
    info.appTitle = TEXT("GUI test");
    info.style = sf::Style::Default;
    info.windowWidth = 800;
    info.windowHeight = 600;
    auto& app = TTestApplication::Create(info);
    loadInterface();
    return app.run();
}
