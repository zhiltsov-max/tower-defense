#ifndef BUTTONCALLBACKS_H
#define BUTTONCALLBACKS_H

#include "..\Core\core.h"
#include "..\GUI\gui_main.h"
#include "game_gui_main.h"

/*
addCallback("MainMenu_Start", MainMenu_Start);
addCallback("MainMenu_Exit", MainMenu_Exit);

addCallback("StartMenu_StartA", StartMenu_StartA);
addCallback("StartMenu_StartB", StartMenu_StartB);
addCallback("StartMenu_Back", StartMenu_Back);

addCallback("GameControl_Start", GameControl_Start);
addCallback("GameControl_Pause", GameControl_Pause);
'addCallback("GameControl_Exit", GameControl_Exit);

addCallback("GameToolbar_Zone", GameToolbar_Zone);
addCallback("GameToolbar_Repair", GameToolbar_Repair);
addCallback("GameToolbar_Buildings", GameToolbar_Buildings);
addCallback("GameToolbar_Base", GameToolbar_Base);
addCallback("GameToolbar_Rocket", GameToolbar_Rocket);
addCallback("GameToolbar_Tree", GameToolbar_Tree);

addCallback("UpgradesTreeWindow_close", UpgradesTreeWindow_close);

addCallback("PopUp_Upgrade", PopUp_Upgrade);
addCallback("PopUp_Sell", PopUp_Sell);

addCallback("PauseWindow_MainMenu", PauseWindow_MainMenu);
addCallback("PauseWindow_Back", PauseWindow_Back);
addCallback("PauseWindow_RestartLevel", PauseWindow_RestartLevel);
*/

BEGIN_GAME_GUI

namespace button_callbacks {

void* MainMenu_Start(void** args = nullptr);

void* MainMenu_Exit(void** args = nullptr);

void* StartMenu_StartA(void** args = nullptr);

void* StartMenu_StartB(void** args = nullptr);

void* StartMenu_Back(void** args = nullptr);


void* GameControl_Start(void** args = nullptr);

void* GameControl_Pause(void** args = nullptr);

void* GameControl_Exit(void** args = nullptr);


void* GameToolbar_Zone(void** args = nullptr);

void* GameToolbar_Repair(void** args = nullptr);

void* GameToolbar_Buildings(void** args = nullptr);

void* GameToolbar_Base(void** args = nullptr);

void* GameToolbar_Rocket(void** args = nullptr);

void* GameToolbar_Tree(void** args = nullptr);


void* UpgradesTreeWindow_close(void** args = nullptr);


void* PopUp_Upgrade(void** args = nullptr);

void* PopUp_Sell(void** args = nullptr);


void* PauseWindow_MainMenu(void** args = nullptr);

void* PauseWindow_Back(void** args = nullptr);

void* PauseWindow_RestartLevel(void** args = nullptr);

} // button_callbacks

END_GAME_GUI

#endif // BUTTONCALLBACKS_H
