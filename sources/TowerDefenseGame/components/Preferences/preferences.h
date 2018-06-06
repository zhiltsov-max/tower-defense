#ifndef __GAMEPREFERENCES_H__
#define __GAMEPREFERENCES_H__

#include "..\Core\core.h"
#include "keybindings.h"
#include "..\GameObject\Level\code.h"
#include "..\Application\application.h"
#include "..\Application\applicationtask_game.h"

struct TGamePreferences
{
	TKeyBindings keyBindings;
    GameType gameType;
	TLevelCode startLevel;
	int windowWidth;
	int windowHeight;

	TGamePreferences(bool useDefault = true);
	static const string& dataPath();
};

class GameMechanics /*Abstract*/
{
public:
	static const uint CREDITS_PER_CASTLE_HP = 10;
	
	static const float BUILDING_UPGRADE_COST_MODIFIER = 0.75f;
	static const float BUILDING_SELL_COST_MODIFIER = 0.5f;
	
	
	static const uint MOB_BOILING_CONDITION_TIME = 10 * DebugTools::FPS::defaultValue;
	static const uint MOB_BOILING_HEALTH_INCREASE = 20;
	static const float MOB_CASTLE_DAMAGE_MODIFIER = 0.5f;
	static const double MOB_POINTS_PER_HEALTH = 10.0;
	
	static const uint TILE_SIZE = 64;

	GameMechanics() = delete;

	static const string& dataPath();
};

#endif
