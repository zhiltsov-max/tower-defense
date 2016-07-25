#ifndef LEVEL_INFO_LOADER_IMPL_H
#define LEVEL_INFO_LOADER_IMPL_H

#include <functional>

#include "Core/core.h"

#include "Game/Level/level.h"
#include "Game/Level/level_info_loader.h"
#include "Game/Level/level_scene.h"

#include "Game/Components/components_list.h"
#include "Game/Map/level_node_map.h"
#include "Game/Map/level_tile_map.h"
#include "Game/Map/level_passability_map.h"
//#include "Game/Player/player_credits.h"
//#include "Game/Player/player_progress.h"
//#include "Game/Player/player_quests.h"
//#include "Game/Player/player_researches.h"
//#include "Game/Player/player_statistics.h"


namespace TD {

// Declarations

template <typename T> T readFromRawLevelInfo(const TRawLevelInfo& source);
template <typename T> T readFromString(const string& source);

template <typename Component>
std::unique_ptr<GE::TComponentCreateArgs>
readComponentInfo(const TRawLevelInfo& source);

vector <string>
readSequence(const string& source, const string& separator = ",");

template <typename T, typename Convert>
vector<T> readSequence(const string& source, const Convert& convert,
    const string& separator = ",");

template <typename Ret, typename Arg>
struct _readArray;

template <typename Ret> struct _readArray<Ret, string>;
template <typename Ret> struct _readArray<Ret, TRawLevelInfo>;

template <> TNamedData<string>
readFromRawLevelInfo<TNamedData<string>>(const TRawLevelInfo& info);

template <> string readFromString<string>(const string& source);

template <typename T, typename Convert>
vector<T> readArray(const TRawLevelInfo& source, const Convert& convert);

template <typename T = TNamedData<string>>
vector<T> readArray(const TRawLevelInfo& source);

template <>
vector<string> readArray<string>(const TRawLevelInfo& source);

template <>
Vec2ui readFromRawLevelInfo(const TRawLevelInfo& source);

template <>
Vec2ui readFromString(const string& source);

template <>
TLevel::Parameters::Common
readFromRawLevelInfo<TLevel::Parameters::Common>(const TRawLevelInfo& source);

//TODO:...
//template <>
//TLevelInfoMobSequenceEntry
//readFromString<TLevelInfoMobSequenceEntry>(const string& source);

//TODO:...
//template <>
//std::unique_ptr<GE::TComponentCreateArgs>
//readComponentInfo<TLevelMobsControllerInfo>(const TRawLevelInfo& source);

//TODO:...
//template <>
//std::unique_ptr<GE::TComponentCreateArgs>
//readComponentInfo<TLevelBuildingsControllerInfo>(const TRawLevelInfo& source);

//TODO:...
//template <>
//std::unique_ptr<GE::TComponentCreateArgs>
//readComponentInfo<TLevelResearchesControllerInfo>(const TRawLevelInfo& source);

//TODO:...
//template <>
//std::unique_ptr<GE::TComponentCreateArgs>
//readComponentInfo<TLevelQuestsControllerInfo>(const TRawLevelInfo& source);

template <>
std::unique_ptr<GE::TComponentCreateArgs>
readComponentInfo<CLevelNodeMap::Parameters>(const TRawLevelInfo& source);

template <>
CLevelTileMap::LayerParameters
readFromRawLevelInfo<CLevelTileMap::LayerParameters>(
    const TRawLevelInfo& source);

template <>
std::unique_ptr<GE::TComponentCreateArgs>
readComponentInfo<CLevelTileMap::Parameters>(const TRawLevelInfo& source);

template <>
std::unique_ptr<GE::TComponentCreateArgs>
readComponentInfo<CLevelTileMapView::Parameters>(const TRawLevelInfo& source);

template <>
TLevel::Parameters::Stage
readFromRawLevelInfo<TLevel::Parameters::Stage>(const TRawLevelInfo& source);

std::unique_ptr<GE::TComponentCreateArgs>
readComponentInfo(const GE::ComponentIDs& id, const TRawLevelInfo& source);

template <>
TComponentInfo
readFromRawLevelInfo<TComponentInfo>(const TRawLevelInfo& source);

template <>
TLevelScene::Parameters::ObjectInfo
readFromRawLevelInfo<TLevelScene::Parameters::ObjectInfo>(
    const TRawLevelInfo& source);

template <>
TLevelScene::Parameters
readFromRawLevelInfo<TLevelScene::Parameters>(const TRawLevelInfo& source);

template <>
TLevel::Parameters
readFromRawLevelInfo<TLevel::Parameters>(const TRawLevelInfo& source);

template <>
TLevelScene::ComponentPath
readFromString<TLevelScene::ComponentPath>(const string& source);


// Implementation

vector<string>
readSequence(const string& source, const string& separator) {
    if (source.empty() == true) {
        return {};
    }
    const auto bracket1 = source.find('[');
    const auto bracket2 = source.rfind(']');
    if ((bracket2 <= bracket1) || (bracket2 == source.npos)) {
        THROW("Failed to read a sequence: wrong format.");
    }
    return String::split(
        source.substr(bracket1, bracket2 - bracket1), separator);
}

template <typename T, typename Convert>
vector<T> readSequence(const string& source, const Convert& convert,
    const string& separator)
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
        source.substr(bracket1, bracket2 - bracket1), separator);
    vector<T> result;
    std::transform(raw.begin(), raw.end(), result.begin(), convert);
    return result;
}

