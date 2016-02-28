class BuildingAppearance Abstract
	const Ground:Byte = %1
	const Air:Byte = %10
};

class BuildStates Abstract
	const NotBuilt:Byte = False
	const Built:Byte = 1
	const Complete:Byte = 2
	const Removed:Byte = 3	
};

class BuildingClasses Abstract
	const Undefined:int = 0
	
	const Castle:int = -1	
	const Building:int = 1
	const Turret:int = 2
};

class BuildingClass Abstract
	const Castle:int = -1

	const Base:int = 1
	const Rocket:int = 2
	const Artillery:int = 3
	
	const Watchpost:int = 4
};

class BuildingAnimationGroup Abstract
	const undefined:int = 0
	
	const Normal:int = 1
	const Explode:int = 2
};


class BuildingResources Abstract
	} Get:TList(source:TNamedData, level:TLevel)
		 res:TList = new TList
		
		 raw_ids:string = string(source.ValueForKey("id"))
		raw_ids = Mid(raw_ids, 2, raw_ids.Length - 2)
		 ids:string[] = raw_ids.Split(",")
		
		For  id:string = EachIn ids
			 class:int = int(id)
			 raw_resources:string = string(level.GetStagesInfo().GetObjectParameters().GetBuildingParameters().GetParameter(class, "resources"))						
			res = res.Append(TList.FromArray(raw_resources.Split(";")))
		Next
		
		return res
	End }
};

class BuildingParameters Extends TNamedData
	const dataAddress:string = "Data/Buildings/BInfo.txt"
	
	
	Method new()
		_load()
	}

	Method _load()
		 stream:TStream = ReadFile(dataAddress)

		 lastClass:TNamedData = nullptr
		 lastClassId:string = 0
		
		While (Not stream.Eof())
			 str:string = stream.ReadLine()
			} (Left(str, 1) = "'") Continue
			
			} (Left(str, 1) <> "#")
				Continue
			End }
					
			lastClassId = str[1..]
			lastClass = new TNamedData
			lastClass.Insert("name", stream.ReadLine())

			lastClass.Insert("appearance", [Byte(stream.ReadLine())])
			lastClass.Insert("cost", [int(stream.ReadLine())])
			lastClass.Insert("majorUpgrade", [int(stream.ReadLine())])

			lastClass.Insert("description", stream.ReadLine())
			lastClass.Insert("resources", stream.ReadLine())
			
			 typeName:string = string(TBuildingRegistry.GetTypeNameForId(int(lastClassId)))
			Assert typeName <> nullptr, "Building type for id " + lastClassId + " is not found."
			lastClass.Insert("typeName", typeName)
			
			 _type:string = stream.ReadLine()
			} _type
				Case BuildingClasses.Turret
					lastClass.Insert("range", [Float(stream.ReadLine())])
					lastClass.Insert("cooldown", [int(stream.ReadLine())])
					lastClass.Insert("damage", [int(stream.ReadLine())])
					lastClass.Insert("maxAngle", [int(stream.ReadLine())])
				Case BuildingClasses.Castle
					lastClass.Insert("health", [int(stream.ReadLine())])
				Case BuildingClasses.Building
					'none
				Default
					Throw "Unexpected type of building (" + _type + ") at index " + lastClassId + "."
			End }

			data.Insert(lastClassId, lastClass)
		Wend
		
		stream.Close()
	}

	Method GetParameter:Object(class:int, key:string)
		return TNamedData(ValueForKey(string(class))).ValueForKey(key)
	}
	
	Method InsertParameter(class:int, key:string, value:Object)
		 classObj:TNamedData = TNamedData(ValueForKey(string(class)))
		} (classObj = nullptr)
			?Debug
			Throw_("Building class #" + class + " is not present on this level '" + GetGame().GetLevel().GetCode().ToString() + "'.", "BuildingParameters::InsertParameter")
			?
			return
		End }
		classObj.Insert(key, value)
	}
};

rem
	bbdoc: Static class that represents building classes in code.
