#ifndef SCENE_RESOURCE_LOADER_H
#define SCENE_RESOURCE_LOADER_H

#include "GameEngine/scene_resource.h"



class TSceneResource::Loader
{
public:
    void Load(const string& source, TSceneResource& resource);

private:
    static const char partsSeparator = ',';
    static const char TYPE_IMAGE_SIGN = 'I';
    static const char TYPE_SOUND_SIGN = 'S';
    static const char IMAGE_MIDHANDLE_SIGN = 'm';
    static const char META_SIGN = '[';
    static const char IMAGE_MASK_R_SIGN = 'r';
    static const char IMAGE_MASK_G_SIGN = 'g';
    static const char IMAGE_MASK_B_SIGN = 'b';


    vector<string> getSourceParts(const string& source);
    TypeID recognizeType(const string& source);
};

#endif // SCENERESOURCE_LOADER_H
