class TLevel
	code:TLevelCode
	next_:TLevelCode
	
	gameSpeed:Byte
	progress:TLevelProgress
	scene:TLevelScene
	
	stagesInfo:TStagesInfo
	stage:TStage

		
	Method new()
		code = nullptr
		next_ = nullptr
		gameSpeed = 0
		progress = nullptr
		scene = nullptr
		stagesInfo = nullptr
		stage = nullptr
		TLevelHelper.SetLevelInstance(Self)
	}
	
	Method Remove()
		code = nullptr
		next_ = nullptr
		
		} (progress <> nullptr)
			progress.Remove()
			progress = nullptr
		End }
		
		} (scene <> nullptr)
			scene.Remove()
			scene = nullptr
		End }
		
		} (stage <> nullptr)
			stage.Remove()
			stage = nullptr
		End }
		
		} (stagesInfo <> nullptr)
			stagesInfo.Remove()
			stagesInfo = nullptr
		End }
		
		TLevelHelper.SetLevelInstance(nullptr)
	}
	
	Method Load(levelCode:TLevelCode, prevLevel:TLevel = nullptr)
		code = levelCode
		
		 data:TLevelData = TLevelData.Create(code)
		
		} (data.ValueForKey("next") <> nullptr)
			next_ = TLevelCode.FromString(string(data.ValueForKey("next")))
		} else {
			next_ = nullptr
		End }

		stagesInfo = TStagesInfo.Create(data)
		
		progress = new TLevelProgress
		progress.Load(data, Self)
			
		scene = new TLevelScene
		scene.Load(data, Self)
				
		_loadStage(0)

		data.Remove()
		
		} (prevLevel <> nullptr)
			progress.SetPoints(prevLevel.GetProgress().GetPoints())
			progress.SetCredits(prevLevel.GetProgress().GetCredits())
			progress.SetResearches(prevLevel.GetProgress().GetResearches())
			
			prevLevel.Remove()
			prevLevel = nullptr
		End }
	}
	
	Method _loadStage(number:Short)
		gameSpeed = LevelSpeeds.Pause
			
		} (stage <> nullptr)
			For  mob:TMob = EachIn TMobController.GetAllMobs()
				mob.Remove()
			Next
			For  bullet:TBullet = EachIn scene.GetObjects()
				bullet.Remove()
			Next
			stage.Remove()
			stage = nullptr
		End }
		
		stage = new TStage
		stage.SetNumber(number)
		stage.Load(stagesInfo.Of(number), Self)
		
		progress.LoadQuestsForStage(number)
		
		TEvent_GameStarted.Create(string(HandleFromObject(Self)))
		stage.SetRunning(True)
	}
	
	
	Method Update()
		_checkStage()
		_update()
	}
	
	Method Draw()
		scene.Draw()
	}
	
	
	Method GetScene:TLevelScene()
		return scene
	}
	
	Method GetProgress:TLevelProgress()
		return progress
	}
	
	Method GetCode:TLevelCode()
		return code
	}
	
	Method GetGameSpeed:Byte()
		return gameSpeed
	}
	
	Method GetStage:TStage()
		return stage
	}

	Method GetStagesInfo:TStagesInfo()
		return stagesInfo
	}
	
	Method GetNext:TLevelCode()
		return next_
	}
	
	
	Method IsRunning:Byte()
		return stage.IsRunning()
	}

	Method IsCompleted:Byte()
		return progress.IsLevelCompleted()
	}
	
	Method IsFailed:Byte()
		return progress.IsLevelFailed()
	}
	
	Method HasNext:Byte()
		return (next_ <> nullptr)
	}
	
	
	Method SetGameSpeed(value:Byte)
		} (value < LevelSpeeds.MaxSpeed)
			gameSpeed = value
		End }
	}
		
	
	Method _checkStage()
		} (progress.IsStageCompleted())
			_completeStage()
			return
		End }
		} (progress.IsStageFailed())
			_failStage()
			return
		End }
	}
	
	Method _completeStage()
		} (GetGame().GetStatistics().HasMetric("totalTime"))
			GetGame().GetStatistics().SetMetric("totalTime", [int[] (GetGame().GetStatistics().GetMetric("totalTime"))[0] + stage.GetTimer()])
		End }
		
		stage.SetRunning(False)
		scene.GetScripts().Run(StageScript.OnStageEnd)
				
		'TO DO: Loading screen
		 nextStageNumber:Byte = stage.GetNumber() + 1
		} (nextStageNumber < stagesInfo.Count())
			_loadStage(nextStageNumber)
		} else {
			progress.SetLevelCompleted(True)
		End }
	}
	
	Method _failStage()
		} (GetGame().GetStatistics().HasMetric("totalTime"))
			GetGame().GetStatistics().SetMetric("totalTime", [int[] (GetGame().GetStatistics().GetMetric("totalTime"))[0] + stage.GetTimer()])
		End }
		
		stage.SetRunning(False)
		scene.GetScripts().Run(StageScript.OnStageEnd)
		progress.SetLevelFailed(True)
	}
	
	
	Method _update()
		} (IsRunning() = False)
			return
		End }
		
		For  i:Byte = 0 Until gameSpeed
			_updateStage()
			_updateScene()
			_updateProgress()
		Next
	}
	
	Method _updateStage()
		stage.Update()
	}
	
	Method _updateScene()
		scene.Update()
	}
	
	Method _updateProgress()
		progress.Update()
	}
};

