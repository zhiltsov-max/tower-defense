#ifndef LEVEL_SCENE_H
#define LEVEL_SCENE_H

#include "GameEngine/scene.h"
#include "Game/Components/components_list.h"
#include "Game/Level/level_info.h"


namespace TD {

class TLevelScene
{
public:
    using Object = Scene::SceneObjects::SceneObject;
    using ObjectName = Scene::SceneObjects::Name;
    using ObjectHandle = Scene::SceneObjects::Handle;
    using ComponentHandle = Scene::ComponentHandle;

    TLevelScene(const TLevelInfoScene& info, GE::GameEngine& engine);

    template<class Component>
    ComponentHandle CreateComponent(TComponentCreateArgs* args);
    ComponentHandle CreateComponent(const GE::TComponent::ID& id,
        const GE::TComponentCreateArgs* args = nullptr
    );
    void RemoveComponent(const ComponentHandle& handle);

    template <class T>
    T* GetComponent(const ComponentHandle& handle);
    GE::TComponent* GetComponent(const ComponentHandle& handle);

    const Object& FindObject(const ObjectName& name) const;
    Object& FindObject(const ObjectName& name);
    const Object& FindObject(const ObjectHandle& handle) const;
    Object& FindObject(const ObjectHandle& handle);

    bool HasObject(const ObjectName& name) const;
    bool HasObject(const ObjectHandle& handle) const;

    ObjectHandle GetHandle(const ObjectName& name) const;

    ObjectHandle AddSceneObject(const ObjectName& name,
        const Object& sceneObject);
    ObjectHandle AddSceneObject(const ObjectName& name, Object&& sceneObject);

    Object RemoveSceneObject(const ObjectName& name);
    Object RemoveSceneObject(const ObjectHandle& handle);

    void Clear();
    bool IsEmpty() const;

private:
    using Scene = GE::TScene;
    Scene scene;

    void loadResources(const TLevelInfoScene& info);
    void loadObjects(const TLevelInfoScene& info);
};

template<class Component>
TLevelScene::ComponentHandle
TLevelScene::CreateComponent(GE::TComponentCreateArgs* args) {
    return CreateComponent(static_cast<uint>(GE::ComponentID<Component>::value),
        args);
}

template<class T>
T* TLevelScene::GetComponent(const ComponentHandle& handle) {
    return dynamic_cast<T*>(GetComponent(handle));
}

} // namespace TD

#endif // LEVEL_SCENE_H
