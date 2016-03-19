#ifndef SCENE_OBJECT_CONTAINER_H
#define SCENE_OBJECT_CONTAINER_H

#include "scene_object.h"
#include <stack>



class TSceneObjectContainer
{
public:
    using Handle = size_t;
    static constexpr Handle HandleUndefined = (Handle)-1;

    using SceneObject = TSceneObject;
    using Name = string;


    const SceneObject& operator [](const Name& name) const;
    SceneObject& operator [](const Name& name);

    Handle GetHandle(const Name& name) const;

    const SceneObject& operator [](const Handle& handle) const;
    SceneObject& operator [](const Handle& handle);

    Handle AddSceneObject(const Name& name, const TSceneObject& sceneObject);

    void RemoveSceneObject(const Name& name);
    void RemoveSceneObject(const Handle& handle);

    bool HasObject(const Name& name) const;
    bool HasObject(const Handle& handle) const;

    void Clear();

private:
    using NameMapping = std::map<Name, Handle>;
    struct Entry {
        Name name;
        SceneObject object;

        Entry(const Name& name, const SceneObject& object);
    };
    using Objects = vector<Entry>;
    using FreeHandles = std::stack<Handle>;

    NameMapping nameMapping;
    Objects objects;
    FreeHandles freeHandles;


    void checkSize();
};

#endif // SCENE_OBJECT_CONTAINER_H
