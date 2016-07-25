#ifndef LEVEL_INFO_LOADER_H
#define LEVEL_INFO_LOADER_H

#include "Core/core.h"
#include "Game/Level/level.h"


namespace TD {

using TRawLevelInfo = TNamedData<string>;

class TLevelInfoLoader
{
public:
    TLevelInfoLoader();

    TLevel::Parameters Load(const TLevelCode& code);

    void SetDataPath(const string& value);

private:
    static const char DEFAULT_LEVEL_DATA_PATH[];
    static const char DEFAULT_LEVEL_DATA_FILE[];

    string dataPath;

    TRawLevelInfo loadRawInfo(const TLevelCode& code);
};

} // namespace TD

#endif // LEVEL_INFO_LOADER_H
