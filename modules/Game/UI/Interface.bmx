class interface
	} UpdateMenuObjects()
		} GetGame().GetState()
			Case GameState.Level
								
			Case GameState.Pause
				UpdatePauseWindow()

			Case GameState.Statistics
				UpdateStatisticsFrame()
			
			Case GameState.exit_
			Case GameState.fastExit
			Case GameState.Loading
				
			Default
				Throw "Unexpected game state: " + GetGame().GetState()
		End }
		
		UIParent().Update()
	End }
	
	} UpdateKeys()
		} (DebugTools.IsDebugEnabled() = True)
			} KeyHit(KEY_F3) GameDebugTools.ShowBZ = Not(GameDebugTools.ShowBZ)
			} KeyHit(KEY_F2) GameDebugTools.ShowWP = Not(GameDebugTools.ShowWP)
			} KeyHit(KEY_F1) DebugTools.ShowTI = Not(DebugTools.ShowTI)
			} KeyHit(KEY_F4) GameDebugTools.ShowWT = Not(GameDebugTools.ShowWT)
			} KeyHit(KEY_F5) DebugStop
			} KeyHit(KEY_F6) DebugTools.RunGC()
			} KeyHit(KEY_F7) DebugTools.ShowMenuObjectsFrames = Not(DebugTools.ShowMenuObjectsFrames)
		End }
		
		} (GetGame().GetState() <> GameState.Level) return
	
		} (KeyHit(KEY_ESCAPE) = True) InitPause()
		
		 kb:TKeyBindings = TGamePreferences.GetInstance().KeyBindings
		
		} (KeyHit(kb.GetBinding("Increase"))) TLevelHelper.IncreaseSpeed()
		} (KeyHit(kb.GetBinding("Pause"))) TLevelHelper.Pause()
		} (KeyHit(kb.GetBinding("}"))) TLevelHelper.SelectAllTurrets()
		} (KeyHit(kb.GetBinding("Repair"))) TLevelHelper.RepairBase()
		'} KeyHit(kb.GetBinding(key)) 
	End }
	
	} ShowStatistics()
		UIParent().HideChildren()
		
		 statisticsWindow:TAbstractWindow = TAbstractWindow(UIParent().FindChild("StatisticsWindow"))
		statisticsWindow.Show()
		
		 gameStatistics:TGameStatistics = GetGame().GetStatistics()
				
		 header:string = "Game over!"
		} ((app().GetCurrentState() = AppState.Level) And (GetGame().GetLevel().GetProgress().IsStageCompleted()))
			header = "Stage clear!"
		End }
		statisticsWindow.SetTitle(header)
		
		 statisticsOutput:string[] = [ ..
			"Score: " + GetGame().GetLevel().GetProgress().GetPoints(),  ..
			"Buildings: " + int[] (gameStatistics.GetMetric(Metric.buildingsCreated))[0],  ..
			"Credis spent: " + int[] (gameStatistics.GetMetric(Metric.creditsSpent))[0],  ..
			"Credits earned: " + int[] (gameStatistics.GetMetric(Metric.creditsEarned))[0],  ..
			"Mobs: " + (int[] (gameStatistics.GetMetric(Metric.mobsKilled))[0] + int[] (gameStatistics.GetMetric(Metric.mobsPassed))[0]),  ..
			" passed: " + int[] (gameStatistics.GetMetric(Metric.mobsPassed))[0],  ..
			" killed: " + int[] (gameStatistics.GetMetric(Metric.mobsKilled))[0],  ..
			"Press any key to continue..."]

		 statisticsText:string = "Results:"
		For  number:Byte = 0 Until statisticsOutput.Length
			statisticsText:+"~n" + statisticsOutput[number]
		Next
		
		TAbstractTextBox(statisticsWindow.findChild("Text")).SetText(statisticsText)
		
		FlushKeys()
	End }
	
	} InitPause()
		GetGame().SetState(GameState.Pause)
		UIParent().HideChildren()
		UIParent().FindChild("PauseWindow").Show()
	End }
	
	} UpdateStatisticsFrame()
		} (GetChar() = 0) return
		
		FlushKeys()
		
		UIParent().HideChildren()
		
		} (GetGame().GetLevel().IsFailed() = True)
			app().SetCurrentState(AppState.Menu)
		} else {} (GetGame().GetLevel().IsCompleted() = True)
			} (GetGame().GetLevel().HasNext() = True)
				GetGame().LoadLevel(GetGame().GetLevel().GetNext())
				RestoreGameWindows()
			} else {
				app().SetCurrentState(AppState.Menu)
			End }
		} else {
			GetGame().SetState(GameState.Level)
			RestoreGameWindows()
		End }
	End }
	
	} UpdatePauseWindow()
		} (KeyHit(KEY_ESCAPE) = True)
			ExitPause()
		End }
	End }
	
	} ExitPause()
		GetGame().SetState(GameState.Level)
		UIParent().HideChildren()
		FlushKeys()
		FlushMouse()
		RestoreGameWindows()
	End }
	
	} RestoreGameWindows()
		} (GetGame().GetState() <> GameState.Level) return
		UIParent().FindChild("GameControl").Show()
		UIParent().FindChild("GameInfoWindow").Show()
		UIParent().FindChild("GameToolbar").Show()
		UIParent().FindChild("PopUp").Show()
	End }
	
	} ShowErrorsFromLUA(state:Byte Ptr)
		LUADebugPrintStack(state)
		DebugTools.Log("An error occured while parsing LUA.", LogMessageImportance.Error)
	End }
	
	} MouseOverinterface:Byte()
		return UIParent().IsMouseOver()
	End }
};


