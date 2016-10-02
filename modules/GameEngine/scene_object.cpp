#include "scene_object.h"


namespace GE {

const TSceneObject::EntryHandle TSceneObject::HandleUndefined =
    TSceneObject::ComponentsAllocator::HandleUndefined;

TSceneObject::TSceneObject() :
    nameMapping(),
    componentsAllocator(),
    observerNotifierInstance()
{}

const TSceneObject::ComponentHandle&
TSceneObject::operator [] (const ComponentName& name) const {
    return operator [] (GetHandle(name));
}

TSceneObject::ComponentHandle&
TSceneObject::operator [] (const ComponentName& name) {
    return operator [] (GetHandle(name));
}

TSceneObject::EntryHandle
TSceneObject::GetHandle(const ComponentName& name) const {
    if (nameMapping.count(name) != 0) {
        return nameMapping.at(name);
    } else {
        return HandleUndefined;
    }
}

const TSceneObject::ComponentHandle&
TSceneObject::operator [] (const EntryHandle& handle) const {
    ASSERT(componentsAllocator.Owns(handle) == true,
        "Attempt to get an unexisting component.")
    return componentsAllocator[handle].component;
}

TSceneObject::ComponentHandle&
TSceneObject::operator [] (const EntryHandle& handle) {
    ASSERT(componentsAllocator.Owns(handle) == true,
        "Attempt to get an unexisting component.")
    return componentsAllocator[handle].component;
}

TSceneObject::EntryHandle
TSceneObject::AddComponent(const ComponentName& name,
    const ComponentHandle& component)
{
    ASSERT(name.empty() == false,
        "Attempt to add an unnamed component.");
    ASSERT(component != ComponentHandle::Undefined,
        "Attempt to add an empty component handle.")
    ASSERT(HasComponent(name) == false,
        "Component with this name already exists.");

    auto handle = componentsAllocator.Allocate();
    try {
        ::new (&componentsAllocator[handle]) Entry(name, component);
        nameMapping[name] = handle;

        TSceneObjectMessage message{TSceneObjectMessage::Type::ComponentAdded};
        message.componentAdded.component = component;
        Notify(message);
    } catch (...) {
        componentsAllocator.Deallocate(handle);
        throw;
    }

    return handle;
}

TSceneObject::ComponentHandle
TSceneObject::RemoveComponent(const ComponentName& name) {
    return RemoveComponent(GetHandle(name));
}

TSceneObject::ComponentHandle
TSceneObject::RemoveComponent(const EntryHandle& handle) {
    ASSERT(componentsAllocator.Owns(handle) == true,
        "Attempt to remove an unexisting component")

    auto& entry = componentsAllocator[handle];
    const auto componentHandle = entry.component;

    nameMapping.erase(entry.name);
    entry.~Entry();
    componentsAllocator.Deallocate(handle);

    TSceneObjectMessage message{TSceneObjectMessage::Type::ComponentRemoved};
    message.componentRemoved.component = componentHandle;
    Notify(message);

    return componentHandle;
}

bool TSceneObject::HasComponent(const ComponentName& name) const {
    return GetHandle(name) != HandleUndefined;
}

bool TSceneObject::HasComponent(const EntryHandle& handle) const {
    const auto* entry = componentsAllocator.GetElementPointer(handle);
    return (entry != nullptr) &&
        (entry->component != ComponentHandle::Undefined);
}

bool TSceneObject::HasComponents() const {
    return nameMapping.empty() == false;
}

void TSceneObject::Notify(const TSceneObjectMessage& message) {
    if (observerNotifierInstance) {
        observerNotifierInstance(message);
    }
}

void TSceneObject::SetObserver(ObserverNotifier instance) {
    observerNotifierInstance = std::move(instance);
}


TSceneObject::Entry::Entry(
    const ComponentName& name, const ComponentHandle& handle
) :
    name(name),
    component(handle)
{}

} // namespace GE
