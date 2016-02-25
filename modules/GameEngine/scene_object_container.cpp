#include "scene_object_container.h"



const TSceneObjectContainer::SceneObject&
TSceneObjectContainer::operator [](const Name& name) const {
    return objects[GetHandle(name)].object;
}

TSceneObjectContainer::SceneObject&
TSceneObjectContainer::operator [](const Name& name) {
    return objects[GetHandle(name)].object;
}

TSceneObjectContainer::Handle
TSceneObjectContainer::GetHandle(const Name& name) const {
    if (nameMapping.count(name) != 0) {
        return nameMapping[name];
    } else {
        return HandleUndefined;
    }
}

const TSceneObjectContainer::SceneObject&
TSceneObjectContainer::operator [](const Handle& handle) const {
    return objects[handle].object;
}

TSceneObjectContainer::SceneObject&
TSceneObjectContainer::operator [](const Handle& handle) {
    return objects[handle].object;
}

TSceneObjectContainer::Handle
TSceneObjectContainer::AddSceneObject(const Name& name,
    const TSceneObject& sceneObject)
{
    ASSERT(HasObject(name) == false,
        "Object with this name already exists.");

    Handle handle = HandleUndefined;
    if (freeHandles.empty() == false) {
        handle = freeHandles.top();
        freeHandles.pop();

        objects[handle] = sceneObject;
    } else {
        handle = objects.size();
        objects.push_back(sceneObject);
    }
    return handle;
}

void TSceneObjectContainer::RemoveSceneObject(const Name& name) {
    Handle handle = GetHandle(name);
    RemoveSceneObject(handle);
}

void TSceneObjectContainer::RemoveSceneObject(const Handle& handle) {
    ASSERT(handle != HandleUndefined,
        "Attempt to remove an unexisting object")
    ASSERT(objects[handle].name.empty() == false,
        "Attempt to remove an unexisting object")

    objects[handle].name.clear();
    nameMapping.erase(name);

    freeHandles.push(handle);
    checkSize();
}

bool TSceneObjectContainer::HasObject(const Name& name) const {
    return GetHandle(name) != HandleUndefined;
}

bool TSceneObjectContainer::HasObject(const Handle& handle) const {
    return objects[handle].name.empty() == false;
}

void TSceneObjectContainer::Clear() {
    objects.clear();
    freeHandles.swap(FreeHandles());
    nameMapping.clear();
}

void TSceneObjectContainer::checkSize() {
    if (objects.size() == freeHandles.size()) {
        Clear();
    }
}