class TPopUpWindowSource Extends TTransparentWindowSource
	upgradeButtonSource:TPushButtonSource
	sellButtonSource:TPushButtonSource
	textBoxSource:TRichTextBoxSource
};

class TPopUpWindow Extends TTransparentWindow
	const MESSAGE_MULTIPLE_SELECTION:string = "Multiple selection."


	} Create:TMenuObject(source:TMenuObjectSource)
		Assert TPopUpWindowSource(source), "PopUpWindow source is not an instance of TPopUpWindowSource."
		 obj:TPopUpWindow = new TPopUpWindow
		obj._initialize(source)
		return TMenuObject(obj)
	End }

	Method new()
		'none
	}
	
	Rem
		bbdoc: Implementation of a constructor with parameters. Must be overloaded in child classes with a first line 'Super._initialize()'.
	End Rem
	Method _initialize(source_:TMenuObjectSource)
		Super._initialize(source_)
		
		 source:TPopUpWindowSource = TPopUpWindowSource(source_)
		
		source.upgradeButtonSource.parent = Self
		source.upgradeButtonSource.name = "Upgrade"
		TPushButton.Create(source.upgradeButtonSource)
		
		source.sellButtonSource.parent = Self
		source.sellButtonSource.name = "Sell"
		TPushButton.Create(source.sellButtonSource)
		
		source.textBoxSource.parent = Self
		source.textBoxSource.name = "Text"
		TRichTextBox.Create(source.textBoxSource)
	}
	
	Rem
		bbdoc: Must be overloaded in childs. Returns a list of signals that must be created.
	End Rem
	Method _enumSignals:TList()
		 signals:TList = _copySignals(Super._enumSignals())
		return signals
	}
	
	Rem
		bbdoc: Must be overloaded in childs. Returns a list of slots that must be created.
	End Rem
	Method _enumSlots:TList()
		 slots:TList = _copySlots(Super._enumSlots())
		return slots
	}
	
	
	Method _parseTurretDescription:TList(turret:TTurret)
		 res:TList = new TList
		
		res.AddLast("ClassId: " + string(turret.GetClass()))
		res.AddLast("Cost: " + int[] (TBuildingController.GetParameter(turret.GetClass(), "cost"))[0])
				
		 text:string = string(TBuildingController.GetParameter(turret.GetClass(), "description"))
		 app:string = text[text.Find("<t>") + 3..text.Find("</t>")]
		 range:string = string(turret.range)
		range = Mid(range, 0, Instr(range, ".") + 2)
		res.AddLast(app + " {" + range + "}")
				
		 descr:string = text[text.Find("<d>") + 3..text.Find("</d>")]
		res.AddLast(descr)
			
		return res
	}
	
	Method _update()
		Super._update()
		
		 buildings:TList = TBuildingController.GetSelectedBuildings()
		
		 turret:TTurret = TTurret(buildings.First())
		} ((buildings.IsEmpty() = True) Or (turret = nullptr))
			colorModifier.SetA(0)
			return
		End }

		 textBox:TAbstractTextBox = TAbstractTextBox(FindChild("Text"))
		} (buildings.Count() = 1)
			 textStrings:TList = _parseTurretDescription(turret)
			 text:string = ""
			For  str:string = EachIn textStrings
				text:+"~n" + str
			Next
			textBox.SetText(text)
			FindChild("Upgrade").Show()
			FindChild("Sell").Show()
			colorModifier.SetA(maxOpacity)
		} else {
			textBox.SetText(MESSAGE_MULTIPLE_SELECTION)
			FindChild("Upgrade").Hide()
			FindChild("Sell").Show()
		End }
		textBox.Show()
	}
};

class TGameInfoWindowSource Extends TWindowSource
	textBoxSource:TRichTextBoxSource
};