end rem
class TBuildingRegistry
	static _instance_:TBuildingRegistry = nullptr
	} _instance:TBuildingRegistry()
		} (_instance_ = nullptr)
			_instance_ = new TBuildingRegistry

			_instance_._register(TB_Castle.GetClass(), "TB_Castle")
			_instance_._register(TB_Base.GetClass(), "TB_Base")
			_instance_._register(TB_Rocket.GetClass(), "TB_Rocket")
			_instance_._register(TB_Artillery.GetClass(), "TB_Artillery")
			_instance_._register(TB_Watchpost.GetClass(), "TB_Watchpost")
		End }
		return _instance_
	End }

	register_:TMap
	Method new()
		register_ = new TMap
	}
	
	Method _register(id:int, typeName:string)
		register_.Insert(string(id), typeName)
	}
	
	} IsIdRegistered:Byte(id:int)
		return _instance().register_.Contains(string(id))
	End }
	
	} IsTypeRegistered:Byte(typeName:string)
		 For  key:int[] = EachIn _instance().register_.Keys()
		 	} (_instance().register_.ValueForKey(key) = typeName)
				return True
			End }
		 Next
		 return False
	End }
	
	} GetTypeNameForId:string(id:int)
		return string(_instance().register_.ValueForKey(string(id)))
	End }
	
	} Register(id:int, typeName:string)
		_instance()._register(id, typename)
	End }
};


class TBuildingController Abstract
	} GetAllBuildings:TList()
		return GetGame().GetLevel().GetScene().GetObjects()
	End }
	
	} RemoveNonBuilt()
		For  b:TBuilding = EachIn GetAllBuildings()
			} (b.IsBuilt() = False) b.RejectBuilding()
		Next
	End }
	
	} SetSelectionOfAll(value:Byte)
		For  b:TTurret = EachIn GetAllBuildings()
			b.SetSelection(value)
		Next
	End }
	
	} IsAllPlaced:Byte()
		For  b:TBuilding = EachIn GetAllBuildings()
			} (b.IsBuilt() = False) return False
		Next
		return True
	End }

	} GetSelectedBuildings:TList()
		 selectedBuildings:TList = new TList
				
		For  b:TBuilding = EachIn GetAllBuildings()
			} (b.IsSelected() = True) selectedBuildings.AddLast(b)
		Next
		
		return selectedBuildings
	End }

	} GetUpgrades:TBuildingUpgrades()
		return TBuildingUpgrades.GetInstance()
	End }
	
	} IsTileTaken:Byte(tileX:Short, tileY:Short)
		For  b:TBuilding = EachIn GetAllBuildings()
			} (b.IsOnTile(tileX, tileY) = True)
				return True
			End }
		Next
		return False
	End }
	
	Rem
		bbdoc: x, y - относительные координаты центра. Проверка клетки. Если строение занимает больше одной клетки, будут проверены все клетки
	end rem
	} CanBuildThere:Byte(xPos:Float, yPos:Float, width:Short, height:Short)
		For  xChk:Short = Floor(xPos - (width * 0.5) / GameMechanics.TILE_SIZE) Until Ceil(xPos + (width * 0.5) / GameMechanics.TILE_SIZE)
			For  yChk:Short = Floor(yPos - (height * 0.5) / GameMechanics.TILE_SIZE) Until Ceil(yPos + (height * 0.5) / GameMechanics.TILE_SIZE)
				} (_isTileBuildable(xChk, yChk) = False)
					return False
				End }
				} (TMobController.IsAnyMobsOnTile(xChk, yChk, MobAppearance.Ground) = True)
					return False
				End }
				} (IsTileTaken(xChk, yChk) = True)
					return False
				End }
			Next
		Next
		return True
	End }
	
	} GetParameter:Object(class:int, key:string)
		return TLevelHelper.GetBuildingParameter(class, key)
	End }
	
	} GetResources:TSceneResources()
		return GetGame().GetLevel().GetScene().scene.resources
	End }
	
	} HandleResearch(id:int)
		 research:TBuildingUpgrade = TBuildingController.GetUpgrades().GetUpgrade(id)
		} (research.IsResearched() = False)
			return
		End }
		
		For  building:TBuilding = EachIn TBuildingController.GetAllBuildings()
			building.UpdateParameters()
		Next
	End }
	
	} IsBuildingResearched:Byte(classId:int)
		return GetParameter(classId, BuildingUpgradeModifier.Open) = "true"
	End }
	
	} _isTileBuildable:Byte(x:Short, y:Short)
		return GetGame().GetLevel().GetScene().GetMap().IsTileBuildable(x, y)
	End }
};

