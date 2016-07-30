#include "scene_object_container.h"


namespace GE {

const TSceneObjectContainer::ObjectHandle
TSceneObjectContainer::ObjectHandle::Undefined{-1u};

const TSceneObjectContainer::SceneObject&
TSceneObjectContainer::operator [] (const SceneObjectName& name) const {
    return GetSceneObject(name);
}

TSceneObjectContainer::SceneObject&
TSceneObjectContainer::operator [] (const SceneObjectName& name) {
    return GetSceneObject(name);
}

const TSceneObjectContainer::SceneObject&
TSceneObjectContainer::GetSceneObject(const SceneObjectName& name) const {
    return objects.at(GetHandle(name)).second;
}

TSceneObjectContainer::SceneObject&
TSceneObjectContainer::GetSceneObject(const SceneObjectName& name) {
    return objects.at(GetHandle(name)).second;
}

TSceneObjectContainer::ObjectHandle
TSceneObjectContainer::GetHandle(const SceneObjectName& name) const {
    if (nameMapping.count(name) != 0) {
        return nameMapping.at(name);
    } else {
        return ObjectHandle::Undefined;
    }
}

const TSceneObjectContainer::SceneObject&
TSceneObjectContainer::operator [] (const ObjectHandle& handle) const {
    return GetSceneObject(handle);
}

TSceneObjectContainer::SceneObject&
TSceneObjectContainer::operator [] (const ObjectHandle& handle) {
    return GetSceneObject(handle);
}

const TSceneObjectContainer::SceneObject&
TSceneObjectContainer::GetSceneObject(const ObjectHandle& handle) const {
    return objects.at(handle).second;
}

TSceneObjectContainer::SceneObject&
TSceneObjectContainer::GetSceneObject(const ObjectHandle& handle) {
    return objects.at(handle).second;
}

TSceneObjectContainer::ObjectHandle
TSceneObjectContainer::AddSceneObject(const SceneObjectName& name,
    const TSceneObject& sceneObject)
{
    ASSERT(name.empty() == false,
        "Attempt to add an unnamed component.");
    ASSERT(HasObject(name) == false,
        "Object with this name already exists.");

    ObjectHandle handle;
    if (freeHandles.empty() == false) {
        handle = freeHandles.top();
        freeHandles.pop();

        objects[handle] = Entry(name, sceneObject);
    } else {
        handle = objects.size();
        objects.emplace_back(name, sceneObject);
    }
    nameMapping[name] = handle;

    return handle;
}

TSceneObjectContainer::ObjectHandle
TSceneObjectContainer::AddSceneObject(const SceneObjectName& name,
    TSceneObject&& sceneObject)
{
    ASSERT(name.empty() == false,
        "Attempt to add an unnamed component.");
    ASSERT(HasObject(name) == false,
        "Object with this name already exists.");

    ObjectHandle handle;
    if (freeHandles.empty() == false) {
        handle = freeHandles.top();
        freeHandles.pop();

        objects[handle] = Entry(name, std::move(sceneObject));
    } else {
        handle = objects.size();
        objects.emplace_back(name, std::move(sceneObject));
    }
    nameMapping[name] = handle;

    return handle;
}

void TSceneObjectContainer::RemoveSceneObject(const SceneObjectName& name) {
    RemoveSceneObject(GetHandle(name));
}

void TSceneObjectContainer::RemoveSceneObject(const ObjectHandle& handle) {
    if (HasObject(handle) == false) {
        return;
    }

    auto& entry = objects.at(handle);
    nameMapping.erase(entry.first);
    entry.first.clear();

    freeHandles.push(handle);
    checkSize();
}

bool TSceneObjectContainer::HasObject(const SceneObjectName& name) const {
    return GetHandle(name) != ObjectHandle::Undefined;
}

bool TSceneObjectContainer::HasObject(const ObjectHandle& handle) const {
    return (handle < objects.size()) &&
        (objects.at(handle).first.empty() == false);
}

void TSceneObjectContainer::Clear() {
    objects.clear();
    objects.shrink_to_fit();
    freeHandles = FreeHandles();
    nameMapping.clear();
}

bool TSceneObjectContainer::IsEmpty() const {
    return objects.empty();
}

void TSceneObjectContainer::checkSize() {
    if (objects.size() == freeHandles.size()) {
        Clear();
    }
}


TSceneObjectContainer::ObjectHandle::ObjectHandle(const size_t& handle) :
    handle(handle)
{}

const TSceneObjectContainer::ObjectHandle::Value&
TSceneObjectContainer::ObjectHandle::GetValue() const {
    return handle;
}

TSceneObjectContainer::ObjectHandle::operator size_t() const {
    return handle;
}

bool TSceneObjectContainer::ObjectHandle::operator == (
    const ObjectHandle& other) const
{
    return handle == other.handle;
}

bool TSceneObjectContainer::ObjectHandle::operator != (
    const ObjectHandle& other) const
{
    return handle != other.handle;
}

} //namespace GE
