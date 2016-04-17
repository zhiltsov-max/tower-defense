#ifndef SCENE_OBJECT_CONTAINER_H
#define SCENE_OBJECT_CONTAINER_H

#include "scene_object.h"



class TSceneObjectContainer
{
public:
    using Handle = size_t;
    static const Handle HandleUndefined;

    using SceneObject = TSceneObject;
    using Name = string;


    const SceneObject& operator [] (const Name& name) const;
    SceneObject& operator [] (const Name& name);

    const SceneObject& operator [] (const Handle& handle) const;
    SceneObject& operator [] (const Handle& handle);

    Handle GetHandle(const Name& name) const;

    Handle AddSceneObject(const Name& name, const TSceneObject& sceneObject);
    Handle AddSceneObject(const Name& name, TSceneObject&& sceneObject);

    TSceneObject RemoveSceneObject(const Name& name);
    TSceneObject RemoveSceneObject(const Handle& handle);

    bool HasObject(const Name& name) const;
    bool HasObject(const Handle& handle) const;

    void Clear();
    bool IsEmpty() const;

private:
    using NameMapping = std::map<Name, Handle>;
    using Entry = std::pair<Name, SceneObject>;
    using Objects = vector<Entry>;
    using FreeHandles = std::stack<Handle>;

    NameMapping nameMapping;
    Objects objects;
    FreeHandles freeHandles;

    void checkSize();
};


#endif // SCENE_OBJECT_CONTAINER_H
