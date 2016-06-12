#ifndef LEVEL_SCENE_H
#define LEVEL_SCENE_H

#include "GameEngine/scene.h"
#include "level_info_scene.h"
#include "level_scene_data_game_objects.h"



namespace TD {


class TLevelScene
{
public:
    using ObjectName = Scene::SceneObjects::Name;
    using ObjectHandle = Scene::SceneObjects::Handle;
    using ComponentHandle = Scene::ComponentHandle;

    TLevelScene(const TLevelInfoScene& info, GE::GameEngine& engine);

    const GE::TScene& GetRaw() const;
    GE::TScene& GetRaw();
private:
    using Scene = GE::TScene;
    Scene scene;

    using Objects = TLevelSceneDataGameObjects;
    Objects objects;


    void loadResources(const TLevelInfoScene& info);
    void loadObjects(const TLevelInfoScene& info);
};


} // namespace TD

#endif // LEVEL_SCENE_H