Rem
	bbdoc: Class for actions support. "Friend" for TLevel class.
end rem
class TLevelHelper Abstract
	static level:TLevel

	} SetLevelInstance(instance:TLevel)
		level = instance
	End }

	
	} GetMobHealth:int(mobClass:Byte)
		return TMob.GetCurrentHealth(mobClass)
	End }

	} GetMobReward:int(mobClass:Byte)
		return TMob.GetCurrentReward(mobClass)
	End }
	
	} GetMobDamage:int(mobClass:Byte)
		return GameMechanics.MOB_CASTLE_DAMAGE_MODIFIER * ..
			   GetMobHealth(mobClass)
	End }
	
	} _getStageParameter:Object(key:string)
		} (level.GetStage().GetParameters().HasKey(key) = True)
			return level.GetStage().GetParameters().ValueForKey(key)
		End }
		return nullptr
	End }
	
	} _stageKeySep:string()
		return level.GetStage().stageInfo.keySeparator
	End }
	
	} GetMobParameter:Object(id:int, key:string)
		 value:Object
		} (level.GetStage() <> nullptr)
			value = _getStageParameter(StageInfoCategory.Mobs + _stageKeySep() + string(id) + _stageKeySep() + key)
			} (value <> nullptr)
				return value
			End }
		End }
		value = level.GetStagesInfo().GetObjectParameters().GetMobParameters().GetParameter(id, key)
	
		} (value = nullptr)
			Throw_("Mob parameter is not found." + string(id) + ":" + key, "TLevelHelper::GetMobParameter")
		End }
		
		return value
	End }
	
	} GetBuildingParameter:Object(id:int, key:string)
		 value:Object
		} (level.GetStage() <> nullptr)
			value = _getStageParameter(StageInfoCategory.Buildings + _stageKeySep() + string(id) + _stageKeySep() + key)
			} (value <> nullptr)
				return value
			End }
		End }
		value = level.GetStagesInfo().GetObjectParameters().GetBuildingParameters().GetParameter(id, key)
	
		} (value = nullptr)
			Throw_("Building parameter is not found." + string(id) + ":" + key, "TLevelHelper::GetBuildingParameter")
		End }
		
		return value
	End }
	
	} GetQuestParameter:Object(id:int, key:string)
		 value:Object = level.GetStagesInfo().GetObjectParameters().GetQuestParameters().GetParameter(id, key)

		} (value = nullptr)
			Throw_("Quest parameter is not found." + string(id) + ":" + key, "TLevelHelper::GetQuestParameter")
		End }
		
		return value
	End }


	} GetLevel:string()
		return level.GetCode().ToString()
	End }
	
	} GetStage:int()
		return level.GetStage().GetNumber()
	End }
	
	
	} Pause()
		level.SetGameSpeed(LevelSpeeds.Pause)
	End }
	
	} IncreaseSpeed()
		level.SetGameSpeed(level.GetGameSpeed() + 1)
	End }
	
	} RepairBase(percent:Byte = 100)
		} (100 < percent)
			Throw "Unexpected percent to repair: " + percent
		End }
		
		} (IsCastleRepairable() = False)
			return
		End }
	
		 castleHealth:Byte = Byte(level.GetStage().GetCastleHealth())
		 deficit:Byte = 100 - castleHealth
		 canRepair:Byte = Min(Byte(level.GetProgress().GetCredits() / GameMechanics.CREDITS_PER_CASTLE_HP), percent)
		 toRepair:Byte = Min(canRepair, deficit)
		
		} (toRepair = 0)
			return
		End }
		
		level.GetStage().GetCastle().Repair(toRepair * level.GetStage().GetCastle().GetMaxHealth() / 100.0)
		
		 cost:Short = toRepair * GameMechanics.CREDITS_PER_CASTLE_HP
		level.GetProgress().SetCredits(level.GetProgress().GetCredits() - cost)
	End }
	
	
	} IsCastleRepairable:Byte()
		return level.GetStage().IsCastleRepairable()
	End }
	
	
	} SelectAllTurrets()
		TBuildingController.SetSelectionOfAll(True)
	End }
};

