#ifndef GAME_GUI_H
#define GAME_GUI_H

#include "../Core/core.h"
#include "game_statistics.h"


#define BEGIN_GAME_GUI BEGIN_GAME namespace GUI {
#define END_GAME_GUI } END_GAME

BEGIN_GAME_GUI

void updateStatistics(const TGameStatistics& statistics, const TLevel& level);
void showStatistics(const TGameStatistics& statistics);
void updateStatisticsFrame();

void initPause();
void exitPause();
void updatePauseWindow();

void restoreGameWindows();

bool MouseOverInterface() {
    return UIParent()->IsMouseOver();
}

END_GAME_GUI

#endif // GAME_GUI_H
