class TUpgradesTreeItemSource Extends TMenuObjectSource
	dataSourceID:int
	description:string

	button:TPushButtonSource
	imageBox:TImageBoxSource
};

class UpgradesTreeItemState Abstract
	const undefined:Byte = 0
	const _min:Byte = 0
	
	const Disabled:Byte = 1
	const Enabled:Byte = 2
	const CanNotResearch:Byte = 3
	const CanResearch:Byte = 4
	const Researched:Byte = 5
	
	const _max:Byte = 4
};

class TUpgradesTreeItem Extends TMenuObject
	const COLOR_LINE_DARK:int = $80A0A0A0
	const COLOR_LINE_BRIGHT:int = $A0D0D0D0
	
	static _colorModifier_Enabled:StColorModifier
	} COLOR_MODIFIER_ENABLED:StColorModifier()
		} (_colorModifier_Enabled = nullptr)
			_colorModifier_Enabled = StColorModifier.Create(1, 1, 1, 1)
		End }
		return _colorModifier_Enabled
	End }
	
	static _colorModifier_Disabled:StColorModifier
	} COLOR_MODIFIER_DISABLED:StColorModifier()
		} (_colorModifier_Disabled = nullptr)
			_colorModifier_disabled = StColorModifier.Create(0.7, 0.7, 0.7, 1)
		End }
		return _colorModifier_Disabled
	End }


	dataID:int
	state:Byte
	description:string
	colorModifier:StColorModifier


	} Create:TMenuObject(source:TMenuObjectSource)
		Assert TUpgradesTreeItemSource(source), "UpgradesTreeItem source is not an instance of TUpgradesTreeItemSource."
		 obj:TUpgradesTreeItem = new TUpgradesTreeItem
		obj._initialize(source)
		return TMenuObject(obj)
	End }

	Method new()
		dataID = 0
		state = UpgradesTreeItemState.undefined
		description = nullptr
		colorModifier = StColorModifier.Create()
	}
	
	Rem
		bbdoc: Implementation of a constructor with parameters. Must be overloaded in child classes with a first line 'Super._initialize()'.
	End Rem
	Method _initialize(source_:TMenuObjectSource)
		Super._initialize(source_)
		
		 source:TUpgradesTreeItemSource = TUpgradesTreeItemSource(source_)
	
		state = UpgradesTreeItemState.Disabled
		
		dataID = source.dataSourceID
		
		description = source.description
		
		source.button.parent = Self
		source.button.text = GetUpgrade().GetCost()
		 button:TMenuObject = TPushButton.Create(source.button)
		Connect(button, button.GetSignal(DefaultSignalName.MouseClick), Self, GetSlot("tryResearch"))
		
		source.imageBox.parent = Self
		 imageBox:TMenuObject = TImageBox.Create(source.imageBox)
		Connect(imageBox, imageBox.GetSignal(DefaultSignalName.MouseClick), Self, GetSlot("imageBoxClicked"))
		
		} (0 < dataID)
			 prev:TUpgradesTreeItem = _getPreviousItem()
			Assert prev <> nullptr, "Previous item is not found for item " + GetName() + "."
			Connect(prev, prev.GetSignal("researched"), Self, GetSlot("previousResearched"))
			
			} (prev.GetUpgrade().IsResearched() = True)
				prev.GetSignal("researched").Send()
			End }
		End }
		SetState(_computeState())
	}
	
	Rem
		bbdoc: Must be overloaded in childs. Returns a list of signals that must be created.
	End Rem
	Method _enumSignals:TList()
		 signals:TList = _basicSignals()
		
		signals.AddLast(TMenuObjectSignal.Create(DefaultSignalName.ObjectEnabled))
		signals.AddLast(TMenuObjectSignal.Create(DefaultSignalName.ObjectDisabled))
		signals.AddLast(TMenuObjectSignal.Create("researched"))
		
		return signals
	}
	
	Rem
		bbdoc: Must be overloaded in childs. Returns a list of slots that must be created.
	End Rem
	Method _enumSlots:TList()
		 slots:TList = new TList
		
		slots.AddLast(TMenuObjectSlot.Create(Self, "previousResearched", slot_ItemResearched))
		slots.AddLast(TMenuObjectSlot.Create(Self, "imageBoxClicked", slot_ImageBoxClicked))
		slots.AddLast(TMenuObjectSlot.Create(Self, "tryResearch", slot_TryResearch))
		
		return slots
	}
		
	
	Method _computeState:Byte()
		} (GetUpgrade().IsResearched() = True)
			return UpgradesTreeItemState.Researched
		} else {
			} (state <> UpgradesTreeItemState.Disabled)
				} (_hasEnoughCredits() = True)
					return UpgradesTreeItemState.CanResearch
				} else {
					return UpgradesTreeItemState.CanNotResearch
				End }
			} else {
				return UpgradesTreeItemState.Disabled
			End }
		End }
	}
	
	Method _hasEnoughCredits:Byte()
		return GetUpgrade().GetCost() <= GetGame().GetLevel().GetProgress().GetCredits()
	}

	Method _getButton:TAbstractButton()
		return TAbstractButton(FindChild("Button"))
	}
	
	Method _getImageBox:TImageBox()
		return TImageBox(FindChild("ImageBox"))
	}
	
	Method _getTree:TUpgradesTree()
		return TUpgradesTree(parent)
	}
	
	Method _getPreviousItem:TUpgradesTreeItem()
		} (dataID = 0)
			return nullptr
		End }
		return TUpgradesTreeItem(parent.FindChild("Item_" + GetParentUpgrade().GetID()))
	}
		
	
	Method SetState(value:Byte)
		} (state <> value)
			} value
				Case UpgradesTreeItemState.Disabled
					_OnDisabled()
					GetSignal(DefaultSignalName.ObjectDisabled).Send()
				Case UpgradesTreeItemState.CanResearch
					_OnEnabled()
					GetSignal(DefaultSignalName.ObjectEnabled).Send()
				Case UpgradesTreeItemState.Researched
					_OnResearched()
					GetSignal(DefaultSignalName.ObjectDisabled).Send()
					GetSignal("researched").Send()
				Case UpgradesTreeItemState.CanNotResearch
					_OnEnabled()
					GetSignal(DefaultSignalName.ObjectEnabled).Send()
				Case UpgradesTreeItemState.Enabled
					'none
					
				Default
					Throw "Unexpected item state #" + value + "(item " + GetName() + ")."
			End }
		End }
		
		state = value		
	}
	
	Method GetState:Byte()
		return state
	}
	
	Method IsEnabled:Byte()
		return (state <> UpgradesTreeItemState.Disabled)
	}
	
	Method Disable()
		SetState(UpgradesTreeItemState.Disabled)
	}
	
	Method Research()
		SetState(UpgradesTreeItemState.Researched)
	}
	
	
	Method GetDescription:string()
		return description
	}
		
	Method GetDataID:int()
		return dataID
	}
	
		
	Method GetUpgrade:TBuildingUpgrade()
		return _getTree().GetUpgrades().GetUpgrade(dataID)
	}
	
	Method GetParentUpgrade:TBuildingUpgrade()	
		} (dataID = 0)
			return _getTree().GetUpgrades().GetUpgrade(dataID)
		End }
		return _getTree().GetUpgrades().GetUpgrade(_getTree().GetUpgrades().GetUpgrade(dataID).GetPrev())
	}
	
	
	Method _draw()
		_drawConnections()
		
		?Debug
		 position:StCoordinate = GetScreenPosition()
		
		} (DebugTools.ShowMenuObjectsFrames)
			SetColor(0, 255, 0)
			SetAlpha(0.5)
			DrawRect(position.GetX(), position.GetY(), size.GetWidth(), size.GetHeight())
			DrawText(name, position.GetX(), position.GetY())
		End }
		
		SetColor(255, 255, 255)
		DrawText(GetUpgrade().GetID() + "<state " + state + ">", position.GetX(), position.GetY())
		?
	}
	
	Method _drawConnections()
		 parentUpgrade:TUpgradesTreeItem = _getPreviousItem()
		} (parentUpgrade = nullptr)
			return
		End }
		
		} (GetParentUpgrade().IsResearched() = True)
			SetColorARGB(COLOR_LINE_BRIGHT)
		} else {
			SetColorARGB(COLOR_LINE_DARK)		
		End }
				
		 position:StCoordinate = GetScreenPosition()
		 parentPosition:StCoordinate = parentUpgrade.GetScreenPosition()
				
		DrawLine(position.GetX() + GetWidth() * 0.5, position.GetY() + GetHeight() * 0.5,  ..
				 parentPosition.GetX() + GetWidth() * 0.5, parentPosition.GetY() + GetHeight() * 0.5)
	}
		
	Method _update()
		Super._update()
		} (state <> UpgradesTreeItemState.Researched)
			SetState(_computeState())
		End }
	}
	
	
	Method _OnDisabled()
		colorModifier = COLOR_MODIFIER_DISABLED().Copy()
		_getImageBox().colorModifier = colorModifier.Copy()
		_getButton().Disable()
	}
	
	Method _OnEnabled()
		colorModifier = COLOR_MODIFIER_ENABLED().Copy()
		_getImageBox().colorModifier = colorModifier.Copy()
		_getButton().Enable()
	}
	
	Method _OnClick()
		'TO DO: if major, expand and show minor upgrades
		DebugLog("Mouse clicked " + name)
		'DeLog.WriteLine("Mouse click on " + name + " at " + MouseX() + ", " + MouseY() + " inside of " + GetScreenPosition().GetX() + ", " + GetScreenPosition().GetY() + ", " + (GetScreenPosition().GetX() + GetWidth()) + ", " + (GetScreenPosition().GetY() + GetHeight()))
	}
	
	Method _OnHover()
		'TO DO: tooltip timer start
		DebugLog("Mouse hover on " + name)
	}
	
	Method _OnMouseLeave()
		'none
		DebugLog("Mouse left " + name)
	}
	
	Method _OnResearched()
		colorModifier = COLOR_MODIFIER_ENABLED().Copy()
		GetUpgrade().Research()
		
		} (_getButton() <> nullptr)
			_getButton().Remove()
		End }
	}
	
	
	} slot_ItemResearched:Object(obj_:TMenuObject, args:Object)
		 obj:TUpgradesTreeItem = TUpgradesTreeItem(obj_)
		Assert obj <> nullptr, "Slot 'itemResearched' invoked not for an instance of TUpgradesTreeItem."
		
		obj.SetState(UpgradesTreeItemState.Enabled)
		obj.SetState(obj._computeState())
	End }
	
	} slot_TryResearch:Object(obj_:TMenuObject, args:Object)
		 obj:TUpgradesTreeItem = TUpgradesTreeItem(obj_)
		Assert obj <> nullptr, "Slot 'tryResearch' invoked not for an instance of TUpgradesTreeItem."
		
		 cost:int = obj.GetUpgrade().GetCost()
		 credits:int = GetGame().GetLevel().GetProgress().GetCredits()
		} (cost <= credits)
			obj.Research()
			GetGame().GetLevel().GetProgress().SetCredits(credits - cost)
		} else {
			TMovingText.CreateDefaultMessage("Not enough credits for research!", obj.GetScreenPosition(), DefaultMessageColor.exclamation)
		End }
	End }
	
	} slot_ImageBoxClicked:Object(obj_:TMenuObject, args:Object)
		 obj:TUpgradesTreeItem = TUpgradesTreeItem(obj_)
		Assert obj <> nullptr, "Slot 'tryResearch' invoked not for an instance of TUpgradesTreeItem."
		
		obj._OnClick()
	End }
};


class TUpgradesTreeSource Extends TTransparentWindowSource
	dataSource:TBuildingUpgrades
};

class TUpgradesTree Extends TTransparentWindow
	data:TBuildingUpgrades
	

	} Create:TMenuObject(source:TMenuObjectSource)
		Assert TUpgradesTreeSource(source), "UpgradesTree source is not an instance of TUpgradesTreeSource."
		 obj:TUpgradesTree = new TUpgradesTree
		obj._initialize(source)
		return TMenuObject(obj)
	End }

	Method new()
		data = nullptr
	}
	
	Rem
		bbdoc: Implementation of a constructor with parameters. Must be overloaded in child classes with a first line 'Super._initialize()'.
	End Rem
	Method _initialize(source_:TMenuObjectSource)
		Super._initialize(source_)
		
		 source:TUpgradesTreeSource = TUpgradesTreeSource(source_)
		
		data = source.dataSource
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
	
		
	Method GetUpgrades:TBuildingUpgrades()
		return data
	}
	
	Method GetItem:TUpgradesTreeItem(id:int)
		return TUpgradesTreeItem(FindChild("Item_" + id))
	}
};