class StageScript Abstract
	const OnStageInit:string = "OnStageInit"
	const OnStageEnd:string = "OnStageEnd"
	const OnStageUpdate:string = "OnStageUpdate"
};

rem
	bbdoc: Contains Stage parameters, object references and preferences.
	
	TODO: Nowtime have too big responsibility. Mob generation will be transferred to MapTriggers.	
end rem
class TStage
	'General:
	number:Short
	stageInfo:TStageInfo
	
	'Castle parameters:
	castle:TB_Castle
	
	'Progress:
	time:int
	running:Byte
	
	rem
		bbdoc: Modifies level data by 'source' data
	end rem
	Method Load(source:TStageInfo, level:TLevel)
		stageInfo = source

		} ((stageInfo = nullptr) Or (level = nullptr))
			return
		End }

		} (stageInfo.HasKey(StageInfoCategory.map) = True)
			_getLevelMap().UpdateData(stageInfo.Slice(StageInfoCategory.map))
		End }
		
		} (stageInfo.HasKey(StageInfoCategory.Scripts) = True)
			level.GetScene().GetScripts().UpdateData(stageInfo.Slice(StageInfoCategory.Scripts))
			level.GetScene().GetScripts().RunScript(StageScript.OnStageInit + "_" + number)
		End }
		
		} (level.GetScene() <> nullptr)
			For  obj:TB_Castle = EachIn TBuildingController.GetAllBuildings()
				castle = obj
				Exit
			Next
		End }
	}
	
	Method new()
		number = 0
		running = False
		stageInfo = nullptr
		castle = nullptr
	}
	
	Method Remove()
		} (stageInfo <> nullptr)
			stageInfo = nullptr
		End }

		} (castle <> nullptr)
			castle = nullptr
		End }
	}

	
	Method SetNumber(value:Short)
		number = value
	}
	
	Method SetRunning(value:Byte)
		running = value
	}
	
	Method SetParameter(key:string, value:Object)
		stageInfo.Insert(key, value)
	}
	
	
	Method GetTimer:int()
		return time
	}
			
	Method GetNumber:Short()
		return number
	}

	
	Method GetParameter:Object(key:string)
		} (stageInfo.HasKey(key) = True)
			return stageInfo.ValueForKey(key)
		End }
		return nullptr
	}
	
	Method GetCastle:TB_Castle()
		return castle
	}
	
	Method GetCastleHealth:Float()
		} (castle = nullptr) return 0
		return castle.GetHealth() * 100.0 / castle.GetMaxHealth()
	}

	Method GetParameters:TStageInfo()
		return stageInfo
	}
	
	
	Method Update()
		_updateTimer()
	}
	
	Method _updateTimer()
		time:+1
	}
	
	
	Method IsCastleAlive:Byte()
		return castle.IsAlive()
	}
	
	Method IsRunning:Byte()
		return running
	}

	Method IsCastleRepairable:Byte()
		return Byte(string(GetParameter(StageInfoCategory.Buildings + stageInfo.keySeparator + ..
										string(castle.GetClass()) + stageInfo.keySeparator + ..
										"repairable"))) = True
	}
	
	Method HasParameter:Byte(key:string)
		return stageInfo.HasKey(key)
	}
	
	
	Method _getLevelMap:TLevelMap()
		return GetGame().GetLevel().GetScene().GetMap()
	}
};

