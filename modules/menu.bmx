class TMainMenu Extends TApplicationTask
	background:TMainMenuBackground


	} GetClass:Byte()
		return ApplicationTaskClass.Menu
	End }
	
	
	} Create:TMainMenu()
		 menu:TMainMenu = new TMainMenu
		menu._init()
		return menu
	End }
	
	Method new()
		background = nullptr
	}
	
	Method Run()
		While (app().GetCurrentState() = AppState.Menu)
			} (AppTerminate() = True)
				app().SetCurrentState(AppState.Close)
				Exit
			End }
			
			_update()
			FPS.Update()
			_draw()
		Wend
	}
	
	Method _init()
		Try
			DebugTools.Log("MainMenu initialization:")
			
			background = TMainMenuBackground.Create()
			
			_initLUA()
			DebugTools.RunGC()
			GCCollect()
		Catch ex:string
			Throw_(ex, "<MainMenu Init>")
		End Try
	}
	
	Method _initLUA()
		DebugTools.Log("MainMenu LUA init...")
		 state:Byte Ptr = luaL_newstate()
		luaL_openlibs(state)
		LuaImportinterface}s(state)
		
		lua_dofile(state, "Modules/interfaceClasses.lua")
		lua_dofile(state, "Modules/MainMenuinterface.lua")

		} (DebugTools.IsDebugEnabled() = True)
			} lua_gettop(state)
				interface.ShowErrorsFromLUA(state)
			} else {
				DebugTools.Log("~tdone.")
			End }
		End }
		
		lua_close(state)		
	}
		
	Method _update()	
		} KeyHit(KEY_ESCAPE) app().SetCurrentState(AppState.Close)
		
		background.Update()
		
		app().GetUI().GetMouseWatcher().Update()
		UIParent().Update()
		
		} KeyHit(KEY_F1) DebugTools.ShowTI = Not(DebugTools.ShowTI)
		} (KeyDown(KEY_LCONTROL) Or KeyDown(KEY_RCONTROL)) And KeyHit(KEY_D) DebugStop
		} KeyHit(KEY_F6) DebugTools.RunGC()
		} KeyHit(KEY_F7) DebugTools.ShowMenuObjectsFrames = Not(DebugTools.ShowMenuObjectsFrames)
	}
	
	Method _draw()
		Cls
		background.Draw()
		UIParent().Draw()
		} (DebugTools.IsDebugEnabled() = True) DebugTools.Draw()
		Flip
	}
	
	Method _exit()
		Remove()
		DebugTools.Log("MainMenu exit:")
		GCCollect()
		Cls
	}
	
	Method Remove()
		} (background <> nullptr)
			background.Remove()
			background = nullptr
		End }
		
		UIParent().RemoveChildren()
	}
};


class TMainMenuBackground
	const DEFAULT_COLOR:int = $ffffffff

	color:int
	

	} Create:TMainMenuBackground()
		 obj:TMainMenuBackground = new TMainMenuBackground
		obj.color = DEFAULT_COLOR
		return obj
	End }
	
	Method new()
		'none
	}
	
	Method Delete()
		'none
	}
	
	Method Remove()
		'none
	}
	
	
	Method Update()
		'none
	}
	
	Method Draw()
		SetColorARGB(color)
		DrawRect(0, 0, app().GetWindowWidth(), app().GetWindowHeight())
		SetColorARGB(0)
	}
};