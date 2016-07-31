#include "level_passability_map.h"


const GE::ComponentIDs GE::ComponentID<TD::CLevelPassabilityMap>::value =
    GE::ComponentIDs::LevelPassabilityMap;

namespace TD {

std::unique_ptr<GE::TComponent>
CLevelPassabilityMap::Create(const GE::TComponentCreateArgs* args_) {
    const auto* args = dynamic_cast<const Parameters*>(args_);
    if ((args_ != nullptr) && (args == nullptr)) {
        THROW("Wrong args passed to function.");
    }
    return std::unique_ptr<GE::TComponent>(new CLevelPassabilityMap(args));
}

CLevelPassabilityMap::CLevelPassabilityMap(const Parameters* source) :
    parent_type(GE::ComponentID<CLevelPassabilityMap>::value)
{
    if (source != nullptr) {
        size = source->size;
        for (auto& map : maps) {
            map.reserve(source->size.x * source->size.y);
        }
    }
}

const CLevelPassabilityMap::PassabilityMap&
CLevelPassabilityMap::GetMap(const Altitude& altitude) {
    return maps[static_cast<uchar>(altitude)];
}

const CLevelPassabilityMap::Size& CLevelPassabilityMap::GetSize() const {
    return size;
}

} // namespace TD