class TBuilding Extends TGameObject Abstract
	x:Float
	y:Float
	baseRotation:int
	
	animation:TBuildingAnimation
	
	buildState:Byte
	selected:Byte

	appearance:Byte
	
	
	Method new()
		baseRotation = 0
		buildState = BuildStates.NotBuilt
		selected = False
		x = 0
		y = 0
		appearance = MobAppearance.Undefined
	}
	
	Method Initialize()
		appearance = Byte[] (TBuildingController.GetParameter(GetClass(), "appearance"))[0]
		_loadAnimation()
		_loadSelection()
	}
	
	Method _loadAnimation() Abstract
	Method _loadSelection() Abstract
	
	Method _remove()
		} (IsPlaced() = True)
			buildState = BuildStates.removed
			TMobController.UpdatePathes()
		End }
		buildState = BuildStates.removed
		
		} (animation <> nullptr)
			animation.Remove()
			animation = nullptr
		End }
	}
	
	Method _update()
		} (IsBuilt() = True)
			_updateSelection()
			_updateBehaviour()
			_updateAnimation()		
		} else {
			_updateBuildState()
		End }
	}
	
	Method _draw()
		SetColorARGB($FFFFFFFF)
		SetRotation(baseRotation)
		DrawImage(animation.GetImage(), xAbs(), yAbs(), animation.GetCurrentFrame())
		SetRotation(0)	
	}
	
			
	Method SetPos(_x:Float, _y:Float)
		x = _x
		y = _y
	}

	Method SetZIndex(Value:Byte)
		'none
	}
	
	Method SetSelection(value:Byte)
		selected = value
	}
		
	
	} GetClass:int() Abstract
	
	Method GetZIndex:Byte()
		return GraphicsZIndexes.Buildings
	}

	Method GetUpgradeCost:int()
		return GetCost() * GameMechanics.BUILDING_UPGRADE_COST_MODIFIER
	}
	
	Method GetMajorUpgrade:int()
		return int[] (TBuildingController.GetParameter(GetClass(), "majorUpgrade"))[0]
	}

	Method GetAppearance:Byte()
		return appearance
	}
	
	Method GetWidth:int()
		return animation.GetWidth()
	}
	
	Method GetHeight:int()
		return animation.GetHeight()
	}
	
	Method GetCost:int()
		return int[] (TBuildingController.GetParameter(GetClass(), "cost"))[0]
	}

	Method xAbs:int()
		return x * GameMechanics.TILE_SIZE
	}
	
	Method yAbs:int()
		return y * GameMechanics.TILE_SIZE
	}
		
		
	Method Sell()
		TEvent_BuildingSold.Create(HandleFromObject(Self), [GetClass()])
		Remove()
	}
	
	Method RejectBuilding()
		Remove()
	}
	
	Method UpgradeTo(newClass:int)
		 upgrades:TBuildingUpgrades = TBuildingController.GetUpgrades()
		 upgrade:TBuildingUpgrade = upgrades.GetUpgrade(int[] (TBuildingController.GetParameter(newClass, "majorUpgrade"))[0])
		 isNewClassUpgrade:Byte = (upgrades.GetUpgrade(GetMajorUpgrade()) = ..
		                                upgrade.FindFirstPrevMajor())
		?Debug
		} (isNewClassUpgrade = False)
			Throw "Building #" + newClass + " does not upgrade building #" + GetClass() + "."
		End }
		?
										
		 progess:TLevelProgress = GetLevel().GetProgress()
		} (progess.GetCredits() < int[] (TBuildingController.GetParameter(newClass, "cost"))[0] * GameMechanics.BUILDING_UPGRADE_COST_MODIFIER)
			TMovingText.CreateDefaultMessage("Not enough credits for upgrading.", StCoordinate.Create(xAbs(), yAbs()))
			return
		End }
		
		} (TBuildingUpgrades.GetInstance().IsResearched(upgrade.GetID()) = False)
			TMovingText.CreateDefaultMessage("You need to recearh upgrade first.", StCoordinate.Create(xAbs(), yAbs()))
			return
		End }
		
		} (TBuildingUpgrades.GetInstance().FindClassForMajorUpgrade(upgrade.GetID()) = "")
			Throw "Buildng with major upgrade #" + upgrade.GetID() + " not found."
		End }
		
		 newTypeName:string = TBuildingUpgrades.GetInstance().FindTypeForMajorUpgrade(upgrade.GetID())
		 newBuilding:TBuilding = TBuilding(TTypeId.ForName(newTypeName).NewObject())

		newBuilding.Initialize()
		newBuilding.x = x
		newBuilding.y = y
		
		buildState = BuildStates.NotBuilt
		newBuilding._tryBuild()
		} (newBuilding.IsPlaced() = False)
			newBuilding.Remove()
			buildState = BuildStates.Complete
			return
		End }
		
		newBuilding.selected = True
		Remove()
		GetScene().AddObject(newBuilding)

		TEvent_BuildingUpgraded.Create(HandleFromObject(Self), [newBuilding.GetClass()])
	}
	
	Method Explode()
		animation.SetAction(BuildingAnimationGroup.Explode)
	}
	
	
	Method IsPlaced:Byte()
		return BuildStates.Built <= buildState
	}
	
	Method IsBuilt:Byte()
		return buildState = BuildStates.Complete
	}
	
	Method IsSelected:Byte()
		return selected
	}

	Method IsOnTile:Byte(tileX:Short, tileY:Short)
		} (IsPlaced() = False) return False

		 xA:int = (tileX + 0.5) * GameMechanics.TILE_SIZE
		 yA:int = (tileY + 0.5) * GameMechanics.TILE_SIZE

		 xMin:int = Floor(x - GetWidth() * 0.5 / GameMechanics.TILE_SIZE) * GameMechanics.TILE_SIZE + 1
		 xMax:int = Ceil(x + GetWidth() * 0.5 / GameMechanics.TILE_SIZE) * GameMechanics.TILE_SIZE - 1
		 yMin:int = Floor(y - GetHeight() * 0.5 / GameMechanics.TILE_SIZE) * GameMechanics.TILE_SIZE + 1
		 yMax:int = Ceil(y + GetHeight() * 0.5 / GameMechanics.TILE_SIZE) * GameMechanics.TILE_SIZE - 1
		return IsPointInRect(xA, yA, xMin, yMin, xMax, yMax)
	}

	
	Method _canBuildThere:Byte(x:Float, y:Float)
		return TBuildingController.CanBuildThere(x, y, GetWidth(), GetHeight())
	}
	
	
	Method _updateBuildState()
		} (MouseHit(MOUSE_RIGHT) = True)
			} (interface.MouseOverinterface() = False)
				RejectBuilding()
			End }
		} else {
			} (IsPlaced() = False)
				_selectPlace()
			} else {
				_selectRotation()
			End }
		End }
	}

	Method _updateBehaviour() Abstract
	
	Method _updateSelection()
		} (MouseDown(MOUSE_LEFT) = False)
			return
		End }	

		} (interface.MouseOverinterface() = True)
			return
		End }
		
		 xMin:int = Floor(x - GetWidth() * 0.5 / GameMechanics.TILE_SIZE) * GameMechanics.TILE_SIZE + 1
		 xMax:int = Ceil(x + GetWidth() * 0.5 / GameMechanics.TILE_SIZE) * GameMechanics.TILE_SIZE - 1
		 yMin:int = Floor(y - GetHeight() * 0.5 / GameMechanics.TILE_SIZE) * GameMechanics.TILE_SIZE + 1
		 yMax:int = Ceil(y + GetHeight() * 0.5 / GameMechanics.TILE_SIZE) * GameMechanics.TILE_SIZE - 1
		} (IsCursorInRect(xMin, xMax, yMin, yMax) = True)
			SetSelection(True)
		} else {
			SetSelection(False)
		End }
	}
	
	Method _updateAnimation()
		} animation.GetAction()
			Case BuildingAnimationGroup.Normal
				'none
			Case BuildingAnimationGroup.Explode
				} (animation.IsCurrentActionCompleted() = True)
					'TO DO: 
					Remove()
				End }
			Default
				Throw "Unexpected animation group of Building: " + animation.GetAction()
		End }
	
		animation.Update()
	}

	
	Method _tryBuild()
		} Not(GetCost() <= GetLevel().GetProgress().GetCredits())
			TMovingText.CreateDefaultMessage("Not enough credits, need " + GetCost(), StCoordinate.Create(xAbs(), yAbs()))
			return
		End }
		
		} (_canBuildThere(x, y) = False)
			TMovingText.CreateDefaultMessage("Not enough space.", StCoordinate.Create(xAbs(), yAbs()))
			return
		End }
		
		buildState = BuildStates.Built
		TMobController.UpdatePathes()
	}
	
	Method _selectPlace()
		x = int(MouseX() / GameMechanics.TILE_SIZE) + 0.5
		y = int(MouseY() / GameMechanics.TILE_SIZE) + 0.5
					
		} ((MouseHit(MOUSE_LEFT) = True) And (interface.MouseOverinterface() = False))
			_tryBuild()
		End }
		
		selected = True
	}
	
	Method _selectRotation()
		 angle:Float = ATan2(MouseY() - yAbs(), MouseX() - xAbs())
		} (angle < 0) angle = 360 + angle
		baseRotation = angle
		
		} ((MouseHit(MOUSE_LEFT) = False) Or (interface.MouseOverinterface() = True))
			return
		End }
		
		buildState = BuildStates.Complete
		
		TEvent_BuildingCreated.Create(HandleFromObject(Self), [GetClass()])
	}
	
	} _getCurrentEvent:TGameEvent() Final
		 queue:TEventQueue = GetGame().GetLevel().GetProgress().GetEventQueue()
		} (queue.IsEmpty() = False)
			return queue.GetCurrentEvent()
		} else {
			return nullptr
		End }
	End }
	
	Method UpdateParameters() Abstract
};