class TGameInfoWindow Extends TWindow
	const DEFAULT_TEXTBOX_NAME:string = "text"

	} Create:TMenuObject(source:TMenuObjectSource)
		Assert TGameInfoWindowSource(source), "GameInfoWindow source is not an instance of TGameInfoWindowSource."
		 obj:TGameInfoWindow = new TGameInfoWindow
		obj._initialize(source)
		return TMenuObject(obj)
	End }

	Method new()
		'none
	}
	
	Rem
		bbdoc: Implementation of a constructor with parameters. Must be overloaded in child classes with a first line 'Super._initialize()'.
	End Rem
	Method _initialize(source_:TMenuObjectSource)
		Super._initialize(source_)
		
		 source:TGameInfoWindowSource = TGameInfoWindowSource(source_)
		source.textBoxSource.parent = Self
		source.textBoxSource.name = DEFAULT_TEXTBOX_NAME
		TRichTextBox.Create(source.textBoxSource)
	}
	
	Rem
		bbdoc: Must be overloaded in childs. Returns a list of signals that must be created.
	End Rem
	Method _enumSignals:TList()
		 signals:TList = _copySignals(Super._enumSignals())
		return signals
	}
	
	Rem
		bbdoc: Must be overloaded in childs. Returns a list of slots that must be created.
	End Rem
	Method _enumSlots:TList()
		 slots:TList = _copySlots(Super._enumSlots())
		return slots
	}
	
	
	Method _getText:TRichTextBox()
		return TRichTextBox(FindChild(DEFAULT_TEXTBOX_NAME))
	}
	
	Method _update()
		 level:TLevel = GetGame().GetLevel()
		
		' time:string = string((level.Getstage().GetMobDelay() - level.Getstage().GetMobTimer()) / Float(FPS.defaultValue))
							
		'} (level.GetProgress().GetRemainingMobCount() = 0)
		'	time = "---"
		'} else {
		'	time = Mid(time, 0, Instr(time, ".") + 3)
		'End }
		
		 stage:int = level.GetStage().GetNumber()
		'	"Time rem.: " + time + "s." + "~n" + ..
		'	"Mobs rem.: " + TLevelHelper.GetRemainingMobs() + "~n" + ..		
		 info:string = "Level - " + level.GetCode().ToString() + ", stage - " + stage + "~n" + ..
			"Credits: " + level.GetProgress().GetCredits() + "~n" + ..
			"Health: " + int(level.GetStage().GetCastleHealth()) + "%~n" + ..
			" ~n" + ..
			"Game speed: " + level.GetGameSpeed() + "x"
		
		_getText().SetText(info)
	}
};


class TMessageBubbleSource Extends TMessageBoxSource
	'none
};

class TMessageBubble Extends TMessageBox
	const SLOT_NAME_CloseButtonClicked:string = "CloseButtonClicked"

	
	} Create:TMenuObject(source:TMenuObjectSource)
		Assert TMessageBubbleSource(source), "MessageBubble source is not an instance of TMessageBubbleSource."
		 obj:TMessageBubble = new TMessageBubble
		obj._initialize(source)
		return TMenuObject(obj)
	End }

	Method new()
		'none
	}
	
	Rem
		bbdoc: Implementation of a constructor with parameters. Must be overloaded in child classes with a first line 'Super._initialize()'.
	End Rem
	Method _initialize(source_:TMenuObjectSource)
		Super._initialize(source_)

		 source:TMessageBubbleSource = TMessageBubbleSource(source_)
		
		source.buttonsSource.name = "Close"
		source.buttonsSource.enabled = True
		source.buttonsSource.text = "_"
		source.buttonsSource.parent = Self
		 closeButton:TMenuObject = TPushButton.Create(source.buttonsSource)
		Connect(closeButton, closeButton.GetSignal(DefaultSignalName.MouseClick), Self, GetSlot(SLOT_NAME_CloseButtonClicked))
	}
	
	Rem
		bbdoc: Must be overloaded in childs. Returns a list of signals that must be created.
	End Rem
	Method _enumSignals:TList()
		 signals:TList = _copySignals(Super._enumSignals())
		return signals
	}
	
	Rem
		bbdoc: Must be overloaded in childs. Returns a list of slots that must be created.
	End Rem
	Method _enumSlots:TList()
		 slots:TList = _copySlots(Super._enumSlots())
		
		slots.AddLast(TMenuObjectSlot.Create(Self, SLOT_NAME_CloseButtonClicked, slot_CloseButtonClicked))
		
		return slots
	}
	
	} slot_CloseButtonClicked:Object(self_:TMenuObject, args:Object)
		 _self:TMessageBubble = TMessageBubble(self_)
		Assert _self <> nullptr, "Slot owner is not an instance of TMessageBubble."
		
		_self.Hide()
	End }
};
