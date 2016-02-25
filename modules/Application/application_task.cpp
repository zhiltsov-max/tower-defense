#include "application_task.h"



TTDApplicationTask::TTDApplicationTask(TTowerDefenseApplication* app) :
    app(app)
{}

void TTDApplicationTask::SetApplication(TTowerDefenseApplication* instance) {
    app = instance;
}
