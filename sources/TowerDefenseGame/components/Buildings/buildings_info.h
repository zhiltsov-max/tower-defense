#ifndef BUILDINGS_INFO_H
#define BUILDINGS_INFO_H

#include "Game/Components/game_objects_info.h"


namespace TD {

struct TBuildingInfo {
    virtual ~TBuildingInfo() = default;
};

using TBuildingInfoLoader = std::function<void (TBuildingInfo&, std::istream& source)>;

class TBuildingsInfoLoader
{
public:
    void SetDataPath(const string& value);

    void Load(const TLevelBuildingsControllerInfo& source, TBuildingsInfo& info);

private:
    static const string DEFAULT_DATA_SOURCE_PATH;
    string dataPath;

    const TBuildingInfoLoader& getInfoLoader(const TBuildingClassId& classId) const;
};

struct TBuildingsRegistryEntry {
    using Create = std::function<TLevelScene::SceneObjects::Handle (
        TLevelScene&, TBuildingsController&)>;

    using Info = std::unique_ptr<TBuildingInfo>;

    Create create;
    Info info;
};

using TBuildingsRegistry = TGameObjectsRegistry<TBuildingRegistryEntry>;

static void BuildingInfoLoader_Basic(Info& info, std::istream& source);

} // namespace TD

#endif // BUILDINGS_INFO_H
