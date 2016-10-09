#include "GameEngine/scene_object.h"
#include <iostream>


namespace GE {

const TSceneObject::EntryHandle TSceneObject::HandleUndefined =
    TSceneObject::ComponentsAllocator::HandleUndefined;

TSceneObject::TSceneObject() :
    nameMapping(),
    componentsAllocator(),
    observable(this)
{}

TSceneObject::TSceneObject(TSceneObject&& other) :
    nameMapping(std::move(other.nameMapping)),
    componentsAllocator(std::move(other.componentsAllocator)),
    observable(std::move(other.observable))
{
    observable.SetOwner(this);
}

TSceneObject& TSceneObject::operator = (TSceneObject&& other) {
    if (this != &other) {
        nameMapping = std::move(other.nameMapping);
        componentsAllocator = std::move(other.componentsAllocator);
        observable = std::move(other.observable);
        observable.SetOwner(this);
    }

    return *this;
}

TSceneObject::~TSceneObject() {
    try {
        for (auto& entry : nameMapping) {
            const auto handle = (*this)[entry.second];
            notifyComponentHandleDeleted(handle);
        }
    } catch (...) {
        std::cout << "some exception in dtor catched" << std::endl;
    }
}

const TSceneObject::ComponentHandle&
TSceneObject::operator [] (const ComponentName& name) const {
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
    return componentsAllocator[handle].second;
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
    auto holderDeleter = [this, &name] (ComponentsAllocator::Handle* handle) {
        componentsAllocator.Deallocate(*handle);
        nameMapping.erase(name);
    };
    std::unique_ptr<decltype(handle), decltype(holderDeleter)>
        handleHolder {&handle, std::move(holderDeleter)};
    ::new (&componentsAllocator[handle]) Entry(name, component);
    nameMapping[name] = handle;

    notifyComponentHandleAdded(component, handle);

    handleHolder.release();
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
    const auto componentHandle = entry.second;

    nameMapping.erase(entry.first);
    entry.~Entry();
    componentsAllocator.Deallocate(handle);

    notifyComponentHandleDeleted(componentHandle);

    return componentHandle;
}

bool TSceneObject::HasComponent(const ComponentName& name) const {
    return GetHandle(name) != HandleUndefined;
}

bool TSceneObject::HasComponent(const EntryHandle& handle) const {
    const auto* entry = componentsAllocator.GetElementPointer(handle);
    return (entry != nullptr) && (entry->second != ComponentHandle::Undefined);
}

bool TSceneObject::HasComponents() const {
    return nameMapping.empty() == false;
}

TSceneObject::EntryConstRange TSceneObject::EnumerateEntries() const {
    return {nameMapping.begin(), nameMapping.end()};
}

TSceneObject::EntryRange TSceneObject::EnumerateEntries() {
    return {nameMapping.begin(), nameMapping.end()};
}

const TSceneObject::Observable& TSceneObject::AsObservable() const {
    return observable;
}

TSceneObject::Observable& TSceneObject::AsObservable() {
    return observable;
}

void TSceneObject::notifyComponentHandleAdded(const ComponentHandle& handle,
    const EntryHandle& entry)
{
    TSceneObjectMessage message{TSceneObjectMessage::Type::ComponentAdded};
    message.componentAdded.component = handle;
    message.componentAdded.entry = entry;
    observable.Notify(message);
}

void TSceneObject::notifyComponentHandleDeleted(const ComponentHandle& handle) {
    TSceneObjectMessage message{TSceneObjectMessage::Type::ComponentRemoved};
    message.componentRemoved.component = handle;
    observable.Notify(message);
}


TSceneObject::Observable::Observable(TSceneObject* owner) :
    owner(owner)
{}

void TSceneObject::Observable::SetOwner(TSceneObject* instance) {
    owner = instance;
}

void TSceneObject::Observable::Notify(const TSceneObjectMessage& message) {
    if (static_cast<bool>(observerNotifierInstance) == true) {
        observerNotifierInstance(message);
    }
}

void TSceneObject::Observable::handleObserverChange() {
    if (owner == nullptr) {
        return;
    }

    for (auto& entry : owner->nameMapping) {
        const auto handle = (*owner)[entry.second];
        owner->notifyComponentHandleDeleted(handle);
        owner->notifyComponentHandleAdded(handle, entry.second);
    }
}

void TSceneObject::Observable::SetObserver(const ObserverNotifier& instance) {
    observerNotifierInstance = instance;
    handleObserverChange();
}

void TSceneObject::Observable::SetObserver(ObserverNotifier&& instance) {
    observerNotifierInstance = std::move(instance);
    handleObserverChange();
}


} // namespace GE
