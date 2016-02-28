#ifndef PLAYER_H
#define PLAYER_H

#include "Game/Components/components_list.h"
#include "Game/Level/level.h"
#include "player_progress.h"
#include "player_statistics.h"



namespace TD {

class TLevel;

class TPlayer
{
public:
    using Progress = CPlayerProgress;
    using Statistics = CPlayerStatistics;
    using Name = TextString;


    TPlayer(TLevel* level);
    virtual ~TPlayer();

    const Progress& GetProgress() const;
    Progress& GetProgress();

    const Statistics& GetStatistics() const;
    Statistics& GetStatistics();

    void SetName(const Name& value);
    const Name& GetName() const;

private:
    Name name;

    using PLevel = TLevel *;
    const PLevel level;

    using Handle = TLevelScene::Handle;
    Handle progress;
    Handle statistics;
};

} // namespace TD

#endif // PLAYER_H
