#include "preferences.h"
#include "..\Application\applicationtask_game.h"


static const string prefsFilePath = "Data/Preferences.txt";
	
TGamePreferences::TGamePreferences(bool useDefault) :
	keyBindings(useDefault),
	gameType(GameType::Normal),
	windowWidth(useDefault ? 1024 : 0),
	windowHeight(useDefault ? 768 : 0)
{}

const string& TGamePreferences::dataPath() {
	return prefsFilePath;
}