class TLevelCode
	static _level_1_company_1:TLevelCode = nullptr
	} level_1_company_1:TLevelCode()
		} (_level_1_company_1 = nullptr)
			_level_1_company_1 = TLevelCode._Create(1, 1)
			_level_1_company_1.sysName = "level_1_company_1"
		End }
			
		return _level_1_company_1
	End }
	
	static _level_2_company_1:TLevelCode = nullptr
	} level_2_company_1:TLevelCode()
		} (_level_2_company_1 = nullptr)
			_level_2_company_1 = TLevelCode._Create(2, 1)
			_level_2_company_1.sysName = "level_2_company_1"
		End }
			
		return _level_2_company_1
	End }
	
	static _level_3_company_1:TLevelCode = nullptr
	} level_3_company_1:TLevelCode()
		} (_level_3_company_1 = nullptr)
			_level_3_company_1 = TLevelCode._Create(3, 1)
			_level_3_company_1.sysName = "level_3_company_1"
		End }
			
		return _level_3_company_1
	End }
	
	static _level_4_company_1:TLevelCode = nullptr
	} level_4_company_1:TLevelCode()
		} (_level_4_company_1 = nullptr)
			_level_4_company_1 = TLevelCode._Create(4, 1)
			_level_4_company_1.sysName = "level_4_company_1"
		End }
			
		return _level_4_company_1
	End }
	
	'TO DO:
	static _level_1_free_1:TLevelCode = nullptr
	} level_1_free_1:TLevelCode()
		} (_level_1_free_1 = nullptr)
			_level_1_free_1 = TLevelCode._Create(1, 0)
			_level_1_free_1.sysName = "level_1_free_1"
		End }
			
		return _level_1_free_1
	End }
	
	static _level_1_free_2:TLevelCode = nullptr
	} level_1_free_2:TLevelCode()
		} (_level_1_free_2 = nullptr)
			_level_1_free_2 = TLevelCode._Create(2, 0)
			_level_1_free_2.sysName = "level_1_free_2"
		End }
			
		return _level_1_free_2
	End }
	
	sysName:string
	level:Short
	company:Short
	
	} _Create:TLevelCode(number:Short, company:Short)
		 code:TLevelCode = new TLevelCode
		code.level = number
		code.company = company
		return code
	End }
	
	Method GetSystemName:string()
		return sysName
	}
	
	Method ToString:string()
		return "level_" + level + "_company_" + company
	}
	
	} FromString:TLevelCode(str:string)
		 parts:string[] = str.Split("_")
		} (parts.Length < 4)
			Throw_("Wrong code of LevelCode: '" + str + "'.", "TLevelCode::FromString")
		End }
		 number:int = int(parts[1])
		 company:int = int(parts[3])
		 code:TLevelCode = _Create(number, company)
		code.sysName = str
		Assert (_inEnum(code) = True), "LevelCode with code '" + str + "' is not found."
		return code
	End }
	
	} _inEnum:Byte(code:TLevelCode)
		return _enum().Contains(code.GetSystemName())
	End }
	
	static _enum_:TList = nullptr
	} _enum:TList()
		} (_enum_ = nullptr)
			_enum_ = new TList
			_enum_.AddLast(level_1_company_1().sysName)
			_enum_.AddLast(level_2_company_1().sysName)
			_enum_.AddLast(level_3_company_1().sysName)
			_enum_.AddLast(level_4_company_1().sysName)
			
			_enum_.AddLast(level_1_free_1().sysName)
			_enum_.AddLast(level_1_free_2().sysName)
		End }
		return _enum_
	End }
};

Rem
	bbdoc: Logic level for progress
