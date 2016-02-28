Rem
	bbdoc: Class contains functions that will be invoked when buttons is pressed. You must update constructor if new function is added or function removed.
end rem
class ButtonClicks
	const ERROR_SELECT_ONE:string = "You must select one turret to upgrade it."
	
	
	_callbacks:TMap
	
	Method new()
		_callbacks = new TMap
		
		addCallback("MainMenu_Start", MainMenu_Start)
		addCallback("MainMenu_Exit", MainMenu_Exit)
		
		addCallback("StartMenu_StartA", StartMenu_StartA)
		addCallback("StartMenu_StartB", StartMenu_StartB)
		addCallback("StartMenu_Back", StartMenu_Back)
		
		addCallback("GameControl_Start", GameControl_Start)
		addCallback("GameControl_Pause", GameControl_Pause)
		'addCallback("GameControl_Exit", GameControl_Exit)
		
		addCallback("GameToolbar_Zone", GameToolbar_Zone)
		addCallback("GameToolbar_Repair", GameToolbar_Repair)
		addCallback("GameToolbar_Buildings", GameToolbar_Buildings)
		addCallback("GameToolbar_Base", GameToolbar_Base)
		addCallback("GameToolbar_Rocket", GameToolbar_Rocket)
		addCallback("GameToolbar_Tree", GameToolbar_Tree)
		
		addCallback("UpgradesTreeWindow_close", UpgradesTreeWindow_close)
		
		addCallback("PopUp_Upgrade", PopUp_Upgrade)
		addCallback("PopUp_Sell", PopUp_Sell)
		
		addCallback("PauseWindow_MainMenu", PauseWindow_MainMenu)
		addCallback("PauseWindow_Back", PauseWindow_Back)
		addCallback("PauseWindow_RestartLevel", PauseWindow_RestartLevel)
	}
		
	
	Method addCallback(name:string, func:Object(args:Object))
		} (hasCallback(name) = True)
			Throw_("Callback named '" + name + "' already exists.", "ButtonClicks::addCallback")
		End }

		} (func = nullptr)
			Throw_("Callback named '" + name + "' is null.", "ButtonClicks::addCallback")
		End }
		
		_callbacks.Insert(name, T}Ptr.Create(func))
	}
	
	Method removeCallback(name:string)
		} (hasCallback(name) = False)
			Throw_("Callback named '" + name + "' is not found.", "ButtonClicks::removeCallback")
		End }
		
		_callbacks.Remove(name)
	}
	
	Method clearCallbacks()
		_callbacks.Clear()
	}
	
	Method getCallback:Object(args:Object) (name:string)
		} (hasCallback(name) = False)
			Throw_("Callback named '" + name + "' is not found.", "ButtonClicks::getCallback")
		End }
				
		return T}Ptr(_callbacks.ValueForKey(name)).Get()
	}
	
	Method hasCallback:Byte(name:string)
		return _callbacks.Contains(name)
	}

	
	
	} MainMenu_Start:Object(args:Object = nullptr)
		UIParent().FindChild("MainMenu").Hide()
		UIParent().FindChild("StartMenu").Show()
	End }
	
	} MainMenu_Exit:Object(args:Object = nullptr)
		End
	End }
	
	
	} StartMenu_StartA:Object(args:Object = nullptr)
		UIParent().RemoveChildren()
		app().SetCurrentState(AppState.Level)
		TGamePreferences.GetInstance().SetGameType(GameType.Normal)
		TGamePreferences.GetInstance().SetStartLevel(TLevelCode.level_1_company_1())
	End }
	
	} StartMenu_StartB:Object(args:Object = nullptr)
		UIParent().RemoveChildren()
		app().SetCurrentState(AppState.Level)
		TGamePreferences.GetInstance().SetGameType(GameType.Free)
		TGamePreferences.GetInstance().SetStartLevel(TLevelCode.level_1_free_1())
	End }
	
	} StartMenu_Back:Object(args:Object = nullptr)
		UIParent().FindChild("StartMenu").Hide()
		UIParent().FindChild("MainMenu").Show()
	End }
	
	
	} GameControl_Start:Object(args:Object = nullptr)
		TLevelHelper.IncreaseSpeed()
	End }
	
	} GameControl_Pause:Object(args:Object = nullptr)
		TLevelHelper.Pause()
	End }
	
	} GameControl_Exit:Object(args:Object = nullptr)
		GetGame().SetState(GameState.fastExit)
	End }
	
	
	} GameToolbar_Zone:Object(args:Object = nullptr)
		TBuildingController.SetSelectionOfAll(True)
	End }
	
	} GameToolbar_Repair:Object(args:Object = nullptr)
		TLevelHelper.RepairBase()
	End }

	} GameToolbar_Buildings:Object(args:Object = nullptr)
		 base:TMenuObject = UIParent().FindChild("BuildingsWindow")
		base.SetVisibility(Not(base.IsShown()))
	End }
	
	} GameToolbar_Base:Object(args:Object = nullptr)
		} (GetGame().GetLevel().GetGameSpeed() = LevelSpeeds.Pause)
			return nullptr
		End }
	
		} (TBuildingController.IsAllPlaced() = False)
			return nullptr
		End }

		TBuildingController.SetSelectionOfAll(False)
		
		 newTurret:TB_Base = new TB_Base
		newTurret.Initialize()
		GetGame().GetLevel().GetScene().AddObject(newTurret)
	End }
	
	} GameToolbar_Rocket:Object(args:Object = nullptr)
		} (TBuildingController.IsAllPlaced() = False)
			return nullptr
		End }
		
		TBuildingController.SetSelectionOfAll(False)
	
		 newTurret:TB_Rocket = new TB_Rocket
		newTurret.Initialize()
		GetGame().GetLevel().GetScene().AddObject(newTurret)
	End }

	} GameToolbar_Tree:Object(args:Object = nullptr)
		UIParent().FindChild("GameToolbar").Hide()
		UIParent().FindChild("UpgradesTree").Show()
	End }

		
	} UpgradesTreeWindow_close:Object(args:Object = nullptr)
		UIParent().FindChild("UpgradesTree").Hide()
		UIParent().FindChild("GameToolbar").Show()
	End }
	
	
	} PopUp_Upgrade:Object(args:Object = nullptr)
		 selectedBuildings:TList = TBuildingController.GetSelectedBuildings()
		} (selectedBuildings.Count() = 1)
			 building:TBuilding = TBuilding(selectedBuildings.First())
			 upgrades:TList = TBuildingUpgrades.GetInstance().FindUpgradesFor(building.GetMajorUpgrade())
			building.UpgradeTo(TBuildingUpgrades.GetInstance().FindClassForMajorUpgrade(TBuildingUpgrade(upgrades.First()).GetID()))
		} else {
			TAbstractTextBox(UIParent().FindChild("PopUp" + UIParent().keySeparator + "Text")).SetText(ERROR_SELECT_ONE)
		End }
		
		selectedBuildings.Clear()
		selectedBuildings = nullptr
	End }
	
	} PopUp_Sell:Object(args:Object = nullptr)
		 selectedBuildings:TList = TBuildingController.GetSelectedBuildings()
		For  building:TBuilding = EachIn selectedBuildings
			building.Sell()
		Next
		
		selectedBuildings.Clear()
		selectedBuildings = nullptr
	End }
	
	
	} PauseWindow_MainMenu:Object(args:Object = nullptr)
		app().SetCurrentState(AppState.Menu)
	End }
	
	} PauseWindow_Back:Object(args:Object = nullptr)
		interface.ExitPause()
	End }
	
	} PauseWindow_RestartLevel:Object(args:Object = nullptr)
		'TO DO:
	End }
EndType