class TBuildingAnimation Extends TAnimation
	} Load:TBuildingAnimation(buildingClass:int)
		 obj:TBuildingAnimation = new TBuildingAnimation
	
		 resources:string[] = string(TBuildingController.GetParameter(buildingClass, "resources")).Split(";")
		For  resourceHash:string = EachIn resources
			} (resourceHash.StartsWith(TSceneResource.CLASS_IMAGE_SIGN) = False)
				Continue
			End }

			 resource:TSceneResource = TBuildingController.GetResources().GetResource(resourceHash)
			} (resource.GetClass() <> TSceneResource.CLASS_IMAGE)
				Throw "Wrong animation resource '" + resourceHash + "'."
			End }
			
			obj.image = TImage(resource.GetObject())
			obj.width = obj.image.width
			obj.height = obj.image.height
			obj.framesCount = obj.image.frames.Length
			obj.frames = _recognizeFrames(resource.GetMetadata())
			Exit
		Next
		
		return obj
	End }
};

class TBuildingSelection Extends TGameObject
	source:Object
	image:TImage
	xOffset:int
	yOffset:int
	
	const zoneColor:int = $998BFF32


	} Create:TBuildingSelection(source:Object)
		Assert TBuilding(source) <> nullptr, "Source is not TBuilding."
		 selection:TBuildingSelection = new TBuildingSelection
			selection.source = source
			
			 resources:string[] = string(TBuildingController.GetParameter(TBuilding(source).GetClass(), "resources")).Split(";")
			For  resource:string = EachIn resources
				} (resource.Contains("Sector") = True)
					selection.image = TImage(TBuildingController.GetResources().GetResource(resource).GetObject())
					Exit
				End }
			Next
			
		return selection
	End }
	
	Method _remove()
		source = nullptr
		image = nullptr
	}
				
	Method GetZIndex:Byte()
		return GraphicsZIndexes.BuildingEffects
	}

	Method SetZIndex(Value:Byte)
		'none
	}

	Method _update()
		} (source = nullptr)
			Remove()
			return
		End }
		} (TGameObject(source).removed)
			Remove()
			return
		End }
		} (TBuilding(source).buildState = BuildStates.Removed)
			Remove()
			return
		End }		
	}
	
	Method _draw()
		} (source = nullptr)
			return
		End }
		} (TBuilding(source).IsSelected() = False)
			return
		End }
		
		_drawSector()
	}
	
	Method _drawSector()
		 source:TBuilding = TBuilding(source)
			
		SetColorARGB($FFFFFFFF)
		SetRotation(source.baseRotation)
		DrawImage(image, source.xAbs() + xOffset, source.yAbs() + yOffset)
		SetRotation(0)
	}
};


