#include "config.h"
#include "Core/core.h"
#include "Application/td_application.h"



int main(int argc, char** argv) {
    TApplicationInfo info;
    info.argc = &argc;
    info.argv = &argv;

    auto& app = TTowerDefenseApplication::Create(info);
    return app.run();
}
