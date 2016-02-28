#ifndef LEVEL_SCENE_H
#define LEVEL_SCENE_H

#include "GameEngine/scene.h"
#include "level_info_scene.h"



namespace TD {


class TLevelScene
{
public:
    TLevelScene(const TLevelInfoScene& info);

private:
    using Scene = TScene;
    Scene scene;
};


} // namespace TD

#endif // LEVEL_SCENE_H
