#include "level_info_loader.h"
#include "level_info_loader_impl.h"
#include "Application/td_application.h"


namespace TD {

TLevelInfoLoader::TLevelInfoLoader() :
    dataPath(DEFAULT_LEVEL_DATA_PATH)
{}

TRawLevelInfo TLevelInfoLoader::loadRawInfo(const TLevelCode& code) {
    TNamedData<string> data;

    TMyON_DataReader parser(dataPath, &data, code);
    if (parser.parse()) {
        THROW("Failed to load level data for level code '" +
            string(code) + "'. Message is: " + parser.getError());
    }

    const string address = dataPath + data["source"];
    parser = TMyON_DataReader(address, &data);
    if (parser.parse()) {
        THROW("Failed to load level data for level code '" +
            string(code) + "'. Message is: " + parser.getError());
    }

    return data;
}

TLevelInfo TLevelInfoLoader::Load(const TLevelCode& code) {
    TLevelInfo info;

    try {
        const auto raw = loadRawInfo(code);
        info = readFromRawLevelInfo<TLevelInfo>(raw);
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
