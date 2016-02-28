#include "player.h"
#include "GameEngine/game_engine.h"



namespace TD {


TPlayer::TPlayer(TLevel* level) :
    parent_type(ComponentID::Player),
    name(),
    progress(),
    statistics(),
    level(level)
{
    TSceneObject player;

    progress = level->GetScene().CreateComponent<CPlayerProgress>();
    player.AddComponent("progress", progress);

    statistics = level->GetScene().CreateComponent<CPlayerStatistics>();
    player.AddComponent("statistics", statistics);

    level->GetScene().GetObjects().AddSceneObject("player", player);
}

const TPlayer::Progress& TPlayer::GetProgress() const {
#if defined(_DEBUG)
    ASSERT(level != nullptr, "Level must be set.")
#endif // DEBUG
    return *dynamic_cast<const Progress*>(
        level->GetScene().GetComponent(progress));
}

TPlayer::Progress& TPlayer::GetProgress() {
#if defined(_DEBUG)
    ASSERT(level != nullptr, "Level must be set.")
#endif // DEBUG
    return *dynamic_cast<Progress*>(
        level->GetScene().GetComponent(progress));
}

const TPlayer::Statistics& TPlayer::GetStatistics() const {
#if defined(_DEBUG)
    ASSERT(level != nullptr, "Level must be set.")
#endif // DEBUG
    return *dynamic_cast<const Statistics*>(
        level->GetScene().GetComponent(statistics));
}

TPlayer::Statistics& TPlayer::GetStatistics() {
#if defined(_DEBUG)
    ASSERT(level != nullptr, "Level must be set.")
#endif // DEBUG
    return *dynamic_cast<Statistics*>(
        level->GetScene().GetComponent(statistics));
}

void TPlayer::SetName(const TPlayer::Name& value) {
    name = value;
}

const TPlayer::Name& TPlayer::GetName() const {
   return name;
}


} // namespace TD
