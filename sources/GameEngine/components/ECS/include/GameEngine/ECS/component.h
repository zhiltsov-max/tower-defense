#ifndef COMPONENT_H
#define COMPONENT_H

#include "GameEngine/utility.h"


GE_BEGIN_ENGINE_NAMESPACE

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

GE_END_ENGINE_NAMESPACE

#endif // COMPONENT_H
