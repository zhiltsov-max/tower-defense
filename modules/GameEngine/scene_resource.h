#ifndef SCENE_RESOURCE_H
#define SCENE_RESOURCE_H

#include "Core/core.h"


/*
Data level for scene resources
*/
class TSceneResource
{
public:
    enum class TypeID {
		_min = 0,

        undefined = 0,
        image,
        /*sound,*/

        _max = 2
	};

    struct Resource {
        union {
            Graphics::TImage image;
            /*Sound*/
        };
    };

    using PCData = std::weak_ptr<const Resource>;
    using PData = std::weak_ptr<Resource>;

    using Metadata = TNamedData<string>;


    const TypeID& GetType() const;

    const Metadata& GetMetadata() const;
	
    PCData GetData() const;
    PData GetData();

    void Load(const string& source);

private:
    class Loader;
	

    using Data = std::shared_ptr<Resource>;
    TypeID type;
	Data data;
    Metadata metadata;
};

#endif //SCENE_RESOURCE_H
