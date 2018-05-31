#ifndef SCENE_COMPONENT_MANAGER_H
#define SCENE_COMPONENT_MANAGER_H

#include <unordered_map>
#include "Core/core.h"
#include "GameEngine/component_systems_manager.h"
#include "GameEngine/scene_object.h"
#include "GameEngine/scene_object_manager.h"


namespace GE {

class TSceneComponentManager
{
public:
    using ComponentHandle = TComponentHandle;
    using SceneObjectHandle = TSceneObjectManager::ObjectHandle;
    using ComponentPath = std::pair<
        SceneObjectHandle,
        TSceneObjectManager::SceneObject::EntryHandle
    >;
private:
    using ComponentHandleHasher = size_t (*)(const ComponentHandle&);
    using ComponentBindingsTable = std::unordered_map<
        ComponentHandle, ComponentPath, ComponentHandleHasher>;
public:
    using EntriesConstRange = std::pair<
        ComponentBindingsTable::const_iterator,
        ComponentBindingsTable::const_iterator
    >;
    using EntriesRange = std::pair<
        ComponentBindingsTable::iterator,
        ComponentBindingsTable::iterator
    >;

    TSceneComponentManager();

    ComponentHandle CreateComponent(const TComponent::ID& id,
        const TComponentCreateArgs* args = nullptr);
    bool HasComponent(const ComponentHandle& handle) const;
    void RemoveComponent(const ComponentHandle& handle);

    const TComponent* GetComponent(const ComponentHandle& handle) const;
    TComponent* GetComponent(const ComponentHandle& handle);

    template<class T>
    const T* GetComponent(const ComponentHandle& handle) const;
    template<class T>
    T* GetComponent(const ComponentHandle& handle);

    void SetGameEngine(TGameEngine* instance);
    void SetSceneObjectManager(TSceneObjectManager* instance);

    bool IsEmpty() const;
    void Clear();

    void BindComponent(const ComponentHandle& componentHandle,
        const ComponentPath& componentPath);
    void UnbindComponent(const ComponentHandle& componentHandle);
    bool IsComponentBound(const ComponentHandle& componentHandle);
    const ComponentPath& GetComponentBinding(
        const ComponentHandle& componentHandle) const;
    ComponentPath GetComponentBinding(
        const ComponentHandle& componentHandle);

    EntriesConstRange EnumerateEntries() const;
    EntriesRange EnumerateEntries();

private:
    using PGameEngine = TGameEngine *;
    PGameEngine engine;

    using PSceneObjectManager = TSceneObjectManager *;
    PSceneObjectManager sceneObjectManager;

    static size_t hashComponentHandle(const ComponentHandle& handle);
    ComponentBindingsTable componentBindingsTable;
};


template< class T >
const T*
TSceneComponentManager::GetComponent(const ComponentHandle& handle) const {
    return dynamic_cast<const T*>(GetComponent(handle));
}

template< class T >
T* TSceneComponentManager::GetComponent(
    const TSceneComponentManager::ComponentHandle& handle)
{
    return dynamic_cast<T*>(GetComponent(handle));
}

} // namespace GE

#endif // SCENE_COMPONENT_MANAGER_H
