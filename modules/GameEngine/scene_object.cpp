#include "scene_object.h"


namespace GE {

const TSceneObject::Handle TSceneObject::HandleUndefined = -1u;

const TSceneObject::ComponentHandle&
TSceneObject::operator [] (const ComponentName& name) const {
    return components.at(GetHandle(name)).component;
}

TSceneObject::ComponentHandle& TSceneObject::operator [] (const ComponentName& name) {
    return components.at(GetHandle(name)).component;
}

const TSceneObject::Handle& TSceneObject::GetHandle(const ComponentName& name) const {
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

TSceneObject::Handle TSceneObject::AddComponent(const ComponentName& name,
    const ComponentHandle& component)
{
    ASSERT(name.empty() == false,
        "Attempt to add an unnamed component.");
    ASSERT(component != ComponentHandle::Undefined,
        "Attempt to add an empty component handle.")
    ASSERT(HasComponent(name) == false,
        "Component with this name already exists.");

    Handle handle = HandleUndefined;
    if (freeHandles.empty() == false) {
        handle = freeHandles.top();
        freeHandles.pop();

        components[handle] = Entry(name, component);
    } else {
        handle = components.size();
        components.emplace_back(name, component);
    }
    nameMapping[name] = handle;

    return handle;
}

TSceneObject::ComponentHandle TSceneObject::RemoveComponent(const ComponentName& name) {
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
    entry.component = ComponentHandle::Undefined;

    freeHandles.push(handle);
    checkSize();

    return componentHandle;
}

bool TSceneObject::HasComponent(const ComponentName& name) const {
    return GetHandle(name) != HandleUndefined;
}

bool TSceneObject::HasComponent(const Handle& handle) const {
    return (handle < components.size()) &&
        (components.at(handle).component != ComponentHandle::Undefined);
}

bool TSceneObject::HasComponents() const {
    return components.empty() == false;
}

const TSceneObject::Components& TSceneObject::GetComponents() const {
    return components;
}

void TSceneObject::checkSize() {
    if (components.size() == freeHandles.size()) {
        components.clear();
        components.shrink_to_fit();
        freeHandles = FreeHandles();
        nameMapping.clear();
    }
}


TSceneObject::Entry::Entry(
    const ComponentName& name, const ComponentHandle& handle
) :
    name(name),
    component(handle)
{}

} // namespace GE
