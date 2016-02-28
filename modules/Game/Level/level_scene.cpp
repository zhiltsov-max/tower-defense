#include "level_scene.h"



namespace TD {

TLevelScene::TLevelScene(const TLevelInfoScene& info) :
    scene()
{
    for(const auto& entry : info.resources.data) {
        scene.GetResources().LoadResource(entry);
    }
}





} // namespace TD
