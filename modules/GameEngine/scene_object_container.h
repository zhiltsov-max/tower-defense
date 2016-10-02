#ifndef SCENE_OBJECT_CONTAINER_H
#define SCENE_OBJECT_CONTAINER_H

#include <stack>
#include "GameEngine/scene_object.h"


namespace GE {

class TSceneObjectContainer
{
public:
    class ObjectHandle;

    using SceneObject = TSceneObject;
    using SceneObjectName = string;

    const SceneObject& operator [] (const SceneObjectName& name) const;
    SceneObject& operator [] (const SceneObjectName& name);

    const SceneObject& operator [] (const ObjectHandle& handle) const;
    SceneObject& operator [] (const ObjectHandle& handle);

    const SceneObject& GetSceneObject (const SceneObjectName& name) const;
    SceneObject& GetSceneObject (const SceneObjectName& name);

    const SceneObject& GetSceneObject (const ObjectHandle& handle) const;
    SceneObject& GetSceneObject (const ObjectHandle& handle);

    ObjectHandle GetHandle(const SceneObjectName& name) const;

    ObjectHandle AddSceneObject(const SceneObjectName& name,
        const TSceneObject& sceneObject);
    ObjectHandle AddSceneObject(const SceneObjectName& name,
        TSceneObject&& sceneObject);

    void RemoveSceneObject(const SceneObjectName& name);
    void RemoveSceneObject(const ObjectHandle& handle);

    bool HasObject(const SceneObjectName& name) const;
    bool HasObject(const ObjectHandle& handle) const;

    void Clear();
    bool IsEmpty() const;

private:
    using NameMapping = std::map<SceneObjectName, ObjectHandle>;
    using Entry = std::pair<SceneObjectName, SceneObject>;
    using Objects = std::vector<Entry>;
    using FreeHandles = std::stack<ObjectHandle>;

    NameMapping nameMapping;
    Objects objects;
    FreeHandles freeHandles;

    void checkSize();
};

class TSceneObjectContainer::ObjectHandle
{
public:
    using Value = size_t;
    static const ObjectHandle Undefined;

    ObjectHandle(const size_t& handle = -1u);
    operator size_t () const;

    const Value& GetValue() const;

    bool operator == (const ObjectHandle& other) const;
    bool operator != (const ObjectHandle& other) const;

    bool IsNull() const;

private:
    Value handle;
};

} // namespace GE

#endif // SCENE_OBJECT_CONTAINER_H
