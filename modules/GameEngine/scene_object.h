#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include <stack>

#include "GameEngine/component_systems.h"



namespace GE {


class TSceneObject
{
public:
    using Handle = size_t;
    static const Handle HandleUndefined;

    class ComponentHandle;
    static const ComponentHandle ComponentHandleUndefined;

    using Name = string;


    const ComponentHandle& operator [] (const Name& name) const;
    ComponentHandle& operator [] (const Name& name);

    const ComponentHandle& operator [] (const Handle& handle) const;
    ComponentHandle& operator [](const Handle& handle);

    const Handle& GetHandle(const Name& name) const;

    Handle AddComponent(const Name& name,
        const ComponentHandle& component);

    ComponentHandle RemoveComponent(const Name& name);
    ComponentHandle RemoveComponent(const Handle& handle);

    bool HasComponent(const Name& name) const;
    bool HasComponent(const Handle& handle) const;

    bool HasComponents() const;

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


    ComponentHandle(size_t handle = -1u,
        const ComponentSystem& system = ComponentSystem::_undefined);

    operator size_t() const;
    const ComponentSystem& GetSystem() const;
    const TComponentSystem::Handle& GetValue() const;

    bool operator==(const ComponentHandle& other) const;
    bool operator!=(const ComponentHandle& other) const;

private:
    using Value = TComponentSystem::Handle;
    using System = ComponentSystem;

    Value value;
    System system;
};

struct TSceneObject::Entry {
    Name name;
    ComponentHandle component;

    Entry(const Name& name = Name(),
        const ComponentHandle& handle = ComponentHandle::Undefined
    );
};


} //namespace GE

#endif // SCENE_OBJECT_H
