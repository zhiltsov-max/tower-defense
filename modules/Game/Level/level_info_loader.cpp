#include "level_info_loader.h"
#include "level_info_loader_impl.h"
#include <fstream>


namespace TD {

const char TLevelInfoLoader::DEFAULT_LEVEL_DATA_PATH[] = "Data/Levels/";
const char TLevelInfoLoader::DEFAULT_LEVEL_DATA_FILE[] = "levelData.dat";

TLevelInfoLoader::TLevelInfoLoader() :
    dataPath(DEFAULT_LEVEL_DATA_PATH)
{}

TRawLevelInfo TLevelInfoLoader::loadRawInfo(const TLevelCode& code) {
    std::ifstream file(dataPath);
    if (file.is_open() == false) {
        THROW("Failed to open file '" + dataPath + "'.");
    }
    TMyON_DataReader levelsParser(file, code);
    bool result = levelsParser.parse();
    file.close();
    if (result == true) {
        THROW("Failed to load level data for level code '" +
            string(code) + "'. Message is: " + levelsParser.getError());
    }

    file.open(dataPath + levelsParser.getParsedData()["source"]);
    if (file.is_open() == false) {
        THROW("Failed to open file '" + dataPath + "'.");
    }
    TMyON_DataReader levelParser(file);
    result = levelParser.parse();
    file.close();
    if (result == true) {
        THROW("Failed to load level data for level code '" +
            string(code) + "'. Message is: " + levelParser.getError());
    }

    return levelParser.getParsedData();
}

TLevel::Parameters TLevelInfoLoader::Load(const TLevelCode& code) {
    TLevel::Parameters info;

    try {
        const auto raw = loadRawInfo(code);
        info = readFromRawLevelInfo<TLevel::Parameters>(raw);
        info.common.levelCode = code;
    } catch (const std::exception& e) {
        //TODO: error logging
        std::cerr << "Failed to load level info from file. The message is:"
                  << e.what() <<std::endl;
    }

    return info;
}

void TLevelInfoLoader::SetDataPath(const string& value) {
    dataPath = value;
}

} // namespace TD