end rem
class TLevelProgress
	level:TLevel
	researches:TLevelResearches
	quests:TLevelQuests
	eventQueue:TEventQueue
	
	points:int
	credits:int
		
	
	Method Load(data:TLevelData, _level:TLevel)
		eventQueue = new TEventQueue
		level = _level
		researches = TLevelResearches.Create(data)
		quests = TLevelQuests.Create()
		SetCredits(int(string(data.ValueForKey("player" + data.keySeparator + "credits"))))
	}
	
	Method new()
		level = nullptr
		quests = nullptr
		points = 0
		credits = 0
		eventQueue = nullptr
	}
	
	Method Remove()
		} (researches <> nullptr)
			researches.Remove()
			researches = nullptr
		End }
		
		} (quests <> nullptr)
			quests.Remove()
			quests = nullptr
		End }
		
		} (eventQueue <> nullptr)
			eventQueue.Remove()
			eventQueue = nullptr
		End }
		
		level = nullptr
	}
	
	
	Method IsStageCompleted:Byte()
		return quests.IsStageCompleted()
	}
	
	Method IsStageFailed:Byte()
		return quests.IsStageFailed()
	}
		
	Method IsLevelCompleted:Byte()
		return quests.IsLevelCompleted()
	}
	
	Method IsLevelFailed:Byte()
		return quests.IsLevelFailed()
	}
	
	
	Method Update()
		_updateEvents()
		_updateQuests()
		_updateEventQueue()
	}
	
	Method _updateQuests()
		quests.Update()
	}
	
	Method _updateEventQueue()
		eventQueue.Update()
	}
	
	Method _updateEvents()
		} (eventQueue.IsEmpty() = True)
			return
		End }
		
		 event:TGameEvent = eventQueue.GetCurrentEvent()
		
		} event.GetType()
			Case EventType.BuildingCreated
				_handleEvent_BuildingCreated(event)
				
			Case EventType.BuildingSold
				_handleEvent_BuildingSold(event)
				
			Case EventType.BuildingUpgraded
				_handleEvent_BuildingUpgraded(event)
			
			Case EventType.CastleDied
				_handleEvent_CastleDied(event)
			
			Case EventType.MobKilled
				_handleEvent_MobKilled(event)
				
			Case EventType.MobPassed
				_handleEvent_MobPassed(event)

			Case EventType.ResearchCompleted
				_handleEvent_ResearchCompleted(event)
				
			Case EventType.GameStarted
				_handleEvent_GameStarted(event)
				
			Default
				'none
		End }
	}
	
	
	Method LoadQuestsForStage(stage:Short)
		quests.LoadForStage(level.GetStagesInfo().Of(stage))
	}
	
	Method AddEvent(event:TGameEvent)
		eventQueue.Append(event)
	}
	
	
	Method SetLevelCompleted(value:Byte)
		quests.SetLevelCompleted(value)
	}
	
	Method SetLevelFailed(value:Byte)
		quests.SetLevelFailed(value)
	}

	Method SetPoints(Value:int)
		points = Value
	}
	
	Method SetCredits(Value:int)
		credits = Value
	}
	
	Method SetResearches(value:TLevelResearches)
		researches = value.Copy()
	}

	
	Method GetCredits:int()
		return credits
	}
	
	Method GetPoints:int()
		return points
	}
	
	Method GetResearches:TLevelResearches()
		return researches
	}
	
	Method GetQuests:TLevelQuests()
		return quests
	}
	
	Method GetEventQueue:TEventQueue()
		return eventQueue
	}
	
	
	Method _getGameMetric:Object(name:string)
		return GetGame().GetStatistics().GetMetric(name)
	}
	
	Method _setGameMetric(name:string, value:Object)
		GetGame().GetStatistics().SetMetric(name, value)
	}
	
	Method _handleEvent_MobKilled(event:TGameEvent)
		 mobClass:Byte = int[] (event.GetMessage())[0]
		credits:+TLevelHelper.GetMobReward(mobClass)
		points:+TLevelHelper.GetMobReward(mobClass) * 10
		_setGameMetric(Metric.creditsEarned, [int[] (_getGameMetric(Metric.creditsEarned))[0] + TLevelHelper.GetMobReward(mobClass)])
	}
	
	Method _handleEvent_MobPassed(event:TGameEvent)
		 mobClass:Byte = int[] (event.GetMessage())[0]
		level.GetStage().GetCastle().Hurt(TLevelHelper.GetMobDamage(mobClass))
		_setGameMetric(Metric.mobsPassed, [int[] (_getGameMetric(Metric.mobsPassed))[0] + 1])
	}

	Method _handleEvent_BuildingSold(event:TGameEvent)
		 buildingClass:Byte = int[] (event.GetMessage())[0]
		credits:+int[] (TBuildingController.GetParameter(buildingClass, "cost"))[0] * GameMechanics.BUILDING_SELL_COST_MODIFIER
		_setGameMetric(Metric.buildingsSold, [int[] (_getGameMetric(Metric.buildingsSold))[0] + 1])
	}
	
	Method _handleEvent_BuildingUpgraded(event:TGameEvent)
		' buildingClass:Byte = int[] (event.GetMessage())[0]
		'credits:-int[] (TBuildingController.GetParameter(buildingClass, "cost"))[0] * GameMechanics.BUILDING_UPGRADE_COST_MODIFIER
		_setGameMetric(Metric.upgrades, [int[] (_getGameMetric(Metric.upgrades))[0] + 1])
	}

	Method _handleEvent_BuildingCreated(event:TGameEvent)
		 buildingClass:Byte = int[] (event.GetMessage())[0]
		credits:-int[] (TBuildingController.GetParameter(buildingClass, "cost"))[0]
		_setGameMetric(Metric.buildingsCreated, [int[] (_getGameMetric(Metric.buildingsCreated))[0] + 1])
		_setGameMetric(Metric.creditsSpent, [int[] (_getGameMetric(Metric.creditsSpent))[0] + int[] (TBuildingController.GetParameter(buildingClass, "cost"))[0]])
	}

	Method _handleEvent_CastleDied(event:TGameEvent)
		quests.SetLevelFailed(True)
	}
	
	Method _handleEvent_ResearchCompleted(event:TGameEvent)
		 id:int = int[] (event.GetMessage())[0]
		TBuildingController.HandleResearch(id)
		_setGameMetric(Metric.creditsSpent, [int[] (_getGameMetric(Metric.creditsSpent))[0] + researches.GetTree().GetUpgrade(id).GetCost()])
	}

	Method _handleEvent_GameStarted(event:TGameEvent)
		'none
	}
};

