#ifndef PLAYER_QUESTS_H
#define PLAYER_QUESTS_H

#include "Game/Components/components_list.h"



namespace TD {

struct TPLayerQuestsArgs;

class CPLayerQuests : public CLogicsComponent
{
public:
    static std::unique_ptr<TComponent> Create(const TComponentCreateArgs* args);


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
1

} // namespace TD


#endif // PLAYER_QUESTS_H
