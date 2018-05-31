#ifndef COMPONENT_H
#define COMPONENT_H

#include "Core/core.h"


namespace GE {

using TComponentID = uint;
enum class ComponentIDs : TComponentID;

std::ostream& operator << (std::ostream& os, const ComponentIDs& id);

class TComponent
{
public:
    using ID = ComponentIDs;

    virtual ~TComponent() = default;

    const ID& GetID() const;

protected:
    TComponent(const ID& id);

private:
    const ID id;
};

template< class Component >
struct ComponentID;

} // namespace GE

#endif // COMPONENT_H