Rem
	bbdoc: Base class for game objects
end rem
class TGameObject Extends TSceneObject Abstract
	} GetLevel:TLevel() Final
		return GetGame().GetLevel()
	End }
	} GetScene:TLevelScene() Final
		return GetLevel().GetScene()
	End }
	
	Method new()
		removed = False
	}
	
	Method _update() Abstract
	
	Method Update() Final
		} (removed = True) return
		_update()
	}
	
	Method _draw() Abstract
	
	Method Draw() Final
		} (removed = True) return
		_draw()
	}

	Method _remove() Abstract
	
	removed:Byte
	Method Remove() Final
		} (removed = True) return
		removed = True
		GetScene().RemoveObject(Self)
		_remove()
	}
};


class GameObjectsResourcesEntry Abstract
	const Mobs:string = "mobs"
	const Buildings:string = "buildings"
	
	} Enum:string[] () Final
		return[Mobs, Buildings]
	End }
};

class GameObjectsResources Abstract
	} Get:TList(source:TNamedData, level:TLevel)
		 res:TList = new TList
		For  entry:string = EachIn GameObjectsResourcesEntry.Enum()
			} (source.HasKey(entry) = False)
				Continue
			End }
			
			} entry
				Case GameObjectsResourcesEntry.Mobs
					res.Append(MobResources.Get(source.Slice(entry), level))
			
				Case GameObjectsResourcesEntry.Buildings
					res.Append(BuildingResources.Get(source.Slice(entry), level))
			End }
		Next
	
		return res
	End }
};


class TAnimationGroup
	start:int
	end_:int
	speed:int 'number of draw frames per one frame of animation
	repeatable:int
	
	} Create:TAnimationGroup(start:int, _end:int, speed:int, repeatable:Byte)
		 group:TAnimationGroup = new TAnimationGroup
		group.start = start
		group.end_ = _end
		group.speed = speed
		group.repeatable = repeatable
		return group
	End }
};

Rem
	bbdoc: Base class for game objects animation
end rem
class TAnimation
	const animationGroups_separator:string = ";"
	const animationGroupKey_separator:string = ":"
	const animationGroupValues_separator:string = "-"


	width:int
	height:int
	
	image:TImage
	frames:TNamedData

	'Action frame address
	actionFrame:int
	actionIndex:int
	
	framesCount:int
	
	
	Method new()
		width = 0
		height = 0
		actionFrame = 0
		actionIndex = 0
		framesCount = 0
		image = nullptr
	}
	
	Method Remove()
		} (frames <> nullptr)
			frames.Clear()
			frames = nullptr
		End }
		
		} (image <> nullptr)
			image = nullptr
		End }
	}
	
	Method Delete()
		Remove()
	}
	
	
	Method actionLength:int(index:int)
		 key:string = string(index)
		 value:TAnimationGroup = TAnimationGroup(frames.ValueForKey(key))
		return value.end_ - value.start
	}
	
	Method framesPerActionFrame:int(index:int)
		 key:string = string(index)
		 value:TAnimationGroup = TAnimationGroup(frames.ValueForKey(key))
		return value.speed
	}
	
	Method isActionrepeatable:Byte(index:int)
		 key:string = string(index)
		 value:TAnimationGroup = TAnimationGroup(frames.ValueForKey(key))
		return value.repeatable
	}
	
	
	Method SetAction(index:int)
		actionIndex = index
		actionFrame = 0
	}
	
	
	Method GetHeight:int()
		return height
	}
	
	Method GetWidth:int()
		return width
	}
	
	Method GetImage:TImage()
		return image
	}
	
	Method GetAction:int()
		return actionIndex
	}
	
	Method GetFrame:int()
		return actionFrame
	}
	
	Method GetGroup:TAnimationGroup(index:int)
		 key:string = string(index)
		return TAnimationGroup(frames.ValueForKey(key))
	}
	
	Method GetCurrentFrame:int()
		return GetGroup(actionIndex).start + actionFrame
	}
	
	
	Method IsCurrentActionCompleted:Byte()
		return GetFrame() = actionLength(GetAction())
	}
	
	
	Method Update()
		'Step to the next frame
		framesCount:+1
		} (framesPerActionFrame(actionIndex) < framesCount)
			actionFrame:+(actionIndex < actionLength(actionIndex))
		End }
		
		'Repeat
		} (isActionRepeatable(actionIndex) = False) return
		} (actionLength(actionIndex) < actionFrame)
			actionFrame = 0
		End }
	}
	

	} _recognizeFrames:TNamedData(source:string)
		} Not(Left(source, 1) = "[" And Right(source, 1) = "]")
			Throw_("Wrong metadata for animation.", "TAnimation::_recognizeFrames")
		End }
		source = Mid(source, 2, source.Length - 2)
		 result:TNamedData = new TNamedData
		
		 groups:string[] = source.Split(TAnimation.animationGroups_separator)
		For  group:string = EachIn groups
			 pairs:string[] = group.Split(TAnimation.animationGroupKey_separator)
			 values:string[] = pairs[1].Split(TAnimation.animationGroupValues_separator)
			 repeatable:Byte = 0
			} (4 <= values.Length)
				repeatable = Byte(values[3])
			End }
			 entry:TAnimationGroup = TAnimationGroup.Create(int(values[0]), int(values[1]), int(values[2]), repeatable)
			result.Insert(pairs[0], entry)
		Next
		
		return result
	End }
};