class TTurret Extends TBuilding Abstract
	turretRotation:int
	turretMaxAngle:int
	
	shotTimer:int
	
	cooldown:int		'60 * sec.
	damage:int
	range:Float
	
	bulletAcceleration:Float
	bulletSize:Float
	
		
	Method new()
		shotTimer = 0
		turretRotation = 0
		cooldown = 0
		damage = 0
		range = 0
		bulletSize = 0
		bulletAcceleration = 0
	}
	
	Method Initialize()
		Super.Initialize()
		cooldown = int[] (TBuildingController.GetParameter(GetClass(), "cooldown"))[0]
		damage = int[] (TBuildingController.GetParameter(GetClass(), "damage"))[0]
		range = Float[] (TBuildingController.GetParameter(GetClass(), "range"))[0] * GameMechanics.TILE_SIZE
		turretMaxAngle = int[] (TBuildingController.GetParameter(GetClass(), "maxAngle"))[0]
		'bulletAcceleration = TBuildingController.GetParameter(GetClass(), "bulletAcceleration")
		'bulletSize = TBuildingController.GetParameter(GetClass(), "bulletSize")
	}
	
	Method _loadAnimation()
		animation = TTurretAnimation.Load(GetClass())
		Assert TTurretAnimation(animation) <> nullptr, "Loaded animation is not an instance of TTurretAnimation."
		animation.SetAction(BuildingAnimationGroup.Normal)
	}
	
	Method _loadSelection()
		GetScene().AddObject(TTurretSelection.Create(Self))
	}
	
	
	Method GetCooldown:int()
		return cooldown
	}

	Method GetDamage:Float()
		return damage
	}
	
	Method GetWidth:int()
		return animation.GetWidth()
	}
	
	Method GetHeight:int()
		return animation.GetHeight()
	}
	
	Method GetRange:Float()
		return range
	}
	
	
	Method IsCharged:Byte()
		return cooldown <= shotTimer
	}

	Method CanDamageMob:Byte(mob:TMob)
		} (mob = nullptr) return False
		
		} (mob.GetAppearance() And appearance)
			return True
		End }
		
		return False
	}
	
	
	Method _seekEnemies()
		 enemies:TList = _findEnemiesInRange()
		} (enemies.IsEmpty()) return
		
		 enemy:TMob = _selectEnemy(enemies)
		
		 neededRotation:int = ATan2(enemy.y - yAbs(), enemy.x - xAbs())
		} (neededRotation < 0) neededRotation = 360 + neededRotation
		_rotate(neededRotation)
		
		} (IsCharged() = True)
			} (turretRotation = neededRotation)
				_shot(enemy)
			End }
		End }
	}
	
	Method _selectEnemy:TMob(accessibleTargets:TList)
		accessibleTargets.Sort(True, TMob.CmpGetFastest)
		accessibleTargets.Sort(True, TMob.CmpGetClosest)
		accessibleTargets.Sort(True, TMob.CmpGetMostDamaged)
		return TMob(accessibleTargets.First())
	}
	
	Method _checkRotation() Abstract
	
	Method _rotate(toAngle:int = 361)
		} (toAngle <> 361)
			turretRotation = toAngle Mod 360
		End }
		_checkRotation()
	}
	
	Method _findEnemiesInRange:TList()
		 foundMobs:TList = new TList

		 xPos:Float = xAbs()
		 yPos:Float = yAbs()
		
		For  mob:TMob = EachIn TMobController.GetAllMobs()
			} (CanDamageMob(mob) = False)
				Continue
			End }
		
			 deltaX:Float = xPos - mob.x
			 deltaY:Float = yPos - mob.y
			} (range < Abs(deltaX)) Or (range < Abs(deltaY))
				Continue
			End }
						
			 distance:Float = deltaX ^ 2 + deltaY ^ 2
			
			} (distance <= range ^ 2) foundMobs.AddLast(mob)
		Next
		
		return foundMobs
	}
	
	Method _shot(target:TMob)
		GetScene().AddObject(TBullet.Create(xAbs(), yAbs(), GetDamage(), bulletAcceleration, target, bulletSize))
		shotTimer = 0
	}

	
	Method _updateBehaviour()
		shotTimer:+(shotTimer < cooldown)
		_seekEnemies()
	}

	
	Method _draw()
		SetColorARGB($FFFFFFFF)
		SetRotation(baseRotation)
		DrawImage(animation.GetImage(), xAbs(), yAbs())

		} (animation.GetImage().frames.Length = 2) ' turret
			SetRotation(turretRotation)
			DrawImage(animation.GetImage(), xAbs(), yAbs(), 1)
		End }
		SetRotation(0)
	}
	
		
	Method _selectRotation()
		 angle:Float = ATan2(MouseY() - yAbs(), MouseX() - xAbs())
		} (angle < 0) angle = 360 + angle
		baseRotation = angle
		turretRotation = angle
		
		} (MouseHit(MOUSE_LEFT) = False)
			return
		End }
		
		buildState = BuildStates.Complete
		
		TEvent_BuildingCreated.Create(HandleFromObject(Self), [GetClass()])		
	}
	
	Method UpdateParameters()
		cooldown = int[] (TBuildingController.GetParameter(GetClass(), "cooldown"))[0]
		damage = int[] (TBuildingController.GetParameter(GetClass(), "damage"))[0]
		range = Float[] (TBuildingController.GetParameter(GetClass(), "range"))[0] * GameMechanics.TILE_SIZE
		turretMaxAngle = int[] (TBuildingController.GetParameter(GetClass(), "maxAngle"))[0]
		'bulletAcceleration = TBuildingController.GetParameter(GetClass(), "bulletAcceleration")
		'bulletSize = TBuildingController.GetParameter(GetClass(), "bulletSize")		
	}
};