template <typename R>
struct _readArray<R, string> {
    using F = R(const string&);
    static vector<R> read(const TRawLevelInfo& source, const F& f) {
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
    using F = R(const TRawLevelInfo&);
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

template <typename T, typename Convert>
vector<T> readArray(const TRawLevelInfo& source, const Convert& convert) {
    using F = typename std::function<Convert>;
    using Arg = typename std::decay<typename F::argument_type>::type;
    return _readArray<T, Arg>::read(source, convert);
}

template <typename T>
vector<T> readArray(const TRawLevelInfo& source) {
    return readArray<T, decltype(readFromRawLevelInfo<T>)>(
        source, readFromRawLevelInfo<T>);
}

template <>
vector<string> readArray<string>(const TRawLevelInfo& source) {
    return readArray<string, decltype(readFromString<string>)>(
        source, readFromString<string>);
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
    const auto coordinates = readSequence<uint>(source,
        [] (const string& s) { return static_cast<uint>(std::stoul(s)); } );
    ASSERT(coordinates.size() == 2, "Expected 2 coordinates.");
    return {coordinates[0], coordinates[1]};
}

template <>
TLevelScene::ComponentPath
readFromString<TLevelScene::ComponentPath>(const string& source) {
    TLevelScene::ComponentPath path;
    const auto parts = String::split(source, ".");
    ASSERT(parts.size() == 2, "Unable to read ComponentPath: wrong format");
    path.first = parts[0];
    path.second = parts[1];
    return path;
}

namespace CommonLevelInfo {
static constexpr char LevelCode[] = "code";
static constexpr char NextLevelCode[] = "nextLevel";
static constexpr char LoadingScript[] = "loadingScript";
static constexpr char LevelType[] = "type";
static constexpr char LevelType_Normal[] = "normal";
static constexpr char LevelType_Free[] = "free";
} // namespace CommonLevelInfo

template <>
TLevel::Parameters::Common
readFromRawLevelInfo<TLevel::Parameters::Common>(const TRawLevelInfo& source) {
    TLevel::Parameters::Common info;
    info.levelCode = source[CommonLevelInfo::LevelCode];
    info.nextLevelCode = source[CommonLevelInfo::NextLevelCode];
    info.loadingScript = source[CommonLevelInfo::LoadingScript];
    info.levelType = LevelType::Undefined;
    const auto& type = source[CommonLevelInfo::LevelType];
    if (CommonLevelInfo::LevelType_Normal == type) {
        info.levelType = LevelType::Normal;
    } else if (CommonLevelInfo::LevelType_Free == type) {
        info.levelType = LevelType::Free;
    } else {
        THROW("Unexpected level type: " + type);
    }
    return info;
}


namespace MobSequenceEntryInfo {
static constexpr char CountSign[] = "*";
static constexpr char RandomSign[] = "R";
} // namespace MobSequenceInfo

//TODO:...
//template <>
//TLevelInfoMobSequenceEntry
//readFromString<TLevelInfoMobSequenceEntry>(const string& source) {
//    TLevelInfoMobSequenceEntry info;
//    const auto parts = String::split(*it, MobSequenceEntryInfo::CountSign);
//    info.id = 0;
//    if (parts[0] != MobSequenceEntryInfo::RandomSign) {
//        info.id = std::stoi(parts[0]);
//    }
//    info.count = std::max(1, std::stoi(parts[1]));
//    return info;
//}

namespace MobsInfo {
static constexpr char Delay[] = "delay";
static constexpr char Sequence[] = "sequence";
} // namespace MobsInfo

//TODO...
//template <>
//std::unique_ptr<GE::TComponentCreateArgs>
//readComponentInfo<TLevelMobsControllerInfo>(const TRawLevelInfo& source) {
//    std::unique_ptr<TLevelMobsControllerInfo> info;
//    info->sequence = readSequence<TLevelInfoMobSequenceEntry>(
//        source.slice(MobsInfo::Sequence),
//        readFromString<TLevelInfoMobSequenceEntry>);
//    info->delay = std::stof(source[MobsInfo::Delay]);
//    return info;
//}


namespace BuildingsInfo {
static constexpr char Restricted[] = "restricted";
static constexpr char Allowed[] = "allowed";
static constexpr char MaxCount[] = "maxCount";
} // namespace BuildingsInfo

//TODO:...
//template <>
//std::unique_ptr<GE::TComponentCreateArgs>
//readComponentInfo<TLevelBuildingsControllerInfo>(const TRawLevelInfo& source) {
//    std::unique_ptr<TLevelBuildingsControllerInfo> info;
//    info->restricted = readSequence<TBuildingClassId>(
//        source[BuildingsInfo::Restricted], std::stoi);
//    info->allowed = readSequence<TBuildingClassId>(
//        source[BuildingsInfo::Allowed], std::stoi);
//    info->maxCount = std::max(std::stoi(source[BuildingsInfo::MaxCount]), 0);
//    return info;
//}


namespace ResearchesInfo {
static constexpr char Restricted[] = "restricted";
static constexpr char Allowed[] = "allowed";
static constexpr char MaxCount[] = "maxCount";
static constexpr char separator[] = ",";
} // namespace ResearchesInfo

//TODO:...
//template <>
//std::unique_ptr<GE::TComponentCreateArgs>
//readComponentInfo<TLevelResearchesControllerInfo>(const TRawLevelInfo& source) {
//    std::unique_ptr<TLevelResearchesControllerInfo> info;
//    info->restricted = readSequence<TResearchClassId>(
//        source[ResearchesInfo::Restricted], std::stoi);
//    info->allowed = readSequence<TResearchClassId>(
//        source[ResearchesInfo::Allowed], std::stoi);
//    info->maxCount = std::max(std::stoi(source[ResearchesInfo::MaxCount]), 0);
//    return info;
//}


namespace QuestsInfo {
} // namespace QuestsInfo

//TODO:...
//template <>
//std::unique_ptr<GE::TComponentCreateArgs>
//readComponentInfo<TLevelQuestsControllerInfo>(const TRawLevelInfo& source) {
//    std::unique_ptr<TLevelQuestsControllerInfo> info;
//    //TODO: ...
//    return info;
//}


namespace NodeMapInfo {
static constexpr char Size[] = "size";
static constexpr char Pathes[] = "pathes";
static constexpr char Enters[] = "enters";
static constexpr char Exits[] = "exits";
} // namespace NodeMapInfo

template <>
std::unique_ptr<GE::TComponentCreateArgs>
readComponentInfo<CLevelNodeMap::Parameters>(const TRawLevelInfo& source) {
    auto info = std::unique_ptr<CLevelNodeMap::Parameters>(
        new CLevelNodeMap::Parameters);
    info->pathes = readArray<vector<Vec2ui>>(source.slice(NodeMapInfo::Pathes),
        readArray<Vec2ui>);
    info->enters = readArray<Vec2ui>(source.slice(NodeMapInfo::Enters),
        readFromString<Vec2ui>);
    info->exits = readArray<Vec2ui>(source.slice(NodeMapInfo::Exits),
        readFromString<Vec2ui>);
    return { std::move(info) };
}

namespace TileMapLayerInfo {
static constexpr char Tiles[] = "tiles";
} // namespace TileMapLayerInfo

template <>
CLevelTileMap::LayerParameters
readFromRawLevelInfo<CLevelTileMap::LayerParameters>(
    const TRawLevelInfo& source)
{
    CLevelTileMap::LayerParameters info;
    info.tiles = readSequence<CLevelTileMap::Tile>(
        source[TileMapLayerInfo::Tiles],
        [] (const string& s) {
            CLevelTileMap::Tile tile;
            tile.index = static_cast<uint>(std::stoul(s));
            return tile;
        }
    );
    return info;
}

namespace TileMapInfo {
static constexpr char Size[] = "size";
static constexpr char Layers[] = "layers";
} // namespace TileMapInfo

template <>
std::unique_ptr<GE::TComponentCreateArgs>
readComponentInfo<CLevelTileMap::Parameters>(const TRawLevelInfo& source) {
    auto info = std::unique_ptr<CLevelTileMap::Parameters>(
        new CLevelTileMap::Parameters);
    info->size = readFromString<Vec2ui>(source[TileMapInfo::Size]);
    info->layers = readArray<CLevelTileMap::LayerParameters>(
        source.slice(TileMapInfo::Layers));
    return { std::move(info) };
}

namespace TileMapViewInfo {
static constexpr char TileMap[] = "tileMap";
} // namespace TileMapView

template <>
std::unique_ptr<GE::TComponentCreateArgs>
readComponentInfo<CLevelTileMapView::Parameters>(const TRawLevelInfo& source) {
    auto info = std::unique_ptr<CLevelTileMapView::Parameters>(
                new CLevelTileMapView::Parameters);
    info->tileMapComponent = readFromString<TLevelScene::ComponentPath>(
        source[TileMapViewInfo::TileMap]);
    return { std::move(info) };
}


namespace StageInfo {
static constexpr char Mobs[] = "mobs";
static constexpr char Buildings[] = "buildings";
static constexpr char Researches[] = "researches";
static constexpr char Quests[] = "quests";
static constexpr char Map[] = "map";
static constexpr char Scripts[] = "scripts";
} // namespace StageInfo

template <>
TLevel::Parameters::Stage
readFromRawLevelInfo<TLevel::Parameters::Stage>(const TRawLevelInfo& source) {
    TLevel::Parameters::Stage info;
    info.scene = readFromRawLevelInfo<TLevelScene::Parameters>(
        source.slice(StageInfo::Mobs));
    return info;
}

using ComponentInfoReader = std::function<
    std::unique_ptr<GE::TComponentCreateArgs>(const TRawLevelInfo& source)
>;
static const std::map<GE::ComponentIDs, ComponentInfoReader>
componentInfoReaders = {
    // list of pairs {id, reader}
//    {GE::ComponentIDs::PlayerStatistics,},
//    {GE::ComponentIDs::PlayerProgress,},
//    {GE::ComponentIDs::PlayerQuests,},
//    {GE::ComponentIDs::PlayerResearches,},
//    {GE::ComponentIDs::PlayerCredits,},

//    {GE::ComponentIDs::ResearchesTreeView,},
//    {GE::ComponentIDs::ResearchesTreeItemView,},

    {GE::ComponentIDs::LevelTileMap, readComponentInfo<CLevelTileMap::Parameters>},
    {GE::ComponentIDs::LevelTileMapView, readComponentInfo<CLevelTileMapView::Parameters>},
    {GE::ComponentIDs::LevelNodeMap, readComponentInfo<CLevelNodeMap::Parameters>},
//    {GE::ComponentIDs::LevelNodeMapView,}, //TODO: debug only?
//    {GE::ComponentIDs::LevelPassabilityMap, readComponentInfo<CLevelPassabilityMap::Parameters>},
//    {GE::ComponentIDs::LevelPassabilityMapView,}, //TODO: debug only?

//    {GE::ComponentIDs::LevelBuildingsController, readComponentInfo<TLevelBuildingsControllerInfo>},
//    {GE::ComponentIDs::LevelMobsController, readComponentInfo<TLevelMobsControllerInfo>},
//    {GE::ComponentIDs::LevelQuestsController, readComponentInfo<TLevelQuestsControllerInfo>},
//    {GE::ComponentIDs::LevelResearchesController, readComponentInfo<TLevelResearchesControllerInfo>}
};

std::unique_ptr<GE::TComponentCreateArgs>
readComponentInfo(const GE::ComponentIDs& id, const TRawLevelInfo& source) {
    return componentInfoReaders.at(id)(source);
}

namespace ComponentInfo {
static constexpr char Name[] = "name";
static constexpr char Id[] = "id";
static constexpr char Parameters[] = "parameters";
} // namespace ComponentInfo

template <>
TComponentInfo
readFromRawLevelInfo<TComponentInfo>(const TRawLevelInfo& source) {
    TComponentInfo info;
    info.name = source[ComponentInfo::Name];
    info.id = static_cast<GE::ComponentIDs>(
        std::stoul(source[ComponentInfo::Id]));
    info.parameters.reset(readComponentInfo(info.id, source).release());
    return info;
}


namespace SceneObjectInfo {
static constexpr char Name[] = "name";
static constexpr char Components[] = "components";
} // namespace SceneObjectInfo

template <>
TLevelScene::Parameters::ObjectInfo
readFromRawLevelInfo<TLevelScene::Parameters::ObjectInfo>(
    const TRawLevelInfo& source)
{
    TLevelScene::Parameters::ObjectInfo info;
    info.name = source[SceneObjectInfo::Name];
    info.components = readArray<TComponentInfo>(
        source.slice(SceneObjectInfo::Components));
    return info;
}


namespace LevelSceneInfo {
static constexpr char Resources[] = "resources";
static constexpr char Objects[] = "objects";
} // namespace SceneInfo

template <>
TLevelScene::Parameters
readFromRawLevelInfo<TLevelScene::Parameters>(const TRawLevelInfo& source) {
    TLevelScene::Parameters info;
    info.resources = readArray<string>(
        source.slice(LevelSceneInfo::Resources));
    info.objects = readArray<TLevelScene::Parameters::ObjectInfo>(
        source.slice(LevelSceneInfo::Objects));
    return info;
}


namespace LevelInfo {
static constexpr char Common[] = "common";
static constexpr char Scene[] = "scene";
static constexpr char Stages[] = "stages";
} // namespace LevelInfo

template <>
TLevel::Parameters
readFromRawLevelInfo<TLevel::Parameters>(const TRawLevelInfo& source) {
    TLevel::Parameters info;
    info.common = readFromRawLevelInfo<TLevel::Parameters::Common>(
        source.slice(LevelInfo::Common));
    info.stages = readArray<TLevel::Parameters::Stage>(
        source.slice(LevelInfo::Stages));
    info.scene = readFromRawLevelInfo<TLevel::Parameters::Scene>(
        source.slice(LevelInfo::Scene));
    return info;
}

} // namespace TD

#endif // LEVEL_INFO_LOADER_IMPL_H
