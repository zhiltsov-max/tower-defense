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
    GE::TSceneObject player;

    progress = level->GetScene().GetRaw().CreateComponent<CPlayerProgress>();
    player.AddComponent("progress", progress);

    statistics = level->GetScene().GetRaw().CreateComponent<CPlayerStatistics>();
    player.AddComponent("statistics", statistics);

    level->GetScene().GetRaw().GetObjects().AddSceneObject("player", player);
}

const TPlayer::Progress& TPlayer::GetProgress() const {
    ASSERT(level != nullptr, "Level must be set.")
    return *dynamic_cast<const Progress*>(
        level->GetScene().GetComponent(progress));
}

TPlayer::Progress& TPlayer::GetProgress() {
    ASSERT(level != nullptr, "Level must be set.")
    return *dynamic_cast<Progress*>(
        level->GetScene().GetComponent(progress));
}

const TPlayer::Statistics& TPlayer::GetStatistics() const {
    ASSERT(level != nullptr, "Level must be set.")
    return *dynamic_cast<const Statistics*>(
        level->GetScene().GetComponent(statistics));
}

TPlayer::Statistics& TPlayer::GetStatistics() {
    ASSERT(level != nullptr, "Level must be set.")
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
