#include "GameEngine/Application/application.h"


namespace GE {

AApplication::PApplication AApplication::instance { nullptr };

AApplication* AApplication::GetInstance() {
    ASSERT(instance != nullptr, "Application does not exist.")

    return instance.get();
}

AApplication::AApplication() {
    ASSERT(instance == nullptr,
        "Can not create multiple instances of Application.")
}

AApplication::~AApplication() { /* none */ }


AApplication& app() {
    return AApplication::GetInstance();
}

} // namespace GE