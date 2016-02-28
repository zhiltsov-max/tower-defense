#ifndef RESEARCHES_INFO_H
#define RESEARCHES_INFO_H

#include "Game/Components/game_objects_info.h"
#include <istream>
#include "Game/Level/level_info_researches.h"



namespace TD {


struct TResearchInfo {
    1
    TextString description;
    uint cost;
    TextString title;
    bool isMajor;


    friend operator >>(std::istream& is, TResearchInfo& info);
};

using TResearchesRegistry = TGameObjectsRegistry<TResearchInfo>;

class TResearchesRegistryLoader
{
public:
    static const char* DEFAULT_DATA_SOURCE_PATH;
    TResearchesRegistryLoader(const string& dataSourcePath = DEFAULT_DATA_SOURCE_PATH);

    void SetDataSourcePath(const string& value);

    void Load(const TLevelInfoResearches& source, TResearchesRegistry& registry);

private:
    string dataSourcePath;
};


} // namepsace TD

#endif // RESEARCHES_INFO_H
