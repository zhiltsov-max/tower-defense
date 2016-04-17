#include "scene_object_container.h"



const TSceneObjectContainer::Handle
TSceneObjectContainer::HandleUndefined = -1u;

const TSceneObjectContainer::SceneObject&
TSceneObjectContainer::operator [] (const Name& name) const {
    return objects.at(GetHandle(name)).second;
}

TSceneObjectContainer::SceneObject&
TSceneObjectContainer::operator [] (const Name& name) {
    return objects.at(GetHandle(name)).second;
}

TSceneObjectContainer::Handle
TSceneObjectContainer::GetHandle(const Name& name) const {
    if (nameMapping.count(name) != 0) {
        return nameMapping.at(name);
    } else {
        return HandleUndefined;
    }
}

const TSceneObjectContainer::SceneObject&
TSceneObjectContainer::operator [](const Handle& handle) const {
    return objects.at(handle).second;
}

TSceneObjectContainer::SceneObject&
TSceneObjectContainer::operator [](const Handle& handle) {
    return objects.at(handle).second;
}

TSceneObjectContainer::Handle
TSceneObjectContainer::AddSceneObject(const Name& name,
    const TSceneObject& sceneObject)
{
    ASSERT(name.empty() == false,
        "Attempt to add an unnamed component.");
    ASSERT(HasObject(name) == false,
        "Object with this name already exists.");

    Handle handle = HandleUndefined;
    if (freeHandles.empty() == false) {
        handle = freeHandles.top();
        freeHandles.pop();

        objects[handle] = std::move(Entry(name, sceneObject));
    } else {
        handle = objects.size();
        objects.emplace_back(name, sceneObject);
    }
    nameMapping[name] = handle;

    return handle;
}

TSceneObjectContainer::Handle
TSceneObjectContainer::AddSceneObject(const Name& name,
    TSceneObject&& sceneObject)
{
    ASSERT(name.empty() == false,
        "Attempt to add an unnamed component.");
    ASSERT(HasObject(name) == false,
        "Object with this name already exists.");

    Handle handle = HandleUndefined;
    if (freeHandles.empty() == false) {
        handle = freeHandles.top();
        freeHandles.pop();

        objects[handle] = std::move(Entry(name, std::move(sceneObject)));
    } else {
        handle = objects.size();
        objects.emplace_back(name, std::move(sceneObject));
    }
    nameMapping[name] = handle;

    return handle;
}

TSceneObject TSceneObjectContainer::RemoveSceneObject(const Name& name) {
    Handle handle = GetHandle(name);
    return std::move(RemoveSceneObject(handle));
}

TSceneObject TSceneObjectContainer::RemoveSceneObject(const Handle& handle) {
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

bool TSceneObjectContainer::HasObject(const Name& name) const {
    return GetHandle(name) != HandleUndefined;
}

bool TSceneObjectContainer::HasObject(const Handle& handle) const {
    return (handle < objects.size()) &&
        (objects.at(handle).first.empty() == false);
}

void TSceneObjectContainer::Clear() {
    objects.clear();
    objects.shrink_to_fit();
    freeHandles = std::move(FreeHandles());
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
