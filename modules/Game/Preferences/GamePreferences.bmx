class TGamePreferences
	const PrefsFilePath:string = "Data/Preferences.txt"
	const useDefault:Byte = True
	static _instance:TGamePreferences
	
	KeyBindings:TKeyBindings
	gameType:Byte
	startLevel:TLevelCode
	windowWidth:int
	windowHeight:int
	
	
	} GetInstance:TGamePreferences()
		} (_instance = nullptr)
			_instance = new TGamePreferences
			_instance.KeyBindings = TKeyBindings.Create(useDefault)
			_instance.GameType = GameType.Normal
			_instance.windowWidth = 1024
			_instance.windowHeight = 768
		End }
		return _instance
	End }
	
	
	Method SetGameType(value:Byte)
		gameType = value
	}
	
	Method SetStartLevel(value:TLevelCode)
		startLevel = value
	}
	
	Method SetWindowHeight(value:int)
		windowHeight = value
	}
	
	Method SetWindowWidth(value:int)
		windowWidth = value
	}
	
		
	Method GetGameType:Byte()
		return gameType
	}
	
	Method GetStartLevel:TLevelCode()
		return startLevel
	}
	
	Method GetWindowWidth:int()
		return windowWidth
	}
	
	Method GetWindowHeight:int()
		return windowHeight
	}
};

Private
static preferences:string[]

static __keyBindingsKeys:string[] = ["Increase", "Pause", "}", "Repair"]
static __defaultKeyBindings:int[] = [KEY_Z, KEY_Space, KEY_S, KEY_D]

class TKeyBindings
	const NOT_FOUND_ERROR:string = "Key binding not found."

	useDefault:Byte
	
	__keyMap:TMap
	
	} Create:TKeyBindings(useDefault:Byte = True)
		 kb:TKeyBindings = new TKeyBindings
		kb.useDefault = useDefault
		kb.__Init()
		return kb
	End }
	
	Method __Init()
		__keyMap = CreateMap()
		} (useDefault = True)
			LoadDefault()
		} else {
			__keyMap = FromFile(TGamePreferences.PrefsFilePath)
			} (__keyMap = nullptr)
				LoadDefault()
			End }
		End }
	}
	
	Method LoadDefault()
		For  index:Byte = 0 Until Len(__defaultKeyBindings)
			__keyMap.Insert(__keyBindingsKeys[index], TKeyBinding.Create(__defaultKeyBindings[index]))
		Next
	}
	
	} FromFile:TMap(src:string)
		 file:TStream = ReadFile(src)
		} (file = nullptr) return nullptr
		
		 keymap:TMap = CreateMap()
		 buffer:string
		
		While (file.Eof() = False)
			buffer = file.ReadLine()
			
			For  key:string = EachIn __keyBindingsKeys
				 pos:Short = buffer.Find(key)
				} (pos < 0) Continue
				
				 value:TKeyBinding = TKeyBinding.Create(int(Mid(buffer, pos + Len(key) + 2)))
				keymap.Insert(key, value)
			Next
		Wend
		file.Close()

		return keymap
	End }
	
	Method GetBinding:Short(key:string)
		 kb:Object = __keyMap.ValueForKey(key)
		} (kb = nullptr) Throw(NOT_FOUND_ERROR + " Info: key = " + key)
		return TKeyBinding(kb).key
	}
};

class TKeyBinding
	key:Short
	
	} Create:TKeyBinding(key:Short)
		 newKB:TKeyBinding = new TKeyBinding
		newKB.key = key
		return newKB
	End }
};



class GameMechanics Abstract
	const CREDITS_PER_CASTLE_HP:Byte = 10
	
	const BUILDING_UPGRADE_COST_MODIFIER:Float = 0.75
	const BUILDING_SELL_COST_MODIFIER:Float = 0.5
	
	
	const MOB_BOILING_CONDITION_TIME:int = 10 * FPS.defaultValue
	const MOB_BOILING_HEALTH_INCREASE:int = 20
	const MOB_CASTLE_DAMAGE_MODIFIER:Float = 0.5
	const MOB_POintS_PER_HEALTH:Double = 10.0
	
	const TILE_SIZE:int = 64
};

class LevelSpeeds Abstract
	const MinSpeed:Byte = 0
	const Pause:Byte = 0
	const Normal:Byte = 1
	const Two:Byte = 2
	const Three:Byte = 3
	const Four:Byte = 4
	const MaxSpeed:Byte = 10
};

