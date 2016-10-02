#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include "GameEngine/free_list_allocator.h"
#include "GameEngine/component_systems_manager.h"


namespace GE {

class TSceneObject
{
private:
    struct Entry;
    using ComponentsAllocator = FreelistAllocator<Entry>;

public:
    using Handle = ComponentsAllocator::Handle;
    static const Handle HandleUndefined;

    using ComponentHandle = TComponentHandle;
    using ComponentName = string;

    const ComponentHandle& operator [] (const ComponentName& name) const;
    ComponentHandle& operator [] (const ComponentName& name);

    const ComponentHandle& operator [] (const Handle& handle) const;
    ComponentHandle& operator [] (const Handle& handle);

    const Handle& GetHandle(const ComponentName& name) const;
    Handle GetHandle(const ComponentName& name);

    Handle AddComponent(const ComponentName& name,
        const ComponentHandle& component);

    ComponentHandle RemoveComponent(const ComponentName& name);
    ComponentHandle RemoveComponent(const Handle& handle);

    bool HasComponent(const ComponentName& name) const;
    bool HasComponent(const Handle& handle) const;

    bool HasComponents() const;

private:
    using NameMapping = std::map<ComponentName, Handle>;
    NameMapping nameMapping;

    ComponentsAllocator componentsAllocator;
};

struct TSceneObject::Entry
{
    ComponentName name;
    ComponentHandle component;

    Entry(const ComponentName& name = ComponentName(),
        const ComponentHandle& handle = ComponentHandle::Undefined);
};

} // namespace GE

#endif // SCENE_OBJECT_H
