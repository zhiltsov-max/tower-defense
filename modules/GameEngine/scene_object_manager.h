#ifndef SCENE_OBJECT_MANAGER_H
#define SCENE_OBJECT_MANAGER_H

#include "GameEngine/free_list_allocator.h"
#include "GameEngine/observable_interface.h"
#include "GameEngine/scene_object.h"


namespace GE {

class TSceneObjectManager
{
public:
    class ObjectHandle;
    using SceneObject = TSceneObject;
    using SceneObjectName = string;

    const SceneObject& operator [] (const SceneObjectName& name) const;
    SceneObject& operator [] (const SceneObjectName& name);

    const SceneObject& operator [] (const ObjectHandle& handle) const;
    SceneObject& operator [] (const ObjectHandle& handle);

    const SceneObject& GetSceneObject(const SceneObjectName& name) const;
    SceneObject& GetSceneObject(const SceneObjectName& name);

    const SceneObject& GetSceneObject(const ObjectHandle& handle) const;
    SceneObject& GetSceneObject(const ObjectHandle& handle);

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
    using ObjectsAllocator = FreelistAllocator<Entry>;

    NameMapping nameMapping;
    ObjectsAllocator objectsAllocator;

    // IObserver<TSceneObjectMessage, ObjectHandle> support
private:
    void RecieveMessage(const TSceneObjectMessage& message,
        const ObjectHandle& source);
    void handleMessage_SceneObjectComponentAdded(
        const TSceneObjectMessage::ComponentAddedMessage& message,
        const ObjectHandle& source);
    void handleMessage_SceneObjectComponentRemoved(
        const TSceneObjectMessage::ComponentRemovedMessage& message,
        const ObjectHandle& source);
};

class TSceneObjectManager::ObjectHandle
{
public:
    using Value = ObjectsAllocator::Handle;
    static const ObjectHandle Undefined;

    ObjectHandle(const Value& handle = Undefined);
    operator Value () const;

    const Value& GetValue() const;

    bool operator == (const ObjectHandle& other) const;
    bool operator != (const ObjectHandle& other) const;

    bool IsNull() const;

private:
    Value handle;
};

} // namespace GE

#endif // SCENE_OBJECT_MANAGER_H
