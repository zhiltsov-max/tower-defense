#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include "GameEngine/component.h"
#include "GameEngine/scene_resources.h"
#include "GameEngine/component_registry.h"
#include "Game/Components/td_components_list.h"
#include "Game/ComponentSystems/td_component_systems_list.h"


TD_DECLARE_COMPONENT_CLASS(CAnimation,
    GE::ComponentIDs::Animation, GE::ComponentSystem::Graphics)

namespace TD {

struct TAnimationResource : GE::TSceneResource
{
    using FrameIndex = uint16_t;
    struct TFramesGroup
    {
        FrameIndex start;
        FrameIndex end;

        Vec2us frameSize;
    };

    vector<TFramesGroup> frameGroups;
};

struct CAnimation : GE::TComponent
{
    using FrameIndex = TAnimationResource::FrameIndex;
    struct Parameters;

    static const short UnlimitedRepeats = -1;
    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args = nullptr);

    CAnimation(const Parameters* parameters);

    GE::TSceneResourceID resource;

    FrameIndex currentFrame;
    FrameIndex actionIndex;
    FrameIndex speed; //count of draw frames per one frame of animation
    short repeats;

private:
    using parent_type = GE::TComponent;
};

struct CAnimation::Parameters : GE::TComponentCreateArgs
{
    GE::TSceneResourceID resource;

    FrameIndex defaultActionIndex;
    FrameIndex defaultSpeed;
    short repeats;
};


//void readResourceInfo<TAnimationResource>() { //TODO: move out
//    const string source = source_.substr(2, source_.size() - 2);
//    const std::vector<string> groups = String::split(source, animationGroups_separator);
//    for(auto it = groups.cbegin(); it != groups.cend(); ++it) {
//        const std::vector<string> pairs = String::split(*it, animationGroupKey_separator);
//        const std::vector<string> values = String::split(pairs[1], animationGroupValues_separator);
//        int repeats = 0;
//        if (4 <= values.size()) {
//            repeats = std::stoi(values[3]);
//        }
//        TAnimationGroup entry = TAnimationGroup(std::stoi(values[0]), std::stoi(values[1]), std::stoi(values[2]), repeats);
//        frames[std::stoul(pairs[0])] = entry;
//    }
//}

} // namespace TD

#endif // ANIMATION_COMPONENT_H
