#ifndef SCENE_OBJECT_CONTAINER_H
#define SCENE_OBJECT_CONTAINER_H

#include "GameEngine/scene_object.h"


namespace GE {

class TSceneObjectContainer
{
public:
    using ObjectHandle = size_t;
    static const ObjectHandle HandleUndefined;

    using SceneObject = TSceneObject;
    using SceneObjectName = string;

    const SceneObject& operator [] (const SceneObjectName& name) const;
    SceneObject& operator [] (const SceneObjectName& name);

    const SceneObject& operator [] (const ObjectHandle& handle) const;
    SceneObject& operator [] (const ObjectHandle& handle);

    ObjectHandle GetHandle(const SceneObjectName& name) const;

    ObjectHandle AddSceneObject(const SceneObjectName& name,
        const TSceneObject& sceneObject);
    ObjectHandle AddSceneObject(const SceneObjectName& name,
        TSceneObject&& sceneObject);

    TSceneObject RemoveSceneObject(const SceneObjectName& name);
    TSceneObject RemoveSceneObject(const ObjectHandle& handle);

    bool HasObject(const SceneObjectName& name) const;
    bool HasObject(const ObjectHandle& handle) const;

    void Clear();
    bool IsEmpty() const;

private:
    using NameMapping = std::map<SceneObjectName, ObjectHandle>;
    using Entry = std::pair<SceneObjectName, SceneObject>;
    using Objects = vector<Entry>;
    using FreeHandles = std::stack<ObjectHandle>;

    NameMapping nameMapping;
    Objects objects;
    FreeHandles freeHandles;

    void checkSize();
};

} //namespace GE

#endif // SCENE_OBJECT_CONTAINER_H
