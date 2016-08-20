#ifndef LEVEL_SCENE_H
#define LEVEL_SCENE_H

#include "GameEngine/component.h"
#include "GameEngine/scene.h"
#include "GameEngine/game_engine.h"


namespace TD {

class TLevelScene
{
public:
    using Scene = GE::TScene;
    using Object = Scene::Object;
    using ObjectName = Scene::ObjectName;
    using ObjectHandle = Scene::ObjectHandle;
    using ComponentHandle = Scene::ComponentHandle;
    using ComponentName = Scene::ComponentName;
    using ComponentPath = Scene::ComponentPath;
    struct Parameters;

    TLevelScene(const Parameters& info, GE::TGameEngine* engine);

    template<class Component>
    ComponentHandle CreateComponent(const GE::TComponentCreateArgs* args);
    ComponentHandle CreateComponent(const GE::TComponent::ID& id,
        const GE::TComponentCreateArgs* args = nullptr);
    void RemoveComponent(const ComponentHandle& handle);

    ComponentHandle FindComponent(const ComponentPath& path) const;

    bool HasComponent(const ComponentPath& path) const;
    bool HasComponent(const ComponentHandle& handle) const;

    template <class T>
    const T* GetComponent(const ComponentHandle& handle) const;
    template <class T>
    T* GetComponent(const ComponentHandle& handle);
    const GE::TComponent* GetComponent(const ComponentHandle& handle) const;
    GE::TComponent* GetComponent(const ComponentHandle& handle);

    ObjectHandle FindSceneObject(const ObjectName& name) const;

    const Object& GetSceneObject(const ObjectHandle& handle) const;
    Object& GetSceneObject(const ObjectHandle& handle);

    bool HasObject(const ObjectName& name) const;
    bool HasObject(const ObjectHandle& handle) const;

    ObjectHandle AddSceneObject(const ObjectName& name,
        const Object& sceneObject);
    ObjectHandle AddSceneObject(const ObjectName& name, Object&& sceneObject);

    void RemoveSceneObject(const ObjectName& name);
    void RemoveSceneObject(const ObjectHandle& handle);

    void Clear();
    bool IsEmpty() const;

    void Update(const GE::TTime& step);

    void SetGameEngine(GE::TGameEngine* instance);

private:
    Scene scene;

    using PGameEngine = GE::TGameEngine *;
    PGameEngine gameEngine;

    void loadResources(const Parameters& info);
    void loadObjects(const Parameters& info);
};

struct TLevelScene::Parameters
{
    struct ObjectInfo;
    vector<string> resources;
    vector<ObjectInfo> objects;
};

struct TComponentInfo
{
    TLevelScene::ComponentName name;
    GE::ComponentIDs id;
    std::shared_ptr<GE::TComponentCreateArgs> parameters;
};

struct TLevelScene::Parameters::ObjectInfo
{
    TLevelScene::ObjectName name;
    vector<TComponentInfo> components;
};


template<class Component>
TLevelScene::ComponentHandle
TLevelScene::CreateComponent(const GE::TComponentCreateArgs* args) {
    return CreateComponent(GE::ComponentID<Component>::value(), args);
}

template< class T >
const T* TLevelScene::GetComponent(const ComponentHandle& handle) const {
    return dynamic_cast<T*>(GetComponent(handle));
}

template<class T>
T* TLevelScene::GetComponent(const ComponentHandle& handle) {
    return dynamic_cast<T*>(GetComponent(handle));
}

} // namespace TD

#endif // LEVEL_SCENE_H