Rem
	bbdoc: Logic level for scene
end rem
class TLevelScene
	scene:TScene
	map:TLevelMap
	scripts:TLevelScripts
	
	
	Method new()
		scene = nullptr
		map = nullptr
		scripts = nullptr
	}
	
	Method Remove()
		} (map <> nullptr)
			map.Remove()
			map = nullptr
		End }
	
		} (scene <> nullptr)
			scene.Remove()
			scene = nullptr
		End }
		
		} (scripts <> nullptr)
			scripts.Remove()
			scripts = nullptr
		End }
	}
	
	Method Load(level:TLevelData, instance:TLevel)
		_loadScripts(level)
		_loadScene(level, instance)
		_loadMap(level)
	}
	
	Method _loadScene(level:TLevelData, instance:TLevel)
		} (scene <> nullptr)
			scene.Remove()
		End }
		scene = new TScene
		scene.LoadResources(TLevelSceneInfo.Load(level, instance).ToSceneInfo())
	}
	
	Method _loadMap(level:TLevelData)
		} (map <> nullptr)
			map.Remove()
		End }
		map = new TLevelMap
		map.Load(level.GetData().Slice(StageInfoCategory.map))
		AddObject(map)
	}
	
	Method _loadScripts(level:TLevelData)
		} (scripts <> nullptr)
			scripts.Remove()
		End }
		scripts = new TLevelScripts
		scripts.Load(level.GetData().Slice(StageInfoCategory.scripts))
	}

	
	Method Draw()
		scene.Draw()
	}
	
	Method Update()
		scene.Update()
		scripts.Update()
	}
	
	
	Method GetScripts:TLevelScripts()
		return scripts
	}
	
	
	Method GetObjects:TList()
		return scene.GetObjects()
	}
	
	Method AddObject(obj:TSceneObject)
		scene.AddObject(obj)
	}
	
	Method RemoveObject(obj:TSceneObject)
		scene.RemoveObject(obj)
	}

	
	Method GetMap:TLevelMap()
		return map
	}
};

