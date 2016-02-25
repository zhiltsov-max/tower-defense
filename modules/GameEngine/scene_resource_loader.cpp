#include "scene_resource_loader.h"



void TSceneResource::Loader::Load(
    const string& source,
    TSceneResource& resource)
{
    //TO DO: implementation fix, handle SFML

    resource.type = recognizeType(source);

    auto sourceParts = std::move(getSourceParts(source.substr(1)));

    switch (resource.type) {
    case TypeID::image:
        {
            bool midHandle = false;
            uchar mask_r = 0;
            uchar mask_g = 0;
            uchar mask_b = 0;

            for(size_t i = 5; i < sourceParts.size(); ++i) {
                switch (sourceParts[i].c_str()[0]) {
                case IMAGE_MIDHANDLE_SIGN:
                    midHandle = true;
                    break;

                case META_SIGN:
                    resource.metadata = sourceParts[i];
                    break;

                case IMAGE_MASK_R_SIGN:
                    mask_r = (uchar) std::stoi(String::right(sourceParts[i], 1));
                    break;

                case IMAGE_MASK_G_SIGN:
                    mask_g = (uchar) std::stoi(String::right(sourceParts[i], 1));
                    break;

                case IMAGE_MASK_B_SIGN:
                    mask_b = (uchar) std::stoi(String::right(sourceParts[i], 1));
                    break;

                default: {/*none*/}
                }
            }

            Graphics::setMaskColor(mask_r, mask_g, mask_b);

            resource.data = Graphics::loadAnimImage(
                sourceParts[2],
                std::stoi(sourceParts[0]),
                std::stoi(sourceParts[1]),
                std::stoi(sourceParts[3]),
                std::stoi(sourceParts[4])
            );

            Graphics::setMaskColor(0, 0, 0);

            if (midHandle == true) {
                Graphics::MidHandleImage(dynamic_cast<Graphics::TImage*>(data));
            }

            Graphics::checkImage(std::dynamic_pointer_cast<Graphics::TImage*>(data), sourceParts[2]);
            break;
        }

    case TypeID::sound:
        {
            resource.data = Sound::loadSound(sourceParts[0], std::stoi(sourceParts[1]));
            break;
        }

    default:
        {
            THROW("Unexpected class of resource '" + source.path + "'.");
        }
    }
}


vector<string> TSceneResource::Loader::getSourceParts(const string& source) {
    return String::split(source, partsSeparator);
}

TSceneResource::TypeID TSceneResource::Loader::recognizeType(const string& source) {
    switch (source.c_str()[0]) {
    case TYPE_IMAGE_SIGN:
        return TypeID::image;
        break;

    case TYPE_SOUND_SIGN:
        return TypeID::sound;
        break;

    default:
        return TypeID::undefined;
    }
}