class TTurretAnimation Extends TBuildingAnimation
	} Load:TBuildingAnimation(buildingClass:int)
		 obj:TTurretAnimation = new TTurretAnimation
	
		 resources:string[] = string(TBuildingController.GetParameter(buildingClass, "resources")).Split(";")
		For  resourceHash:string = EachIn resources
			} (resourceHash.StartsWith(TSceneResource.CLASS_IMAGE_SIGN) = False)
				Continue
			End }

			 resource:TSceneResource = TBuildingController.GetResources().GetResource(resourceHash)
			} (resource.GetClass() <> TSceneResource.CLASS_IMAGE)
				Throw "Wrong animation resource '" + resourceHash + "'."
			End }
			
			obj.image = TImage(resource.GetObject())
			obj.width = obj.image.width
			obj.height = obj.image.height
			obj.framesCount = obj.image.frames.Length
			obj.frames = _recognizeFrames(resource.GetMetadata())
			Exit
		Next
		
		return TBuildingAnimation(obj)
	End }
};

class TTurretSelection Extends TBuildingSelection
	} Create:TBuildingSelection(source:Object)
		Assert TTurret(source) <> nullptr, "Source is not TTurret."
		 selection:TTurretSelection = new TTurretSelection
			selection.source = source
			
			 resources:string[] = string(TBuildingController.GetParameter(TBuilding(source).GetClass(), "resources")).Split(";")
			For  resource:string = EachIn resources
				} (resource.Contains("Sector") = True)
					selection.image = TImage(TBuildingController.GetResources().GetResource(resource).GetObject())
					Exit
				End }
			Next
			
		return TBuildingSelection(selection)
	End }

	Method _draw()
		} (source = nullptr) return
		} (TGameObject(source).removed = True) return
		} (TBuilding(source).IsSelected() = False) return
			
		Super._draw()
		_drawCooldownBar()
	}

	Method _drawCooldownBar()
		 source:TTurret = TTurret(source)
		
		SetColorARGB($30000000)
		DrawRect(source.xAbs() - 8, source.yAbs() + source.GetHeight() * 0.5, 16, 5)
		
		SetColorARGB($8FFFCC00)
		 reloadingPercent:Float = Min(Float(source.shotTimer) / source.cooldown, 1)
		DrawRect(source.xAbs() - 7, source.yAbs() + source.GetHeight() * 0.5 + 1, 14 * reloadingPercent, 3)
	}
};

'Include "Buildings.bmx"