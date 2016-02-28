#include "level_info_stages.h"



namespace TD {


TLevelInfoStages::TLevelInfoStages(const TRawLevelInfo& source)
{
    const int count = std::stoi(source["size"]);
    if (count == 0) {
        return;
    }

    stages.reserve(count);

    for (int i = 0; i < count; ++i) {
        const string key = std::to_string(i);

        if (source.contains(key) == false) {
            THROW("Failed to load stages info: " +
                "source does not contain info for '" +
                key + "'th stage.")
        }

        stages.emplace_back(source.slice(key));
    }
}


} // namespace TD
