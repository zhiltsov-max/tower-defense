#include "level_info_scene.h"



namespace TD {


TLevelInfoSceneResources::TLevelInfoSceneResources(const TRawLevelInfo& source) :
    data()
{
    const int count = std::stoi(source["size"]);
    if (count == 0) {
        return;
    }

    for(int i = 0; i < count; ++i) {
        const string key = std::to_string(i);
        data.emplace_front(std::move(source[key]));
    }
}


TLevelInfoSceneObjects::TLevelInfoSceneObjects(const TRawLevelInfo& source) :
    data()
{
    const int count = std::stoi(source["size"]);
    if (count == 0) {
        return;
    }

    for(int i = 0; i < count; ++i) {
        const string key = std::to_string(i);
        data.emplace_front(std::move(source.slice(key)));
    }
}


TLevelInfoScene::TSceneInfo(const TRawLevelInfo& info) :
    resources(info.slice(LevelSceneInfo::Resources)),
    objects(info.slice(LevelSceneInfo::Objects))
{}



} // namespace TD
