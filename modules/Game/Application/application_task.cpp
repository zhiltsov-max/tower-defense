#include "application_task.h"


namespace TD {

TApplicationTask::TApplicationTask(TTowerDefenseApplication* app) :
    app(app)
{}

void TApplicationTask::SetApplication(TTowerDefenseApplication* instance) {
    app = instance;
}

} // namespace TD
