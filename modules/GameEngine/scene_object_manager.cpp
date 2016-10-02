#include "GameEngine/scene_object_manager.h"


namespace GE {

const TSceneObjectManager::ObjectHandle
TSceneObjectManager::ObjectHandle::Undefined =
    TSceneObjectManager::ObjectsAllocator::HandleUndefined;

const TSceneObjectManager::SceneObject&
TSceneObjectManager::operator [] (const SceneObjectName& name) const {
    return GetSceneObject(name);
}

TSceneObjectManager::SceneObject&
TSceneObjectManager::operator [] (const SceneObjectName& name) {
    return GetSceneObject(name);
}

const TSceneObjectManager::SceneObject&
TSceneObjectManager::GetSceneObject(const SceneObjectName& name) const {
    auto handle = GetHandle(name);
    ASSERT(handle.IsNull() == false, "Attempt to get an unexisting object.")
    return objectsAllocator[handle].second;
}

TSceneObjectManager::SceneObject&
TSceneObjectManager::GetSceneObject(const SceneObjectName& name) {
    auto handle = GetHandle(name);
    ASSERT(handle.IsNull() == false, "Attempt to get an unexisting object.")
    return objectsAllocator[handle].second;
}

TSceneObjectManager::ObjectHandle
TSceneObjectManager::GetHandle(const SceneObjectName& name) const {
    if (nameMapping.count(name) != 0) {
        return nameMapping.at(name);
    } else {
        return ObjectHandle::Undefined;
    }
}

const TSceneObjectManager::SceneObject&
TSceneObjectManager::operator [] (const ObjectHandle& handle) const {
    return GetSceneObject(handle);
}

TSceneObjectManager::SceneObject&
TSceneObjectManager::operator [] (const ObjectHandle& handle) {
    return GetSceneObject(handle);
}

const TSceneObjectManager::SceneObject&
TSceneObjectManager::GetSceneObject(const ObjectHandle& handle) const {
    ASSERT(handle.IsNull() == false, "Attempt to get an unexisting object.")
    return objectsAllocator[handle].second;
}

TSceneObjectManager::SceneObject&
TSceneObjectManager::GetSceneObject(const ObjectHandle& handle) {
    ASSERT(handle.IsNull() == false, "Attempt to get an unexisting object.")
    return objectsAllocator[handle].second;
}

TSceneObjectManager::ObjectHandle
TSceneObjectManager::AddSceneObject(const SceneObjectName& name,
    const TSceneObject& sceneObject)
{
    ASSERT(name.empty() == false,
        "Attempt to add an unnamed object.");
    ASSERT(HasObject(name) == false,
        "Object with this name already exists.");

    auto handle = objectsAllocator.Allocate();
    try {
        auto* entry = ::new (&objectsAllocator[handle])
            Entry(name, sceneObject);
        entry->second.SetObserver(
            [this, handle] (const TSceneObjectMessage& message) {
                this->RecieveMessage(message, handle);
            }
        );
        nameMapping[name] = handle;
    } catch (...) {
        objectsAllocator.Deallocate(handle);
        throw;
    }

    return handle;
}

TSceneObjectManager::ObjectHandle
TSceneObjectManager::AddSceneObject(const SceneObjectName& name,
    TSceneObject&& sceneObject)
{
    ASSERT(name.empty() == false,
        "Attempt to add an unnamed object.");
    ASSERT(HasObject(name) == false,
        "Object with this name already exists.");

    auto handle = objectsAllocator.Allocate();
    try {
        auto* entry = ::new (&objectsAllocator[handle])
            Entry(name, std::move(sceneObject));
        entry->second.SetObserver(
            [this, handle] (const TSceneObjectMessage& message) {
                this->RecieveMessage(message, handle);
            }
        );
        nameMapping[name] = handle;
    } catch (...) {
        objectsAllocator.Deallocate(handle);
        throw;
    }

    return handle;
}

void TSceneObjectManager::RemoveSceneObject(const SceneObjectName& name) {
    RemoveSceneObject(GetHandle(name));
}

void TSceneObjectManager::RemoveSceneObject(const ObjectHandle& handle) {
    if (HasObject(handle) == false) {
        return;
    }

    auto& entry = objectsAllocator[handle];
    nameMapping.erase(entry.first);
    entry.~Entry();
    objectsAllocator.Deallocate(handle);
}

bool TSceneObjectManager::HasObject(const SceneObjectName& name) const {
    return GetHandle(name) != ObjectHandle::Undefined;
}

bool TSceneObjectManager::HasObject(const ObjectHandle& handle) const {
    return objectsAllocator.Owns(handle) == true;
}

void TSceneObjectManager::Clear() {
    objectsAllocator = std::move(ObjectsAllocator());
    nameMapping.clear();
}

bool TSceneObjectManager::IsEmpty() const {
    return nameMapping.empty();
}

void TSceneObjectManager::RecieveMessage(const TSceneObjectMessage& message,
    const ObjectHandle& source)
{
    switch (message.type) {
    case TSceneObjectMessage::Type::ComponentAdded:
        handleMessage_SceneObjectComponentAdded(message.componentAdded,
            source);
        break;

    case TSceneObjectMessage::Type::ComponentRemoved:
        handleMessage_SceneObjectComponentRemoved(message.componentRemoved,
            source);
        break;

    default: /*none*/;
    }
}

void TSceneObjectManager::handleMessage_SceneObjectComponentAdded(
    const TSceneObjectMessage::ComponentAddedMessage& message,
    const ObjectHandle& source)
{
    //TODO: notify subscribers
}

void TSceneObjectManager::handleMessage_SceneObjectComponentRemoved(
    const TSceneObjectMessage::ComponentRemovedMessage& message,
    const ObjectHandle& source)
{
    //TODO: notify subscribers
}


TSceneObjectManager::ObjectHandle::ObjectHandle(const Value& handle) :
    handle(handle)
{}

const TSceneObjectManager::ObjectHandle::Value&
TSceneObjectManager::ObjectHandle::GetValue() const {
    return handle;
}

TSceneObjectManager::ObjectHandle::operator Value() const {
    return handle;
}

bool TSceneObjectManager::ObjectHandle::operator == (
    const ObjectHandle& other) const
{
    return handle == other.handle;
}

bool TSceneObjectManager::ObjectHandle::operator != (
    const ObjectHandle& other) const
{
    return handle != other.handle;
}

bool TSceneObjectManager::ObjectHandle::IsNull() const {
    return operator==(Undefined);
}

} // namespace GE
