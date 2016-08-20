#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include <stack>
#include "GameEngine/component_systems_manager.h"


namespace GE {

class TSceneObject
{
public:
    using Handle = size_t;
    static const Handle HandleUndefined;

    using ComponentHandle = TComponentHandle;

    using ComponentName = string;
    struct Entry;
    using Components = vector<Entry>;

    const ComponentHandle& operator [] (const ComponentName& name) const;
    ComponentHandle& operator [] (const ComponentName& name);

    const ComponentHandle& operator [] (const Handle& handle) const;
    ComponentHandle& operator [](const Handle& handle);

    const Handle& GetHandle(const ComponentName& name) const;

    Handle AddComponent(const ComponentName& name,
        const ComponentHandle& component);

    ComponentHandle RemoveComponent(const ComponentName& name);
    ComponentHandle RemoveComponent(const Handle& handle);

    bool HasComponent(const ComponentName& name) const;
    bool HasComponent(const Handle& handle) const;

    bool HasComponents() const;

    const Components& GetComponents() const;

private:
    using NameMapping = std::map<ComponentName, Handle>;
    using FreeHandles = std::stack<Handle>;

    NameMapping nameMapping;
    Components components;
    FreeHandles freeHandles;

    void checkSize();
};

struct TSceneObject::Entry
{
    ComponentName name;
    ComponentHandle component;

    Entry(const ComponentName& name = ComponentName(),
        const ComponentHandle& handle = ComponentHandle::Undefined
    );
};

} // namespace GE

#endif // SCENE_OBJECT_H
