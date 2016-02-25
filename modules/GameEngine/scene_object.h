#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include <stack>

#include "GameEngine/component_systems.h"



class TSceneObject
{
public:
    using Handle = size_t;
    static constexpr Handle HandleUndefined = (Handle)-1;

    class ComponentHandle;
    static const ComponentHandle ComponentHandleUndefined;

    using Name = string;


    const ComponentHandle& operator [](const Name& name) const;
    ComponentHandle& operator [](const Name& name);

    const Handle& GetHandle(const Name& name) const;

    const ComponentHandle& operator [](const Handle& handle) const;
    ComponentHandle& operator [](const Handle& handle);

    const Handle& AddComponent(const Name& name, const ComponentHandle& component);

    void RemoveComponent(const Name& name);
    void RemoveComponent(const Handle& handle);

    bool HasComponent(const Name& name) const;
    bool HasComponent(const Handle& handle) const;

private:
    using NameMapping = std::map<Name, Handle>;
    struct Entry;
    using FreeHandles = std::stack<Handle>;
    using Components = vector<Entry>;

    NameMapping nameMapping;
    Components components;
    FreeHandles freeHandles;

    void checkSize();

};

class TSceneObject::ComponentHandle
{
public:
    static const ComponentHandle Undefined;


    ComponentHandle(size_t handle = (size_t)-1,
        const ComponentSystem& system = ComponentSystem::_undefined);

    operator size_t() const;
    const ComponentSystem& GetSystem() const;

    bool operator==(const ComponentHandle& other) const;
    bool operator!=(const ComponentHandle& other) const;
private:
    using Value = TComponentSystem::Handle;
    using System = ComponentSystem;

    const Value value;
    const System system;
};

struct TSceneObject::Entry {
    Name name;
    ComponentHandle component;
};

#endif // SCENE_OBJECT_H
