#include "player_quests.h"


namespace TD {

std::unique_ptr<TComponent>
CPLayerQuests::Create(const TComponentCreateArgs* args) {
    //TODO: implementation
    return std::unique_ptr<TComponent>(new CPLayerQuests(*args));
}

CPLayerQuests::CPLayerQuests() {
    //TODO: implementation
}

} // namespace TD
