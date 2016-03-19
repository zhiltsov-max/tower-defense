#include "scene_object.h"



const TSceneObject::ComponentHandle
TSceneObject::ComponentHandleUndefined =
    TSceneObject::ComponentHandle::Undefined;

const TSceneObject::ComponentHandle&
TSceneObject::operator [](const Name& name) const {
    return components[GetHandle(name)].component;
}

TSceneObject::ComponentHandle&
TSceneObject::operator [](const Name& name) {
    return components[GetHandle(name)].component;
}

const TSceneObject::Handle& TSceneObject::GetHandle(const Name& name) const {
    if (nameMapping.count(name) != 0) {
        return nameMapping.at(name);
    } else {
        return HandleUndefined;
    }
}

const TSceneObject::ComponentHandle&
TSceneObject::operator [](const Handle& handle) const {
    return components[handle].component;
}

TSceneObject::ComponentHandle&
TSceneObject::operator [](const Handle& handle) {
    return components[handle].component;
}

TSceneObject::Handle
TSceneObject::AddComponent(const Name& name,
    const ComponentHandle& component)
{
    ASSERT(HasComponent(name) == false,
        "Component with this name already exists.");

    Handle handle = HandleUndefined;
    if (freeHandles.empty() == false) {
        handle = freeHandles.top();
        freeHandles.pop();

        components[handle] = std::move(Entry(name, component));
    } else {
        handle = components.size();
        components.emplace_back(name, component);
    }
    return handle;
}

void TSceneObject::RemoveComponent(const Name& name) {
    Handle handle = GetHandle(name);
    RemoveComponent(handle);
}

void TSceneObject::RemoveComponent(const Handle& handle) {
    ASSERT(handle != HandleUndefined,
        "Attempt to remove an unexisting component")
    ASSERT(components[handle].name.empty() == false,
        "Attempt to remove an unexisting component")

    auto& entry = components[handle];
    nameMapping.erase(entry.name);
    entry.name.clear();
    entry.component = ComponentHandleUndefined;

    freeHandles.push(handle);
    checkSize();
}

bool TSceneObject::HasComponent(const Name& name) const {
    return GetHandle(name) != HandleUndefined;
}

bool TSceneObject::HasComponent(const Handle& handle) const {
    return components[handle].component != ComponentHandleUndefined;
}

void TSceneObject::checkSize() {
    if (components.size() == freeHandles.size()) {
        components.clear();
        freeHandles = FreeHandles();
        nameMapping.clear();
    }
}



const TSceneObject::ComponentHandle
TSceneObject::ComponentHandle::Undefined {
    (size_t)-1,
    ComponentSystem::_undefined
};

TSceneObject::ComponentHandle::ComponentHandle(
    size_t handle, const ComponentSystem& system
) :
    value(handle),
    system(system)
{}

const ComponentSystem&
TSceneObject::ComponentHandle::GetSystem() const {
    return system;
}

bool TSceneObject::ComponentHandle::operator == (
    const ComponentHandle& other) const
{
    return (system == other.system) &&
        (value == other.value);
}

bool TSceneObject::ComponentHandle::operator != (
    const ComponentHandle& other) const
{
    return !operator==(other);
}

TSceneObject::ComponentHandle::operator size_t() const {
    return value;
}

TSceneObject::Entry::Entry(
    const Name& name, const ComponentHandle& handle
) :
    name(name),
    component(handle)
{}
