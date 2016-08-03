#ifndef SCENE_COMPONENT_MANAGER_H
#define SCENE_COMPONENT_MANAGER_H

#include "Core/core.h"
#include "GameEngine/scene_object.h"


namespace GE {

class TSceneComponentManager
{
public:
    using ComponentHandle = TSceneObject::ComponentHandle;

    ComponentHandle CreateComponent(const TComponent::ID& id,
        const TComponentCreateArgs* args = nullptr
    );

    bool HasComponent(const ComponentHandle& handle) const;

    void RemoveComponent(const ComponentHandle& handle);

    const TComponent* GetComponent(const ComponentHandle& handle) const;
    TComponent* GetComponent(const ComponentHandle& handle);

    template <class T>
    const T* GetComponent(const ComponentHandle& handle) const;
    template <class T>
    T* GetComponent(const ComponentHandle& handle);

    void SetGameEngine(TGameEngine* instance);

    bool IsEmpty() const;
    void Clear();

private:
    using PGameEngine = TGameEngine *;
    PGameEngine engine;
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

} //namespace GE

#endif // SCENE_COMPONENT_MANAGER_H
