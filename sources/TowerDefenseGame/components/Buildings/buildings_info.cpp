#include "buildings_info.h"
#include "buildings_list.h"



namespace TD {


const string TBuildingsInfoLoader::DEFAULT_DATA_SOURCE_PATH =
    "Data/Buildings/BInfo.txt";

TBuildingsInfoLoader::operator()(TBuildingsInfo& info) {
    std::ifstream stream(dataPath);
    if (stream.is_open() == false) {
        THROW("Failed to load buildings info: source is not found.")
    }

    while (stream.good()) {
		string str; 
		std::getline(*stream, str);

		if ((String::startsWith(str, "'") == true) || 
			(String::startsWith(str, " ") == true) ||
			(String::left(str, 1) != "#")) {
				continue; 
		}

        uint lastClassId = (uint) std::stoi(str.substr(1, str.size() - 1));
		if (lastClassId == 0) {
			continue;
		}

        Info& lastClass = info[lastClassId];

        try {
            const auto& loader = getInfoLoader(lastClassId);
            if (loader == false) {
                THROW("loader is not found")
            }

            loader(lastClass, stream);
        } catch (const std::exception& e) {
            THROW("Failed to load building info for class #" +
                std::to_string(lastClassId) +". Message: " +
                e.what())
        }
	}
		
    stream.close();
}

const TBuildingsInfoLoader& TBuildingsInfoLoader::getInfoLoader(const TBuildingClassId& classId) const {
    return buildingMetadata.at(classId).loader;
}

void TBuildingsInfoLoader::SetDataPath(const string& value) {
    dataPath = value;
}


} // namespace TD
