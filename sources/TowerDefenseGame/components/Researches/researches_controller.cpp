#include "researches_controller.h"



namespace TD {


TResearchesController::TResearchesController(const TLevelInfoResearches& info) :
    registry()
{
    TResearchesRegistryLoader loader;
    loader.Load(info, registry);
}

TResearch TResearchesController::CreateResearch(const TResearch::ID& id) {
    ASSERT(registry.IsRegistered(id) == true,
        "Unknown research id #" + std::to_string(id));

    return TResearch(id);
}

const TResearchesController::Registry& TResearchesController::GetRegistry() const {
    return registry;
}

TResearchesController::Registry& TResearchesController::GetRegistry() {
    return registry;
}


} // namespace TD
