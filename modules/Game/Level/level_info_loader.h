#ifndef LEVEL_INFO_LOADER_H
#define LEVEL_INFO_LOADER_H

#include "Game/Level/level_info.h"
#include "Game/Level/level_code.h"


namespace TD {

class TLevelInfoLoader
{
public:
    TLevelInfoLoader();

    TLevelInfo Load(const TLevelCode& code);

    void SetDataPath(const string& value);

private:
    static constexpr string DEFAULT_LEVEL_DATA_PATH = "Data/Levels/";
    static constexpr string DEFAULT_LEVEL_DATA_FILE = "levelData.dat";

    string dataPath;

    TRawLevelInfo loadRawInfo(const TLevelCode& code);
};

} // namespace TD

#endif // LEVEL_INFO_LOADER_H
