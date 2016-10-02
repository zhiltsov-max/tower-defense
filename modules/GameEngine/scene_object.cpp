#include "scene_object.h"


namespace GE {

const TSceneObject::Handle TSceneObject::HandleUndefined =
    TSceneObject::ComponentsAllocator::HandleUndefined;

const TSceneObject::ComponentHandle&
TSceneObject::operator [] (const ComponentName& name) const {
    return operator [] (GetHandle(name));
}

TSceneObject::ComponentHandle&
TSceneObject::operator [] (const ComponentName& name) {
    return operator [] (GetHandle(name));
}

const TSceneObject::Handle&
TSceneObject::GetHandle(const ComponentName& name) const {
    if (nameMapping.count(name) != 0) {
        return nameMapping.at(name);
    } else {
        return HandleUndefined;
    }
}

TSceneObject::Handle
TSceneObject::GetHandle(const ComponentName& name) {
    if (nameMapping.count(name) != 0) {
        return nameMapping.at(name);
    } else {
        return HandleUndefined;
    }
}

const TSceneObject::ComponentHandle&
TSceneObject::operator [] (const Handle& handle) const {
    ASSERT(componentsAllocator.Owns(handle) == true,
        "Attempt to get an unexisting component.")
    return componentsAllocator[handle].component;
}

TSceneObject::ComponentHandle&
TSceneObject::operator [] (const Handle& handle) {
    ASSERT(componentsAllocator.Owns(handle) == true,
        "Attempt to get an unexisting component.")
    return componentsAllocator[handle].component;
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

    Handle handle = componentsAllocator.Allocate();
    try {
        ::new (componentsAllocator.GetElementPointer(handle)) Entry(name, component);
    } catch (...) {
        componentsAllocator.Deallocate(handle);
        throw;
    }
    nameMapping[name] = handle;

    return handle;
}

TSceneObject::ComponentHandle
TSceneObject::RemoveComponent(const ComponentName& name) {
    return RemoveComponent(GetHandle(name));
}

TSceneObject::ComponentHandle
TSceneObject::RemoveComponent(const Handle& handle) {
    ASSERT(componentsAllocator.Owns(handle) == true,
        "Attempt to remove an unexisting component")

    auto& entry = componentsAllocator[handle];
    const auto componentHandle = entry.component;

    nameMapping.erase(entry.name);
    entry.~Entry();
    componentsAllocator.Deallocate(handle);

    return componentHandle;
}

bool TSceneObject::HasComponent(const ComponentName& name) const {
    return GetHandle(name) != HandleUndefined;
}

bool TSceneObject::HasComponent(const Handle& handle) const {
    const auto* entry = componentsAllocator.GetElementPointer(handle);
    return (entry != nullptr) &&
        (entry->component != ComponentHandle::Undefined);
}

bool TSceneObject::HasComponents() const {
    return nameMapping.empty() == false;
}


TSceneObject::Entry::Entry(
    const ComponentName& name, const ComponentHandle& handle
) :
    name(name),
    component(handle)
{}

} // namespace GE
