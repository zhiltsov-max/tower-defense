#include "mob_info.h"
#include "mob_controller.h"


static const string TMobsInfoLoader::DATA_SOURCE_ADDRESS = "Data/Mobs/BInfo.txt";

void TMobsInfoLoader::operator()(TMobsInfo& info) {
    std::ifstream stream(DATA_SOURCE_ADDRESS);
    if (stream.is_open() == false) {
        Throw("Failed to load mobs info: source is not found.");
    }

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

        TMob::Info& lastClass = info[lastClassId];

        try {
            const auto& loader = getInfoLoader(lastClassId);
            if (loader == false) {
                throw exception("loader is not found");
            }

            loader(&lastClass, *stream);
        } catch (const exception& e) {
            Throw("Failed to load mob info for class #" + std::to_string(lastClassId) +". Message: " + e.what(),
                  "TMobsInfo::TMobsInfo");
        }
    }

    stream.close();
}

const TMobsInfoLoader::MobInfoLoader& TMobsInfoLoader::getInfoLoader(const TMob::ClassId& classId) const {

}



void TMobInfoLoader_basic(TMob::Info& info, std::istream& source) {
    string buffer;

    std::getline(source, buffer);
    info["name"].asString = buffer;

    std::getline(source, buffer);
    info["reward"].asUint = std::stoi(buffer);

    std::getline(source, buffer);
    info["health"].asInt = std::stoi(buffer);

    std::getline(source, buffer);
    info["health"].asFloat = std::stof(buffer);

    std::getline(source, buffer);
    info["appearance"].asInt = std::stoi(buffer);

    std::getline(source, buffer);
    info["description"].asString = buffer;

    std::getline(source, buffer);
    info["resources"].asString = buffer;
}
