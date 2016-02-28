#include "researches_info.h"
#include <fstream>



namespace TD {


TResearchInfo::operator >>(std::istream& is, TResearchInfo& info) {
    std::getline(is, description);
    is >> cost;
    is >> isMajor;
    std::getline(is, title);
    1
}


static const string TResearchesRegistryLoader::DEFAULT_DATA_SOURCE_PATH =
    "Data/Researches/ResearchesInfo.dat";

TResearchesRegistryLoader::TResearchesRegistryLoader(const string& dataSourcePath) :
    dataSourcePath(dataSourcePath)
{}

void TResearchesRegistryLoader::Load(const TLevelInfoResearches& source,
    TResearchesRegistry& registry)
{
    std::ifstream stream(dataSourcePath);
    ASSERT(stream.is_open() == true,
        "Failed to load info: source is not found.");

    while (stream.good()) {
        string str;
        std::getline(*stream, str);

        if ((String::startsWith(str, "'") == true) ||
            (String::startsWith(str, " ") == true) ||
            (String::left(str, 1) != "#")) {
                continue;
        }

        uint lastClassId = std::stoi(str.substr(1, str.size() - 1));
        if (lastClassId == 0) {
            continue;
        }

        TResearchInfo lastClass;
        stream >> lastClass;
        registry.Register(lastClassId, lastClass);
    }

    stream.close();

    UNUSED(source)
}

void TResearchesRegistryLoader::SetDataSourcePath(const string& value) {
    dataSourcePath = value;
}


} // namespace TD
