#include "scene_object_container.h"


namespace GE {

const TSceneObjectContainer::ObjectHandle
TSceneObjectContainer::HandleUndefined = -1u;

const TSceneObjectContainer::SceneObject&
TSceneObjectContainer::operator [] (const SceneObjectName& name) const {
    return objects.at(GetHandle(name)).second;
}

TSceneObjectContainer::SceneObject&
TSceneObjectContainer::operator [] (const SceneObjectName& name) {
    return objects.at(GetHandle(name)).second;
}

TSceneObjectContainer::ObjectHandle
TSceneObjectContainer::GetHandle(const SceneObjectName& name) const {
    if (nameMapping.count(name) != 0) {
        return nameMapping.at(name);
    } else {
        return HandleUndefined;
    }
}

const TSceneObjectContainer::SceneObject&
TSceneObjectContainer::operator [](const ObjectHandle& handle) const {
    return objects.at(handle).second;
}

TSceneObjectContainer::SceneObject&
TSceneObjectContainer::operator [](const ObjectHandle& handle) {
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

    ObjectHandle handle = HandleUndefined;
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

    ObjectHandle handle = HandleUndefined;
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

TSceneObject
TSceneObjectContainer::RemoveSceneObject(const SceneObjectName& name) {
    ObjectHandle handle = GetHandle(name);
    return RemoveSceneObject(handle);
}

TSceneObject
TSceneObjectContainer::RemoveSceneObject(const ObjectHandle& handle) {
    ASSERT(handle != HandleUndefined,
        "Attempt to remove an unexisting object")
    ASSERT(objects.at(handle).first.empty() == false,
        "Attempt to remove an unexisting object")

    auto& entry = objects.at(handle);
    nameMapping.erase(entry.first);
    entry.first.clear();
    auto object = std::move(entry.second);

    freeHandles.push(handle);
    checkSize();

    return object;
}

bool TSceneObjectContainer::HasObject(const SceneObjectName& name) const {
    return GetHandle(name) != HandleUndefined;
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

} //namespace GE
