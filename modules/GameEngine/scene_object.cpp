#include "scene_object.h"



const TSceneObject::ComponentHandle TSceneObject::ComponentHandle::Undefined; //keep it before TSceneObject::ComponentHandleUndefined

const TSceneObject::ComponentHandle TSceneObject::ComponentHandleUndefined =
    TSceneObject::ComponentHandle::Undefined;

const TSceneObject::Handle TSceneObject::HandleUndefined = -1u;

const TSceneObject::ComponentHandle&
TSceneObject::operator [] (const Name& name) const {
    return components.at(GetHandle(name)).component;
}

TSceneObject::ComponentHandle& TSceneObject::operator [] (const Name& name) {
    return components.at(GetHandle(name)).component;
}

const TSceneObject::Handle& TSceneObject::GetHandle(const Name& name) const {
    if (nameMapping.count(name) != 0) {
        return nameMapping.at(name);
    } else {
        return HandleUndefined;
    }
}

const TSceneObject::ComponentHandle&
TSceneObject::operator [] (const Handle& handle) const {
    return components.at(handle).component;
}

TSceneObject::ComponentHandle&
TSceneObject::operator [] (const Handle& handle) {
    return components.at(handle).component;
}

TSceneObject::Handle TSceneObject::AddComponent(const Name& name,
    const ComponentHandle& component)
{
    ASSERT(name.empty() == false,
        "Attempt to add an unnamed component.");
    ASSERT(component != ComponentHandleUndefined,
        "Attempt to add an empty component handle.")
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
    nameMapping[name] = handle;

    return handle;
}

TSceneObject::ComponentHandle TSceneObject::RemoveComponent(const Name& name) {
    Handle handle = GetHandle(name);
    return RemoveComponent(handle);
}

TSceneObject::ComponentHandle
TSceneObject::RemoveComponent(const Handle& handle) {
    ASSERT(handle != HandleUndefined,
        "Attempt to remove an unexisting component")
    ASSERT(components.at(handle).name.empty() == false,
        "Attempt to remove an unexisting component")

    auto& entry = components.at(handle);
    nameMapping.erase(entry.name);
    entry.name.clear();

    auto componentHandle = entry.component;
    entry.component = ComponentHandleUndefined;

    freeHandles.push(handle);
    checkSize();

    return componentHandle;
}

bool TSceneObject::HasComponent(const Name& name) const {
    return GetHandle(name) != HandleUndefined;
}

bool TSceneObject::HasComponent(const Handle& handle) const {
    return (handle < components.size()) &&
        (components.at(handle).component != ComponentHandleUndefined);
}

bool TSceneObject::HasComponents() const {
    return components.empty() == false;
}

void TSceneObject::checkSize() {
    if (components.size() == freeHandles.size()) {
        components.clear();
        components.shrink_to_fit();
        freeHandles = std::move(FreeHandles());
        nameMapping.clear();
    }
}



TSceneObject::ComponentHandle::ComponentHandle(
    size_t handle, const ComponentSystem& system
) :
    value(handle),
    system(system)
{}

const ComponentSystem& TSceneObject::ComponentHandle::GetSystem() const {
    return system;
}

const TComponentSystem::Handle&
TSceneObject::ComponentHandle::GetValue() const {
    return value;
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
