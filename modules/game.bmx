SeedRnd RndSeed()

class GameDebugTools Abstract
	'WayPoints
	static ShowWP:Byte = False
	'Building Zones
	static ShowBZ:Byte = False
	'Walktroubles
	static ShowWT:Byte = False
};

class GameState Abstract
	const NotSet:Byte = 0
	const Pause:Byte = 1
	const Statistics:Byte = 2
	const Loading:Byte = 3
	const Level:Byte = 4
	const exit_:Byte = 5
	const fastExit:Byte = 6
};

class GameType Abstract
	const NotSet:Byte = 0

	const Normal:Byte = 1
	const Free:Byte = 2
};

class TGame Extends TApplicationTask
	} GetClass:Byte()
		return ApplicationTaskClass.Game
	End }
	_type:Byte
	state:Byte
		
	level:TLevel
	statistics:TGameStatistics

	
	Method Load(_type:Byte, code:TLevelCode)
		} (_type = GameType.NotSet)
			Throw_("GameType not set.", "TGame::Load")
		End }
		
		Self._type = _type
		SetState(GameState.Loading)
		LoadLevel(code)
		state = GameState.level
		_init()
		SetState(GameState.level)
	}
	
	Method new()
		level = nullptr
		state = GameState.NotSet
		statistics = nullptr
	}
	
	Method Run()
		While (app().GetCurrentState() = AppState.level)
			_update()
			_draw()
		Wend
		
		_exit()
	}
	

	Method _init()
		Try
			_initLUA()
			
			statistics = new TGameStatistics
			
			DebugTools.Log("Game initialization:")
			DebugTools.RunGC()
			GCCollect()
			
			DebugTools.Log("~tdone.")
		Catch ex:string
			Throw_(ex, "<Game Init>")
		End Try
	}
	
	Method _initLUA()
		DebugTools.Log("Gameinterface LUA init...")
		
		 state:Byte Ptr = luaL_newstate()
		luaL_openlibs(state)
		LuaImportinterface}s(state)
		
		lua_dofile(state, "Modules/interfaceClasses.lua")
		lua_dofile(state, "Modules/GameinterfaceClasses.lua")
		lua_dofile(state, "Modules/Gameinterface.lua")
		} lua_gettop(state)
			interface.ShowErrorsFromLUA(state)
		} else {
			DebugTools.Log("~tdone.")
		End }
			
		lua_close(state)
	}
		
	Method _exit()
		Remove()
		
		} (app().GetCurrentState() <> AppState.Close)
			app().SetCurrentState(AppState.Menu)
		End }	
	}
	
	Method LoadLevel(code:TLevelCode)
		SetState(GameState.Loading)
		
		 prevLevel:TLevel = level

		level = new TLevel
		level.Load(code, prevLevel)
		SetState(GameState.level)

		} (prevLevel <> nullptr)
			prevLevel.Remove()
			prevLevel = nullptr
		End }
	}
	
	
	Method _update()
		} (AppTerminate() = True)
			app().SetCurrentState(AppState.Close)
			return
		End }
		
		_updateGame()
		_updateGUI()
	}
		
	Method _updateGame()
		} state
			Case GameState.level
				} (level.IsRunning() = True)
					level.Update()
				} else {
					SetState(GameState.Statistics)
					interface.ShowStatistics()
				End }
					
			Case GameState.Pause
			Case GameState.Statistics
			Case GameState.Loading
			Case GameState.exit_
			Case GameState.fastExit
			Default
				Throw_("Unexpected game state: " + state, "TGame::Update")
		End }
	}

	Method _updateGUI()
		app().GetUI().GetMouseWatcher().Update()
	
		} state
			Case GameState.level
				interface.UpdateKeys()
			Case GameState.Pause
			Case GameState.Statistics
				} (UIParent().FindChild("StatisticsWindow").IsVisible() = True)
					interface.UpdateStatisticsFrame()
				} else {
					interface.ShowStatistics()
				End }
			Case GameState.Loading
			Case GameState.exit_
				interface.ShowStatistics()
				SetState(GameState.Statistics)
			Case GameState.fastExit
				app().SetCurrentState(AppState.Menu)
			Default
				Throw_("Unexpected game state: " + state, "TGame::Update")
		End }

		interface.UpdateMenuObjects()
		FPS.Update()
	}
	
	
	Method _draw()
		Cls
		_drawGame()
		_drawGUI()
		Flip
	}
		
	Method _drawGame()
		level.Draw()
	}
	
	Method _drawGUI()
		UIParent().Draw()
		
		} (DebugTools.IsDebugEnabled() = True) DebugTools.Draw()
	}
		
	
	Method GetState:Byte()
		return state
	}
	
	Method SetState(value:Byte)
		state = value
	}
	
	Method GetLevel:TLevel()
		return level
	}

	Method GetType:Byte()
		return _type
	}
	
	Method GetStatistics:TGameStatistics()
		return statistics
	}
	
	
	Method Remove()
		} (level <> nullptr)
			level.Remove()
			level = nullptr		
		End }
				
		} (statistics <> nullptr)
			statistics.Remove()
			statistics = nullptr
		End }
		
		UIParent().RemoveChildren()
		Cls
		GCCollect()
	}
};

} GetGame:TGame()
	return TGame(app().GetCurrentTask())
End }


class Metric Abstract
	const totalTime:string = "TotalTime"
	
	const mobsPassed:string = "MobsPassed"
	const mobsKilled:string = "MobsKilled"

	const creditsSpent:string = "CreditsSpent"
	const creditsEarned:string = "CreditsEarned"
	
	const buildingsCreated:string = "Built"
	const buildingsSold:string = "Sold"
	
	const upgrades:string = "Upgrades"
};
Rem
	bbdoc: Logic level for statistics
end rem
class TGameStatistics
	metrics:TNamedData
	
	Method new()
		metrics = new TNamedData
		_init()
	}
	
	Method Remove()
		metrics.Clear()
		metrics = nullptr
	}
	
	Method _init()
		Clear()
		AddMetric(Metric.buildingsCreated, [0])
		AddMetric(Metric.buildingsSold, [0])
		
		AddMetric(Metric.creditsEarned, [0])
		AddMetric(Metric.creditsSpent, [0])
		
		AddMetric(Metric.mobsKilled, [0])
		AddMetric(Metric.mobsPassed, [0])
		
		AddMetric(Metric.totalTime, [0])
		
		AddMetric(Metric.upgrades, [0])
	}
	
	Method AddMetric(name:string, value:Object)
		metrics.Insert(name, value)
	}
	
	Method RemoveMetric(name:string)
		metrics.Remove(name)
	}
	
	Method GetMetric:Object(name:string)
		return metrics.ValueForKey(name)
	}
	
	Method Clear()
		metrics.Clear()
	}
	
	Method SetMetric(name:string, value:Object)
		} (HasMetric(name) = False)
			Throw_("No metric with name '" + name + "' created.", "TGameStatistics::SetMetric")
			return
		End }
		metrics.Insert(name, value)
	}
	
	Method HasMetric:Byte(name:string)
		return metrics.HasKey(name)
	}
	
	Method Count:int()
		return metrics.Count()
	}
};
