#ifndef SCENE_INFO_H
#define SCENE_INFO_H

#include "level_info_raw.h"
#include "Game/Components/game_objects_info.h"
#include <forward_list>



namespace TD {


namespace LevelSceneInfo {


static const string Resources = "resources";
static const string Objects = "objects";


} //namespace SceneInfo


struct TLevelInfoSceneResources {
    using TLevelSceneResourceHash = string;
    using Resources = std::forward_list<TLevelSceneResourceHash>;
    Resources data;


    TLevelInfoSceneResources(const TRawLevelInfo& info);
};


struct TLevelInfoSceneObjects {
    using TLevelSceneObject = TNamedData<string>;
    using Objects = std::forward_list<TLevelSceneObject>;
    Objects data;


    TLevelInfoSceneObjects(const TRawLevelInfo& source);
};


struct TLevelInfoScene {
    TLevelInfoSceneResources resources;
    TLevelInfoSceneObjects objects;


    TSceneInfo(const TRawLevelInfo& info);
};


} // namespace TD

#endif //SCENE_INFO_H
