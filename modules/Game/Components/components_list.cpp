#include "Game/Components/components_list.h"


namespace TD {

namespace CS {

GE::TComponentRegistry componentsRegistry;

namespace impl {

GE::TComponentRegistry& GetComponentsRegistry() {
    return componentsRegistry;
}

} // namespace impl

const GE::TComponentRegistry& GetComponentsRegistry() {
    return componentsRegistry;
}

} // namespace CS

} // namespace TD
