#ifndef PLAYER_QUESTS_H
#define PLAYER_QUESTS_H

#include "Game/Components/components_list.h"


namespace TD {

class CPLayerQuests : public CLogicsComponent
{
public:
    struct Parameters;
    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args);

    CPLayerQuests(const Parameters& parameters);
    virtual ~CPLayerQuests();

private:
    enum class StageState : uint {
        Undefined = 0,
        Failed,
        Completed
    };

    enum class LevelState : uint {
        Undefined = 0,
        Failed,
        Completed
    };

};

struct CPLayerQuests : GE::TComponentCreateArgs
{
1
};

} // namespace TD

#endif // PLAYER_QUESTS_H
