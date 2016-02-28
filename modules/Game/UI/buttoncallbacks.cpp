#include "buttoncallbacks.h"
#include "..\Application\applicationtask_game.h"
#include "..\Application\applicationtask_menu.h"
#include "..\GameObject\Buildings\controller.h"
#include "..\GameObject\Buildings\turret.h"
#include "..\GameObject\Buildings\tb_base.h"
#include "..\GameObject\Buildings\tb_rocket.h"
#include "..\GameObject\Level\helper.h"

BEGIN_GAME_GUI

namespace button_callbacks {

    void* MainMenu_Start(void** args) {
        UIParent()->FindChild("MainMenu")->Hide();
        UIParent()->FindChild("StartMenu")->Show();
    }

    void* MainMenu_Exit(void** args) {
        app()>setCurrentState(AppState::Exit);
    }

    void* StartMenu_StartA(void** args) {
        UIParent()->RemoveChildren();
        app()>setCurrentState(AppState::Level);
        TGamePreferences.().SetGameType(GameType::Normal);
        TGamePreferences.().SetStartLevel(TLevelCode::level_1_company_1());
    }

    void* StartMenu_StartB(void** args) {
        UIParent()->RemoveChildren();
        app()>SetCurrentState(AppState::Level);
        TGamePreferences.().SetGameType(GameType::Free);
        TGamePreferences.().SetStartLevel(TLevelCode::level_1_free_1());
    }

    void* StartMenu_Back(void** args) {
        UIParent()->FindChild("StartMenu")->Hide();
        UIParent()->FindChild("MainMenu")->Show();
    }


    void* GameControl_Start(void** args) {
        LevelHelper::increaseSpeed();
    }

    void* GameControl_Pause(void** args) {
        LevelHelper::pause();
    }

    void* GameControl_Exit(void** args) {
        GetGame().setState(GameState::fastExit);
    }

    void* GameToolbar_Zone(void** args) {
        BuildingsController::setSelectionOfAll(true);
    }

    void* GameToolbar_Repair(void** args) {
        LevelHelper::repairBase();
    }

    void* GameToolbar_Buildings(void** args) {
        auto base = UIParent()->FindChild("BuildingsWindow");
        base->SetVisibility( !base->IsShown() );
    }

    void* GameToolbar_Base(void** args) {
        if (LevelHelper::getLevelInstance().getGameSpeed() == LevelSpeed::Pause) {
            return nullptr;
        }

        if (BuildingsController::isAllPlaced() == false) {
            return nullptr;
        }

        BuildingsController::setSelectionOfAll(false);

        TB_Base* newTurret = new TB_Base;
        newTurret->initialize( get tb base info );
        LevelHelper::getInstance().getScene().addObject(newTurret);
    }

    void* GameToolbar_Rocket(void** args) {
        if (BuildingsController::isAllPlaced() == false) {
            return nullptr;
        }

        BuildingsController::setSelectionOfAll(false);

        TB_Rocket* newTurret = new TB_Rocket;
        newTurret->initialize();
        LevelHelper::getInstance().getScene().addObject(newTurret);
    }

    void* GameToolbar_Tree(void** args) {
        UIParent()->FindChild("GameToolbar")->Hide();
        UIParent()->FindChild("UpgradesTree")->Show();
    }


    void* UpgradesTreeWindow_close(void** args) {
        UIParent()->FindChild("UpgradesTree")->Hide();
        UIParent()->FindChild("GameToolbar")->Show();
    }


    void* PopUp_Upgrade(void** args) {
        auto selectedBuildings = BuildingController::getSelectedBuildings();
        if (selectedBuildings.size() == 1) {
            auto building = selectedBuildings.front();
            auto upgrades = TBuildingUpgrades::findUpgradesFor(building->getMajorUpgrade());
            building->UpgradeTo(TBuildingUpgrades.GetInstance().FindClassForMajorUpgrade(TBuildingUpgrade(upgrades.First()).GetID()));
        } else {
            UIParent()->FindChild<GUI::TAbstractTextBox>(string("PopUp") + UIParent().keySep() + "Text")->SetText(ERROR_SELECT_ONE);
        }
    }

    void* PopUp_Sell(void** args) {
        auto selectedBuildings = BuildingController::getSelectedBuildings();
        for (auto& building : selectedBuildings) {
            building->sell();
        }
    }


    void* PauseWindow_MainMenu(void** args) {
        app()>setCurrentState(AppState::Menu);
    }

    void* PauseWindow_Back(void** args) {
        Game::GUI::exitPause();
    }

    void* PauseWindow_RestartLevel(void** args) {
        //TO DO:
    }

} // button_callbacks

END_GAME_GUI
