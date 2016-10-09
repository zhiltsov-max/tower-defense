#ifndef SCENE_OBJECT_MANAGER_H
#define SCENE_OBJECT_MANAGER_H

#include "GameEngine/free_list_allocator.h"
#include "GameEngine/observable_interface.h"
#include "GameEngine/scene_object.h"


namespace GE {

class TSceneComponentManager;

class TSceneObjectManager
{
public:
    class ObjectHandle;
    using SceneObject = TSceneObject;
    using SceneObjectName = string;
private:
    using NameMapping = std::map<SceneObjectName, ObjectHandle>;
    using Entry = std::pair<SceneObjectName, SceneObject>;
public:
    using EntriesRange = std::pair<
        NameMapping::iterator,
        NameMapping::iterator
    >;
    using EntriesConstRange = std::pair<
        NameMapping::const_iterator,
        NameMapping::const_iterator
    >;

    TSceneObjectManager();
    TSceneObjectManager(
        const TSceneObjectManager& other) = delete; // can't copy ownership
    TSceneObjectManager& operator = (
        const TSceneObjectManager& other) = delete; // can't copy ownership
    TSceneObjectManager(TSceneObjectManager&& other);
    TSceneObjectManager& operator = (TSceneObjectManager&& other);

    const SceneObject& operator [] (const SceneObjectName& name) const;
    SceneObject& operator [] (const SceneObjectName& name);

    const SceneObject& operator [] (const ObjectHandle& handle) const;
    SceneObject& operator [] (const ObjectHandle& handle);

    const SceneObject& GetSceneObject(const SceneObjectName& name) const;
    SceneObject& GetSceneObject(const SceneObjectName& name);

    const SceneObject& GetSceneObject(const ObjectHandle& handle) const;
    SceneObject& GetSceneObject(const ObjectHandle& handle);

    ObjectHandle GetHandle(const SceneObjectName& name) const;

    std::pair<ObjectHandle, SceneObject&> CreateSceneObject(
        const SceneObjectName& name);
    std::pair<ObjectHandle, SceneObject&> CreateSceneObject(
        const SceneObjectName& name, TSceneObject&& object);

    void RemoveSceneObject(const SceneObjectName& name);
    void RemoveSceneObject(const ObjectHandle& handle);

    bool HasObject(const SceneObjectName& name) const;
    bool HasObject(const ObjectHandle& handle) const;

    void Clear();
    bool IsEmpty() const;

    void SetSceneComponentManager(TSceneComponentManager* instance);

    EntriesConstRange EnumerateEntries() const;
    EntriesRange EnumerateEntries();

private:
    using ObjectsAllocator = FreelistAllocator<Entry>;
    NameMapping nameMapping;
    ObjectsAllocator objectsAllocator;

    using PSceneComponentManager = TSceneComponentManager *;
    PSceneComponentManager componentManager;

protected:
    class SceneObjectMessageObserver :
        public IObserver<TSceneObjectMessage>
    {
    public:
        SceneObjectMessageObserver(TSceneObjectManager* owner = nullptr);
        void SetOwner(TSceneObjectManager* instance);

        void RecieveMessage(const TSceneObjectMessage& message,
            const ObjectHandle& source);
    private:
        TSceneObjectManager* owner;

        void handleMessage_ComponentAdded(
            const TSceneObjectMessage::ComponentAddedMessage& message,
            const ObjectHandle& source);
        void handleMessage_ComponentRemoved(
            const TSceneObjectMessage::ComponentRemovedMessage& message,
            const ObjectHandle& source);
    };

private:
    SceneObjectMessageObserver sceneObjectMessageObserver;
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
