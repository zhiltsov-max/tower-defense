#include "level_scene.h"



namespace TD {


TLevelScene::TLevelScene(const TLevelInfoScene& info, GE::GameEngine& engine) :
    scene(),
    objects(info)
{
    scene.SetGameEngine(&engine);
    loadResources(info);
    loadObjects(info);
}

const GE::TScene& TLevelScene::GetRaw() const {
    return scene;
}

GE::TScene& TLevelScene::GetRaw() {
    return scene;
}

void TLevelScene::loadResources(const TLevelInfoScene& info) {
    for (const auto& entry : info.resources.data) {
        scene.GetResources().LoadResource(entry);
    }
}

void TLevelScene::loadObjects(const TLevelInfoScene& info) {
    for (const auto& entry : info.objects.data) {
        scene.
    }
}


} // namespace TD