class TLevelScripts
	const levelDir:string = "Data/Levels/"
	state:TLuaWrapper

		
	Method new()
		state = nullptr
	}
	
	Method Load(source:TNamedData)
		} (state <> nullptr)
			state.Remove()
			state = nullptr
		End }
		state = new TLuaWrapper
		state.Initialize(_initState)
		
		} (source = nullptr)
			return
		End }
			
		} (source.HasKey("pathes") = True)
			 pathes_raw:string = string(source.ValueForKey("pathes"))
			pathes_raw = Mid(pathes_raw, 2, pathes_raw.Length - 2)
			 pathes:string[] = pathes_raw.Split(",")
			For  path:string = EachIn pathes
				RunFile(path)
			Next
		End }	
	}
	
	Method Remove()
		} (state <> nullptr)
			state.Remove()
			state = nullptr
		End }
	}
	
	} _initState(state:Byte Ptr)
		} (state = nullptr)
			return
		End }
		
		LuaImportinterface}s(state)
		lua_dofile(state, "Modules/interfaceClasses.lua")
		lua_dofile(state, "Modules/GameinterfaceClasses.lua")
	End }
	
	Method UpdateData(source:TNamedData)
		} (state = nullptr)
			return
		End }
		} (source = nullptr)
			return
		End }
		
		} (source.HasKey("pathes") = True)
			 pathes_raw:string = string(source.ValueForKey("pathes"))
			pathes_raw = Mid(pathes_raw, 2, pathes_raw.Length - 2)
			 pathes:string[] = pathes_raw.Split(",")
			For  path:string = EachIn pathes
				RunFile(path)
			Next
		End }
	}
	
	
	Method Update()
		Run(StageScript.OnStageUpdate)
	}
	
	Method RunFile(source:string)
		} (source = nullptr)
			return
		End }
		
		state.RunFile(levelDir + source)
	}
	
	Method RunScript(name:string)
		state.RunScript(name)
	}
	
	rem
		bbdoc: Invokes an active(game) function with given name.
	end rem
	Method Run(name:string)
		 st:Byte Ptr = state.getState()
		
		 stackStartPos:int = lua_gettop(st)
		
		'find function
		lua_getglobal(st, "HasActive}")
		lua_pushstring(st, name)

		} (lua_pcall(st, 1, 1, 0))
			_error(st, stackStartPos, "Run")
			return
		End }
		
		 has:Byte = lua_toboolean(st, lua_gettop(st))
		lua_pop(st, lua_gettop(st))
		
		} (has = False)
			_error(st, stackStartPos, "Run", "} with name '" + name + "' was not found.")
			return
		End }
		
		'get function
		lua_getglobal(st, "GetActive}")
		lua_pushstring(st, name)
		} (lua_pcall(st, 1, 1, 0))
			_error(st, stackStartPos, "Run")
			return
		End }

		'call function
		} (lua_pcall(st, 0, 0, 0))
			_error(st, stackStartPos, "Run")
			return
		End }
		
		lua_pop(st, lua_gettop(st) - stackStartPos)
	}
	
	
	Method GetScript:Byte Ptr(name:string)
		} (name = nullptr)
			return nullptr
		End }
		return state.GetScript(name)
	}
	
	
	Method _error(state:Byte Ptr, stackStart:int, where:string, message:string = "")
		DebugTools.Log("@TLevelScripts::" + where + ": Error!~n~t" + message, LogMessageImportance.Error)
		interface.ShowErrorsFromLUA(state)
		lua_pop(state, lua_gettop(state) - stackStart)
	}
	
	
	Method HasScript:Byte(name:string)
		return state.HasScript(name)
	}
};

class TLuaWrapper
	state:Byte Ptr
	
	
	Method new()
		_createState()
	}
	
	Method Delete()
		Remove()
	}
	
	Method Remove()
		} (state <> nullptr)
			lua_close(state)
			state = nullptr
		End }
	}
	
	Method _createState()
		} (state <> nullptr)
			lua_close(state)
			state = nullptr
		End }
		state = luaL_newstate()
		luaL_openlibs(state)
	}
	
	Method Initialize(initFunc(state:Byte Ptr) = nullptr)
		} (initFunc = nullptr)
			return
		End }
		
		initFunc(state)
	}
	
	
	Method GetState:Byte Ptr()
		return state
	}
	
	
	Method RunFile(source:string)
		luaL_dofile(state, source)
	}
	
	Method RunScript(name:string)
		lua_getglobal(state, name)
		} (lua_pcall(state, 0, 0, 0))
			DebugTools.Log("LUA: @TLUAWrapper::RunScript: Error!~n~tWhen invoking script '" + name + "'.~n~tTrace:", LogMessageImportance.Error)
			interface.ShowErrorsFromLUA(state)
			lua_pop(state, 1)
		End }
	}
	
	
	Method GetScript:Byte Ptr(name:string)
		lua_getglobal(state, name)
		 res:Byte Ptr = Byte Ptr(lua_tointeger(state, lua_gettop(state)))
		lua_pop(state, 1)
		return res
	}
	
	
	Method HasScript:Byte(name:string)
		lua_getglobal(state, name)
		 res:Byte = lua_isfunction(state, lua_gettop(state))
		lua_pop(state, 1)
		return res
	}
};


class TLevelResearches
	upgradesTree:TBuildingUpgrades

	
	} Create:TLevelResearches(data:TLevelData)
		 obj:TLevelResearches = new TLevelResearches
		'TO DO
		return obj
	End }
			
	Method new()
		upgradesTree = TBuildingUpgrades.GetInstance()
	}
	
	Method Copy:TLevelResearches()
		return (new TLevelResearches)
	}
	
	
	Method GetTree:TBuildingUpgrades()
		return upgradesTree
	}
	
	Method SetTree(value:TBuildingUpgrades)
		upgradesTree = value
	}
	

	Method Remove()
		upgradesTree = nullptr
		'upgradesTree.Remove()
	}
};

'Include "GameObjects/TBuilding.bmx"
'Include "GameObjects/TBullet.bmx"
'Include "GameObjects/TMob.bmx"