#ifndef LEVEL_INFO_LOADER_IMPL_H
#define LEVEL_INFO_LOADER_IMPL_H

#include "Core/core.h"
#include "Game/Level/level_info_raw.h"
#include "Game/Level/level_info.h"
#include "Game/Components/components_list.h"
#include "Game/Map/level_node_map.h"
#include "Game/Map/level_tile_map.h"
#include "Game/Map/level_passability_map.h"
#include "Game/Player/player_credits.h"
#include "Game/Player/player_progress.h"
#include "Game/Player/player_quests.h"
#include "Game/Player/player_researches.h"
#include "Game/Player/player_statistics.h"
#include <functional>


namespace TD {

template <typename T>
T readFromRawLevelInfo(const TRawLevelInfo& source);

template <typename T>
T readFromString(const string& source);

template <typename Component>
std::unique_ptr<GE::TComponentCreateArgs>
readComponentInfo(const TRawLevelInfo& source);


vector<string>
readSequence(const string& source, const string& separator = ",") {
    if (source.empty() == true) {
        return {};
    }
    const auto bracket1 = source.find('[');
    const auto bracket2 = source.rfind(']');
    if ((bracket2 <= bracket1) || (bracket2 == source.npos)) {
        THROW("Failed to read a sequence: wrong format.");
    }
    return String::split(source.substr(bracket1, bracket2), separator);
}

template <typename T, typename Convert>
vector<T> readSequence(const string& source, const Convert& convert,
    const string& separator = ",")
{
    if (source.empty() == true) {
        return {};
    }
    const auto bracket1 = source.find('[');
    const auto bracket2 = source.rfind(']');
    if ((bracket2 <= bracket1) || (bracket2 == source.npos)) {
        THROW("Failed to read a sequence: wrong format.");
    }
    const auto raw = String::split(
        source.substr(source.substr(bracket1, bracket2)), separator);
    vector<T> result;
    std::transform(raw.begin(), raw.end(), result.begin(), convert);
    return result;
}

template <typename R, typename Arg>
struct _readArray {
    using F = R(Arg);
    static vector<R> read(const TRawLevelInfo& source, const F& f);
};

template <typename R>
struct _readArray<R, string> {
    using F = R(Arg);
    static vector<R> read(const TRawLevelInfo& source, const F& convert) {
        const size_t count = std::max(std::stoi(source["size"]), 0);
        if (count == 0) {
            return {};
        }

        vector<R> result;
        result.reserve(count);
        size_t i = 0;
        for (; i < count; ++i) {
            result.emplace_back(std::move(f(source[std::to_string(i)])));
        }
        if (i != count) {
            THROW("Failed to read an array: not enoungh entries presented.");
        }
        return result;
    }
};

template <typename R>
struct _readArray<R, TRawLevelInfo> {
    using F = R(Arg);
    static vector<R> read(const TRawLevelInfo& source, const F& f) {
        const size_t count = std::max(std::stoi(source["size"]), 0);
        if (count == 0) {
            return {};
        }

        vector<R> result;
        result.reserve(count);
        size_t i = 0;
        for (; i < count; ++i) {
            result.emplace_back(std::move(f(source.slice(std::to_string(i)))));
        }
        if (i != count) {
            THROW("Failed to read an array: not enoungh entries presented.");
        }
        return result;
    }
};

template <typename T, typename Convert>
vector<T> readArray(const TRawLevelInfo& source, const Convert& convert) {
    return _readArray::read(source, convert);
}

template <typename T = TNamedData<string>>
vector<T> readArray(const TRawLevelInfo& source) {
    return readArray<T, decltype(readFromRawLevelInfo<T>)>(
        source, readFromRawLevelInfo<T>);
}

template <>
vector<string> readArray<string>(const TRawLevelInfo& source) {
    return readArray(source, readFromString<string>);
}

template <>
TNamedData<string> readFromRawLevelInfo<TNamedData<string>>(
    const TRawLevelInfo& source)
{
    return source;
}

template <>
string readFromString<string>(const string& source) {
    return source;
}

template <>
Vec2ui readFromRawLevelInfo(const TRawLevelInfo& source) {
    Vec2ui info;
    info.x = std::stoul(source["x"]);
    info.y = std::stoul(source["y"]);
    return info;
}

template <>
Vec2ui readFromString(const string& source) {
    const auto coordinates = readSequence<uint>(source, std::stoul);
    ASSERT(coordinates.size() == 2, "Expected 2 coordinates.");
    return {coordinates[0], coordinates[1]};
}

namespace CommonLevelInfo {
static constexpr string NextLevelCode = "nextLevel";
static constexpr string LoadingScript = "loadingScript";
static constexpr string LevelType = "type";
static constexpr string LevelType_Normal = "normal";
static constexpr string LevelType_Free = "free";
} // namespace CommonLevelInfo

template <>
TLevelInfoCommon
readFromRawLevelInfo<TLevelInfoCommon>(const TRawLevelInfo& source) {
    TLevelInfoCommon info;
    info.levelCode;
    info.nextLevelCode = source[CommonLevelInfo::NextLevelCode];
    info.loadingScript = source[CommonLevelInfo::LoadingScript];
    info.levelType = LevelType::Undefined;
    const auto& type = source[CommonLevelInfo::LevelType];
    switch (type) {
    case CommonLevelInfo::LevelType_Normal:
        levelType = LevelType::Normal;
        break;
    case CommonLevelInfo::LevelType_Free:
        levelType = LevelType::Free;
        break;
    default:
        THROW("Unexpected level type: " + type)
    }
    return info;
}


namespace MobSequenceEntryInfo {
static constexpr string CountSign = "*";
static const string RandomSign = "R";
} // namespace MobSequenceInfo

template <>
TLevelInfoMobSequenceEntry
readFromString<TLevelInfoMobSequenceEntry>(const string& source) {
    TLevelInfoMobSequenceEntry info;
    const auto parts = String::split(*it, MobSequenceEntryInfo::CountSign);
    info.id = 0;
    if (parts[0] != MobSequenceEntryInfo::RandomSign) {
        info.id = std::stoi(parts[0]);
    }
    info.count = std::max(1, std::stoi(parts[1]));
    return info;
}

namespace MobsInfo {
static constexpr string Delay = "delay";
static constexpr string Sequence = "sequence";
} // namespace MobsInfo

template <>
std::unique_ptr<GE::TComponentCreateArgs>
readComponentInfo<TLevelMobsControllerInfo>(const TRawLevelInfo& source) {
    std::unique_ptr<TLevelMobsControllerInfo> info;
    info->sequence = readSequence<TLevelInfoMobSequenceEntry>(
        source.slice(MobsInfo::Sequence),
        readFromString<TLevelInfoMobSequenceEntry>);
    info->delay = std::stof(source[MobsInfo::Delay]);
    return info;
}


namespace BuildingsInfo {
static constexpr string Restricted = "restricted";
static constexpr string Allowed = "allowed";
static constexpr string MaxCount = "maxCount";
} // namespace BuildingsInfo

template <>
std::unique_ptr<GE::TComponentCreateArgs>
readComponentInfo<TLevelBuildingsControllerInfo>(const TRawLevelInfo& source) {
    std::unique_ptr<TLevelBuildingsControllerInfo> info;
    info->restricted = readSequence<TBuildingClassId>(
        source[BuildingsInfo::Restricted], std::stoi);
    info->allowed = readSequence<TBuildingClassId>(
        source[BuildingsInfo::Allowed], std::stoi);
    info->maxCount = std::max(std::stoi(source[BuildingsInfo::MaxCount]), 0);
    return info;
}


namespace ResearchesInfo {
static constexpr string Restricted = "restricted";
static constexpr string Allowed = "allowed";
static constexpr string MaxCount = "maxCount";
static constexpr string separator = ",";
} // namespace ResearchesInfo

template <>
std::unique_ptr<GE::TComponentCreateArgs>
readComponentInfo<TLevelResearchesControllerInfo>(const TRawLevelInfo& source) {
    std::unique_ptr<TLevelResearchesControllerInfo> info;
    info->restricted = readSequence<TResearchClassId>(
        source[ResearchesInfo::Restricted], std::stoi);
    info->allowed = readSequence<TResearchClassId>(
        source[ResearchesInfo::Allowed], std::stoi);
    info->maxCount = std::max(std::stoi(source[ResearchesInfo::MaxCount]), 0);
    return info;
}


namespace QuestsInfo {
} // namespace QuestsInfo

template <>
std::unique_ptr<GE::TComponentCreateArgs>
readComponentInfo<TLevelQuestsControllerInfo>(const TRawLevelInfo& source) {
    std::unique_ptr<TLevelQuestsControllerInfo> info;
    //TODO: ...
    return info;
}


namespace NodeMapInfo {
static constexpr string Size = "size";
static constexpr string Pathes = "pathes";
static constexpr string Enters = "enters";
static constexpr string Exits = "exits";
} // namespace NodeMapInfo

template <>
std::unique_ptr<GE::TComponentCreateArgs>
readComponentInfo<TLevelNodeMapInfo>(const TRawLevelInfo& source) {
    std::unique_ptr<TLevelNodeMapInfo> info;
    info->pathes = readArray< vector<Vec2ui> >(source.slice(NodeMapInfo::Pathes),
        readArray<Vec2ui>);
    info->enters = readArray<Vec2ui>(source.slice(NodeMapInfo::Enters),
        readFromString<Vec2ui>);
    info->exits = readArray<Vec2ui>(source.slice(NodeMapInfo::Exits),
        readFromString<Vec2ui>);
    return info;
}

namespace TileMapLayerInfo {
static constexpr string Tiles = "tiles";
} // namespace TileMapLayerInfo

template <>
TLevelInfoTileMapLayer
readFromRawLevelInfo<TLevelInfoTileMapLayer>(const TRawLevelInfo& source) {
    TLevelInfoTileMapLayer info;
    info.tiles = readSequence<int>(source[TileMapLayerInfo::Tiles], std::stoi);
    return info;
}

namespace TileMapInfo {
static constexpr string Size = "size";
static constexpr string Layers = "layers";
} // namespace TileMapInfo

template <>
std::unique_ptr<GE::TComponentCreateArgs>
readComponentInfo<TLevelTileMapInfo>(const TRawLevelInfo& source) {
    std::unique_ptr<TLevelTileMapInfo> info;
    info->size = readFromString<Vec2ui>(source[TileMapInfo::Size]);
    info->layers = readArray<TLevelInfoTileMapLayer>(
        source.slice(TileMapInfo::Layers));
    return info;
}


namespace StageInfo {
static constexpr string Mobs = "mobs";
static constexpr string Buildings = "buildings";
static constexpr string Researches = "researches";
static constexpr string Quests = "quests";
static constexpr string Map = "map";
static constexpr string Scripts = "scripts";
} // namespace StageInfo

template <>
TLevelInfoStage
readFromRawLevelInfo<TLevelInfoStage>(const TRawLevelInfo& source) {
    TLevelInfoStage info;
    info.scene = readFromRawLevelInfo<TLevelInfoScene>(
        source.slice(StageInfo::Mobs));
    return info;
}

using ComponentInfoReader = std::function<
    std::unique_ptr<GE::TComponentCreateArgs>(const TRawLevelInfo& source)
>;
static constexpr std::map<GE::TComponentIDs, ComponentInfoReader>
componentInfoTable = {
    // list of pairs {id, reader}
//    {GE::ComponentIDs::PlayerStatistics,},
//    {GE::ComponentIDs::PlayerProgress,},
//    {GE::ComponentIDs::PlayerQuests,},
//    {GE::ComponentIDs::PlayerResearches,},
//    {GE::ComponentIDs::PlayerCredits,},

//    {GE::ComponentIDs::ResearchesTreeView,},
//    {GE::ComponentIDs::ResearchesTreeItemView,},

    {GE::ComponentIDs::LevelTileMap, readComponentInfo<TLevelTileMapInfo>},
    {GE::ComponentIDs::LevelTileMapView, readComponentInfo<TLevelTileMapViewInfo},
    {GE::ComponentIDs::LevelNodeMap, readComponentInfo<TLevelNodeMapInfo>},
//    {GE::ComponentIDs::LevelNodeMapView,}, //TODO: debug only?
    {GE::ComponentIDs::LevelPassabilityMap, readComponentInfo<TLevelPassabilityMapInfo},
//    {GE::ComponentIDs::LevelPassabilityMapView,}, //TODO: debug only?

    {GE::ComponentIDs::LevelBuildingsController, readComponentInfo<TLevelBuildingsControllerInfo>},
    {GE::ComponentIDs::LevelMobsController, readComponentInfo<TLevelMobsControllerInfo>},
    {GE::ComponentIDs::LevelQuestsController, readComponentInfo<TLevelQuestsControllerInfo>},
    {GE::ComponentIDs::LevelResearchesController, readComponentInfo<TLevelResearchesControllerInfo>}
};

std::unique_ptr<TComponentInfo>
readComponentInfo(const GE::TComponentIDs& id, const TRawLevelInfo& source) {
    return componentInfoTable[id](source);
}

namespace ComponentInfo {
static constexpr string Name = "name";
static constexpr string Id = "id";
static constexpr string Parameters = "parameters";
} // namespace ComponentInfo

template <>
readFromRawLevelInfo<TComponentInfo>(const TRawLevelInfo& source) {
    TComponentInfo info;
    info.name = source[ComponentInfo::Name];
    info.id = std::stoul(source[ComponentInfo::Id]);
    info.parameters = std::move(readComponentInfo(info.id, source));
    return info;
}


namespace SceneObjectInfo {
static constexpr string Name = "name";
static constexpr string Components = "components";
};

template <>
readFromRawLevelInfo<TSceneObjectInfo>(const TRawLevelInfo& source) {
    TSceneObjectInfo info;
    info.name = source[SceneObjectInfo::Name];
    info.components = readArray<TComponentInfo>(
        source.slice(SceneObjectInfo::Components));
    return info;
}


namespace LevelSceneInfo {
static constexpr string Resources = "resources";
static constexpr string Objects = "objects";
} // namespace SceneInfo

template <>
TLevelInfoScene
readFromRawLevelInfo<TLevelInfoScene>(const TRawLevelInfo& source) {
    TLevelInfoScene info;
    info.resources = readArray<string>(
        source.slice(LevelSceneInfo::Resources));
    info.objects = readArray<TSceneObjectInfo>(
        source.slice(LevelSceneInfo::Objects));
    return info;
}


namespace LevelInfo {
static constexpr string Common = "common";
static constexpr string Scene = "scene";
static constexpr string Stages = "stages";
} // namespace LevelInfo

template <>
TLevelInfo
readFromRawLevelInfo<TLevelInfo>(const TRawLevelInfo& source) {
    TLevelInfo info;
    info.common = readFromRawLevelInfo<TLevelInfoCommon>(
        source.slice(LevelInfo::Common));
    info.stages = readArray<TLevelInfoStage>(LevelInfo::Stages);
    info.scene = readFromRawLevelInfo<TLevelInfoMap>(
        source.slice(LevelInfo::Scene));
    return info;
}

} // namespace TD

#endif // LEVEL_INFO_LOADER_IMPL_H
