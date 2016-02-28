class QuestImportance Abstract
	const undefined:Byte = 0
	const Usual:Byte = 1	
	const Main:Byte = 2

	} Enum:Byte[] () Final
		return[Usual, Main]
	End }
};

class QuestState Abstract
	const Normal:Byte = 0
	const Completed:Byte = 1
	const Failed:Byte = 2
	
	} Enum:Byte[] () Final
		return[Normal, Completed, Failed]
	End }
};

Rem
	bbdoc: Data level for quests
end rem
class TLevelQuest
	id:int
	tasks:TQuestTasks
	reward:TQuestRewards
	active:Byte
	importance:Byte
	
	
	} Create:TLevelQuest(id:int)
		 obj:TLevelQuest = new TLevelQuest
		obj.id = id
		obj.active = False
		
		 raw_taskID:string = string(TLevelQuestController.GetParameter(id, "tasks"))
		raw_taskID = Mid(raw_taskID, 2, raw_taskID.Length - 2)
		 raw_taskIDs:string[] = raw_taskID.Split(",")
		 taskIDs:int[] = new int[raw_taskIDs.Length]
		For  i:int = 0 Until raw_taskIDs.length
			taskIDs[i] = int(raw_taskIDs[i])
		Next
				
		 raw_rewardID:string = string(TLevelQuestController.GetParameter(id, "rewards"))
		raw_rewardID = Mid(raw_rewardID, 2, raw_rewardID.Length - 2)
		 raw_rewardIDs:string[] = raw_rewardID.Split(",")
		 rewardIDs:int[] = new int[raw_rewardIDs.Length]
		For  i:int = 0 Until raw_rewardIDs.length
			rewardIDs[i] = int(raw_rewardIDs[i])
		Next
	
		obj.tasks = TQuestTasks.Create(taskIDs)
		obj.reward = TQuestRewards.Create(rewardIDs)
		return obj
	End }
	
	
	Method new()
		tasks = nullptr
		id = 0
		reward = nullptr
		active = False
		importance = QuestImportance.undefined
	}
	
	Method Remove()
		} (tasks <> nullptr)
			tasks.Remove()
			tasks = nullptr
		End }
		
		} (reward <> nullptr)
			reward.Remove()
			reward = nullptr
		End }
	}
	
	
	Method IsCompleted:Byte()
		return tasks.IsCompleted()
	}
	
	Method IsFailed:Byte()
		return tasks.IsFailed()
	}
	
	Method IsActive:Byte()
		return active
	}
	
	
	Method SetCompleted(value:Byte)
		tasks.SetCompleted(value)
	}
	
	Method SetFailed(value:Byte)
		tasks.SetFailed(value)
	}
	
	Method SetActive(value:Byte)
		active = value
	}
	
	Method SetImportance(value:Byte)
		importance = value
	}
	
	
	Method GetProgress:TQuestTask[] ()
		return tasks.GetProgress()
	}
	
	Method GetID:int()
		return id
	}
	
	Method GetDescription:string()
		return string(TLevelQuestController.GetParameter(GetID(), "description"))
	}
	
	Method GetName:string()
		return string(TLevelQuestController.GetParameter(GetID(), "name"))
	}
	
	Method GetRewardDescription:string()
		return reward.GetDescription()
	}
	
	Method GetImportance:Byte()
		return importance
	}
	
	
	Method Update()
		} (IsActive() = False)
			return
		End }
		
		tasks.Update()
		} (tasks.IsCompleted() = True)
			reward.Grant()
			SetActive(False)
		End }
	}
};


class QuestRewardType Abstract
	const undefined:Byte = 0
	
	const _min:Byte = 1
	
	const level:Byte = 1
	const stage:Byte = 2
	
	const mob_count_increase:Byte = 3
	const mob_health_decrease:Byte = 4
	const mob_speed_decrease:Byte = 5
	const mob_reward_inclrease:Byte = 6
	
	const credits_increase:Byte = 7
	
	const buildings_grant:Byte = 8
	const buildings_cost_decrease:Byte = 9
	
	const researces_open:Byte = 10
	const researces_grant:Byte = 11
	
	const _max:Byte = 11
};

class TQuestRewards
	const descriptionSeparator:string = ";"


	rewards:TQuestReward[]
	

	} Create:TQuestRewards(ids:int[])
		 obj:TQuestRewards = new TQuestRewards
		obj.rewards = new TQuestReward[ids.length]
		For  i:int = 0 Until ids.length
			obj.rewards[i] = TQuestReward.Create(ids[i])
		Next
		return obj
	End }
	
	Method new()
		rewards = nullptr
	}
	
	Method Remove()
		} (rewards <> nullptr)
			rewards = nullptr
		End }
	}
	
	
	Method GetDescription:string()
		 res:string = ""
		For  reward:TQuestReward = EachIn rewards
			res:+reward.GetDescription() + descriptionSeparator
		Next
		return res[0..res.length - 1]
	}


	Method Grant()
		For  reward:TQuestReward = EachIn rewards
			reward.Grant()
		Next
	}
};

class TQuestReward
	id:int
	typeID:int
	
	
	} Create:TQuestReward(id:int)
		 obj:TQuestReward = new TQuestReward
		obj.id = id
		obj.typeID = int(string(TLevelQuestController.GetRewards().GetParameter(id, "type")))
		return obj
	End }
	
	Method new()
		id = 0
		typeID = 0
	}
	
	
	Method GetID:int()
		return id
	}
	
	Method GetTypeID:int()
		return typeID
	}
	
	Method GetDescription:string()
		return string(TLevelQuestController.GetRewards().GetParameter(GetID(), "description"))
	}
	
	Method _getArgs:Object[] ()
		 raw_args:string = string(TLevelQuestController.GetRewards().GetParameter(GetID(), "reward"))
		raw_args = Mid(raw_args, 2, raw_args.Length - 2)
		return raw_args.Split(",")
	}

	
	Method Grant()
		TQuestReward_Impl.Invoke(GetTypeID(), Self)
	}
};


class TQuestTriggers
	triggers:TList


	} Create:TQuestTriggers(ids:int[])
		 obj:TQuestTriggers = new TQuestTriggers
		obj.triggers = new TList
		For  id:int = EachIn ids
			 classId:int = int(string(_getTriggerParameters().GetParameter(id, "classId")))
			 args:string = string(_getTriggerParameters().GetParameter(id, "args"))
			obj.triggers.AddFirst(_getFactory().Create2(classId, args))
		Next
		return obj
	End }

	Method new()
		triggers = nullptr
	}
	
	Method Remove()
		} (triggers <> nullptr)
			triggers.Clear()
			triggers = nullptr
		End }
	}
	
	
	} _getFactory:TQuestTriggerFactory() Final
		return _getTriggerParameters().GetFactory()
	End }
	
	} _getTriggerParameters:QuestTriggerParameters()
		return TLevelQuestController.GetTasks().GetTriggers()
	End }
	
	
	Method Update()
		For  trigger:TQuestTrigger = EachIn triggers
			trigger.Update()
		Next
	}
};

class TQuestTrigger Extends TLevelTrigger Abstract
	Method Initialize(args:Object[]) Abstract
	rem
		bbdoc: Construct from string args representation.
	end rem
	Method Initialize2(args:string) Abstract
	
	Method Update() Abstract
	Method Remove() Abstract
};

class TQuestTrigger_MobSpawn Extends TQuestTrigger
	const EVENT_TAG_MOB_SPAWNED:string = "MobSpawned"
	
	timer:int
	pathId:int
	sequence:TMobSequence


	} Create:TQuestTrigger_MobSpawn(sequence:TMobSequence, pathId:int)
		 obj:TQuestTrigger_MobSpawn = new TQuestTrigger_MobSpawn
		obj.pathId = pathId
		obj.sequence = sequence
		return obj
	End }
	
	Method Initialize(args:Object[])
		} (args = nullptr)
			return
		End }
		} (args.Length <> 2)
			return
		End }

		sequence = TMobSequence(args[0])
		pathId = int[] (args[1])[0]
	}
	
	Method Initialize2(args:string)
		} (args = nullptr)
			return
		End }
		
		 stream:TStream = TStringStream.Create(args)
		 data:TNamedData = TNamedData.Parse(stream)
		stream.Close()
		stream = nullptr
		
		sequence = new TMobSequence
		sequence.Load(data.Slice("sequence"))

		pathId = int(string(data.ValueForKey("pathId")))
	}
	
	
	} _getMobDelay:int(position:int, sequence:TMobSequence)
		return sequence.GetDelay() * FPS.Normalized() * FPS.defaultValue
	End }
	} _getMobFactory:TMobFactory() Final
		return TMobController.GetMobFactory()
	End }
	} _getScene:TLevelScene()
		return GetGame().GetLevel().GetScene()
	End }
	
	
	Method GetTimer:int()
		return timer
	}
	
	Method SetTimer(value:int)
		timer = value
	}


	Method GetPathId:int()
		return pathId
	}
	
	Method SetPathId(value:int)
		pathId = value
	}
	
	Method SetSequence(value:TMobSequence)
		sequence = value
	}
	
	
	Method new()
		timer = 0
		sequence = nullptr
		pathId = -1
		
		'AddEventHandler(EventType.TimerTick, ...)
		_registerEvent(EVENT_TAG_MOB_SPAWNED)
	}
	
	Method Delete()
		Remove()
	}
	Method Remove()
		} (sequence <> nullptr)
			sequence = nullptr
		End }
	}
	
	Method Update()
		} (sequence.IsCompleted() = False)
			timer:+1
			} (_getMobDelay(-1, sequence) < timer)
				 id:int = sequence.MakeStep()
				TEvent_MobTimerCompleted.Create(HandleFromObject(Self), [id, pathId])
				_getScene().AddObject(_getMobFactory().Create(id, pathId))
				TEvent_TriggerEvent.Create2(EventType.GetTagId(EVENT_TAG_MOB_SPAWNED), HandleFromObject(Self))
				timer = 0
			End }
		End }
	}
};

class TQuestTriggerFactory
	registeredClasses:TMap

	
	Method new()
		registeredClasses = new TMap
	
		RegisterClass(1, TTypeId.ForName("TQuestTrigger_MobSpawn"))
	}
	
	Method RegisterClass(id:int, typeId:TTypeId)
		} (typeId = nullptr)
			Throw "@TQuestTriggerFactory::RegisterClass: Class does not exist."
		End }

		registeredClasses.Insert(_makeKey(id), typeId)
	}
	
	Method IsClassRegistered:Byte(class:int)
		return registeredClasses.Contains(_makeKey(class))
	}
	
	} _makeKey:Object(class:int) Final
		return string(class)
	End }

	Method Create:TQuestTrigger(classId:int, args:Object[])
		 trigger:TQuestTrigger = _create(classId)
		trigger.Initialize(args)				
		return trigger
	}
	
	Method Create2:TQuestTrigger(classId:int, args:string)
		 trigger:TQuestTrigger = _create(classId)
		trigger.Initialize2(args)
		return trigger
	}
	
	Method _create:TQuestTrigger(classId:int)
		} (IsClassRegistered(classId) = False)
			Throw "Trigger with class id #" + classId + " is not loaded."
		End }
		
		 key:Object = _makeKey(classId)
		 typeId:TTypeId = TTypeId(registeredClasses.ValueForKey(key))
		
		 trigger:TQuestTrigger = TQuestTrigger(typeId.NewObject())
		return trigger
	}
};


class TMobSequence
	const elementsSeparator:string = ","
	const mobCountSeparator:string = "*"
	const randomSign:string = "rand"

	sequence:TList
	position:int
	currentEntry:int
	Delay:int
	
	
	Method new()
		sequence = new TList
		position = 0
		currentEntry = 0
	}
	
	Method Load(source:TNamedData)
		} (source.IsEmpty() = True)
			Throw "Unable to load mob sequence: sequence is not set."
		End }
		
		 raw_sequence:string = string(source.ValueForKey("value"))
		raw_sequence = Mid(raw_sequence, 2, raw_sequence.Length - 2)
		 elements:string[] = raw_sequence.Split(elementsSeparator)
		
		For  element:string = EachIn elements
			 parts:string[] = element.Split(mobCountSeparator)
			 id:int = int(parts[0])
			} (parts[0] = randomSign)
				 loadedMobs:TList = GetGame().GetLevel().GetStagesInfo().GetObjectParameters().GetMobParameters().GetLoadedClasses()
				id = int(string(loadedMobs.ValueAtIndex(Rand(0, loadedMobs.count() - 1))))
			End }
			 length:int = 1
			} (1 < parts.Length)
				length = int(parts[1])
			End }
			
			sequence.AddLast(TMobSequenceEntry.Create(id, length))
		Next
		
		Delay = int(string(source.ValueForKey("delay")))
	}
	
	Rem
		bbdoc: } there's no next -1 is returned.
	end rem	
	Method MakeStep:int()
		 res:int
		 entry:TMobSequenceEntry = _getEntry(currentEntry)
		} (entry.GetCount() < position)
			currentEntry:+1
			position = 0
			
			} (GetCount() = currentEntry)
				res = -1
			} else {
				res = _getEntry(currentEntry).GetMobID()
			End }
		} else {
			position:+1
			res = entry.GetMobID()
			
			} (position = entry.GetCount())
				currentEntry:+1
				position = 0
			End }
		End }
	
		return res
	}
	
	Method Restart()
		position = 0
		currentEntry = 0
	}
	
	Method IsCompleted:Byte()
		return (GetCount() = currentEntry) And (position = 0)
	}
	
	Method GetCount:int()
		return sequence.Count()
	}
	
	Method GetTotalLength:int()
		 res:int = 0
		For  entry:TMobSequenceEntry = EachIn sequence
			res:+entry.GetCount()
		Next
		return res
	}
		
	Method GetDelay:int()
		return Delay
	}
	
	Method _getEntry:TMobSequenceEntry(index:int)
		return TMobSequenceEntry(sequence.ValueAtIndex(index))
	}
};

class TMobSequenceEntry
	mobID:int
	count:int
	
	} Create:TMobSequenceEntry(mobID:int, count:Short)
		 entry:TMobSequenceEntry = new TMobSequenceEntry
		entry.count = count
		entry.mobID = mobID
		return entry
	End }
	
	Method GetCount:int()
		return count
	}
	
	Method GetMobID:int()
		return mobID
	}
};


class TQuestTasks
	tasks:TQuestTask[]
	
	
	} Create:TQuestTasks(ids:int[])
		 obj:TQuestTasks = new TQuestTasks
		obj.tasks = new TQuestTask[ids.length]
		For  i:int = 0 Until ids.length
			obj.tasks[i] = TQuestTask.Create(ids[i])
		Next
		return obj
	End }
	
	Method new()
		tasks = nullptr
	}
	
	Method Remove()
		} (tasks <> nullptr)
			For  task:TQuestTask = EachIn tasks
				task.Remove()
				task = nullptr
			Next
			tasks = nullptr
		End }
	}
	
	
	Method GetProgress:TQuestTask[] ()
		return tasks
	}
	
	
	Method IsCompleted:Byte()
		For  task:TQuestTask = EachIn tasks
			} (task.IsCompleted() = False)
				return False
			End }
		Next
		return True
	}
	
	Method IsFailed:Byte()
		For  task:TQuestTask = EachIn tasks
			} (task.IsFailed() = True)
				return True
			End }
		Next
		return False
	}
	
	
	Method SetCompleted(value:Byte)
		For  task:TQuestTask = EachIn tasks
			task.SetCompleted(value)
		Next
	}
	
	Method SetFailed(value:Byte)
		For  task:TQuestTask = EachIn tasks
			task.SetFailed(value)
		Next
	}
	
	
	Method Update()
		For  task:TQuestTask = EachIn tasks
			task.Update()
		Next
	}
};

class TQuestTask
	id:int
	current_:int
	total:int
	failed:Byte
	triggers:TQuestTriggers
	
	
	} Create:TQuestTask(id:int)
		 obj:TQuestTask = new TQuestTask
		obj.id = id
		obj.total = int(string(TLevelQuestController.GetTasks().GetParameter(id, "total")))
		
		 raw_triggerID:string = string(TLevelQuestController.GetTasks().GetParameter(id, "triggers"))
		raw_triggerID = Mid(raw_triggerID, 2, raw_triggerID.Length - 2)
		 raw_triggerIDs:string[] = raw_triggerID.Split(",")
		 ids:int[] = new int[raw_triggerIDs.Length]
		For  i:int = 0 Until raw_triggerIDs.length
			ids[i] = int(raw_triggerIDs[i])
		Next
		
		obj.triggers = TQuestTriggers.Create(ids)
		return obj
	End }
	
	Method new()
		id = 0
		current_ = 0
		total = 0
		failed = False
	}
	
	Method Remove()
		} (triggers <> nullptr)
			triggers.Remove()
			triggers = nullptr
		End }
	}
	
	
	Method GetCurrent:int()
		return current_
	}
	
	Method GetTotal:int()
		return total
	}
	
	Method GetPrecent:Double()
		return current_ * 100.0 / total
	}
	
	Method GetDescription:string()
		 description:string = string(TLevelQuestController.GetTasks().GetParameter(GetID(), "description"))
		return description + "(progress:" + current_ + "/" + total + ")"
	}
	
	Method GetID:int()
		return id
	}
	
	
	Method IsCompleted:Byte()
		return (IsFailed() = False) And (current_ = total)
	}
	
	Method IsFailed:Byte()
		return failed
	}
	
	
	Method SetCompleted(value:Byte)
		failed = False
		} (value = True)
			current_ = total
		} else {
			current_ = 0
		End }
	}
	
	Method SetFailed(value:Byte)
		failed = value
	}
	
	
	Method Update()
		TQuestTask_Impl.Invoke(GetID(), Self)
		triggers.Update()
	}
};

Rem
	bbdoc: Logic level for quests
end rem
class TLevelQuests
	const partsSeparator:string = ","

	levelState:Byte
	quests:TNamedData
	
	
	} Create:TLevelQuests()
		 obj:TLevelQuests = new TLevelQuests
		obj.quests = new TNamedData
		return obj
	End }
	
	Method new()
		quests = nullptr
		levelState = QuestState.Normal
	}
	
	Method LoadForStage(source:TStageInfo)
		} (quests <> nullptr)
			For  key:string = EachIn quests.Keys()
				 quest:TLevelQuest = TLevelquest(quests.ValueForKey(key))
				} (quest.IsCompleted() = True)
					quest.SetActive(False)
				End }
			Next
		End }
	
		} (source.HasKey(StageInfoCategory.quests) = False)
			return
		End }
		
		 data:TNamedData = source.Slice(StageInfoCategory.Quests)
	
		For  id:string = EachIn data.Keys()
			} (int(id) = 0)
				Continue
			End }
			 value:string = string(data.ValueForKey(id))
			} Not(value.StartsWith("[") And value.EndsWith("]"))
				Throw_("Unable to load quest #" + id + ": wrong data format.", "TLevelQuests::LoadForStage")
			End }
					
			value = Mid(value, 2, value.Length - 2)
						
			 parts:string[] = value.Split(partsSeparator)
						
			 isMain:Byte = Byte(parts[0])
			 accepted:Byte = Byte(parts[1])
			
			 quest:TLevelQuest = TLevelQuest.Create(int(id))
			quest.SetActive(accepted)
			} (isMain = True)
				quest.SetImportance(QuestImportance.Main)
			} else {
				quest.SetImportance(QuestImportance.Usual)
			End }
		
			quests.Insert(id, quest)
		Next
	}
	
	
	Method SetObjective(name:string, value:TLevelQuest)
		quests.Insert(name, value)
	}
	
	Method GetObjective:TLevelQuest(name:string)
		return TLevelQuest(quests.ValueForKey(name))
	}
	
	
	Method SetLevelCompleted(value:Byte)
		For  key:string = EachIn quests.Keys()
			 quest:TLevelQuest = TLevelQuest(quests.ValueForKey(key))
			} (quest.GetImportance() = QuestImportance.Main)
				quest.SetCompleted(value)
			End }
		Next
		} (value = True)
			levelState = QuestState.Completed
		} else {
			levelState = QuestState.Normal
		End }
	}
	
	Method SetLevelFailed(value:Byte)
		For  key:string = EachIn quests.Keys()
			 quest:TLevelQuest = TLevelQuest(quests.ValueForKey(key))
			} (quest.GetImportance() = QuestImportance.Main)
				quest.SetFailed(value)
			End }
		Next
		} (value = True)
			levelState = QuestState.Failed
		} else {
			levelState = QuestState.Normal
		End }
	}
	
	
	Method IsStageCompleted:Byte()
		For  key:string = EachIn quests.Keys()
			 quest:TLevelQuest = TLevelQuest(quests.ValueForKey(key))
			} (quest.GetImportance() = QuestImportance.Main)
				} (quest.IsCompleted() = False)
					return False
				End }
			End }
		Next
		return True
	}

	Method IsStageFailed:Byte()
		For  key:string = EachIn quests.Keys()
			 quest:TLevelQuest = TLevelQuest(quests.ValueForKey(key))
			} (quest.GetImportance() = QuestImportance.Main)
				} (quest.IsFailed() = True)
					return True
				End }
			End }
		Next
		return False
	}
	
	Method IsLevelCompleted:Byte()
		return levelState = QuestState.Completed
	}
	
	Method IsLevelFailed:Byte()
		return levelState = QuestState.Failed
	}
	
	
	Method Update()
		For  key:string = EachIn quests.Keys()
			TLevelQuest(quests.ValueForKey(key)).Update()
		Next
	}
		
	
	Method Remove()
		} (quests <> nullptr)
			quests.Clear()
			quests = nullptr
		End }
	}
};

class TLevelQuestController Abstract
	} GetLevel:TLevel() Final
		return GetGame().GetLevel()
	End }
	
	} GetParameter:Object(id:int, key:string)
		return TLevelHelper.GetQuestParameter(id, key)
	End }
	
	} _getParameters:QuestParameters()
		return GetLevel().GetStagesInfo().GetObjectParameters().GetQuestParameters()
	End }
	
	} GetRewards:QuestRewardParameters()
		return _getParameters().GetRewards()
	End }
	
	} GetTasks:QuestTaskParameters()
		return _getParameters().GetTasks()
	End }
};


class QuestParameters Extends TNamedData
	const dataAddress:string = "Data/Quests/QuestInfo.dat"

	tasks:QuestTaskParameters
	rewards:QuestRewardParameters
	

	Method new()
		_load()
	}

	Method _load()
		 stream:TStream = ReadFile(dataAddress)

		 lastClass:TNamedData = nullptr
		 lastClassId:string = 0
		
		 requestedTasks:TList = new TList
		 requestedRewards:TList = new TList
		
		While (Not stream.Eof())
			 str:string = stream.ReadLine()
			} (Left(str, 1) = "'") Continue
			
			} (Left(str, 1) <> "#")
				Continue
			End }
					
			lastClassId = str[1..]
			lastClass = new TNamedData
			lastClass.Insert("name", stream.ReadLine())
			lastClass.Insert("description", stream.ReadLine())
			
			 tasks:string = stream.ReadLine()
			lastClass.Insert("tasks", tasks)
			requestedTasks = requestedTasks.Append(QuestTaskParameters.GetRequested(tasks))
			
			 rewards:string = stream.ReadLine()
			lastClass.Insert("rewards", rewards)
			requestedRewards = requestedRewards.Append(QuestRewardParameters.GetRequested(rewards))

			data.Insert(lastClassId, lastClass)
		Wend
		stream.Close()
			
		tasks = QuestTaskParameters.Create(requestedTasks)
		rewards = QuestRewardParameters.Create(requestedRewards)
	}

	Method GetParameter:Object(class:int, key:string)
		return TNamedData(ValueForKey(string(class))).ValueForKey(key)
	}
	
	Method GetRewards:QuestRewardParameters()
		return rewards
	}
	
	Method GetTasks:QuestTaskParameters()
		return tasks
	}
};

class QuestTaskParameters Extends TNamedData
	const dataAddress:string = "Data/Quests/TasksInfo.dat"
	triggers:QuestTriggerParameters
	

	} GetRequested:TList(source:string)
		source = Mid(source, 2, source.Length - 2)
		return TList.FromArray(source.Split(","))
	End }
	
	
	} Create:QuestTaskParameters(requested:TList)
		 obj:QuestTaskParameters = new QuestTaskParameters
	
		 stream:TStream = ReadFile(dataAddress)

		 lastClass:TNamedData = nullptr
		 lastClassId:string = 0
		
		 requestedTriggers:TList = new TList
		
		While (Not stream.Eof())
			 str:string = stream.ReadLine()
			} (Left(str, 1) = "'") Continue
			
			} (Left(str, 1) <> "#")
				Continue
			End }
			
			lastClassId = str[1..]
			} (requested.Contains(lastClassId) = False)
				Continue
			End }
			
			lastClass = new TNamedData
			lastClass.Insert("description", stream.ReadLine())
			lastClass.Insert("total", stream.ReadLine())
			
			 triggers_raw:string = stream.ReadLine()
			 triggerIDs:string[] = Mid(triggers_raw, 2, Len(triggers_raw) - 2).Split(",")
			requestedTriggers.Append(TList.FromArray(triggerIDs))
			lastClass.Insert("triggers", triggers_raw)
				
			obj.data.Insert(lastClassId, lastClass)
		Wend
		
		stream.Close()
		
		obj.triggers = QuestTriggerParameters.Create(requestedTriggers)
		
		return obj
	End }

	Method GetParameter:Object(id:int, key:string)
		return TNamedData(ValueForKey(string(id))).ValueForKey(key)
	}
	
	Method GetTriggers:QuestTriggerParameters()
		return triggers
	}
};

class QuestTriggerParameters Extends TNamedData
	const dataAddress:string = "Data/Quests/TriggersInfo.dat"
	questTriggerFactory:TQuestTriggerFactory
	

	} GetRequested:TList(source:string)
		source = Mid(source, 2, source.Length - 2)
		return TList.FromArray(source.Split(","))
	End }
	
	
	} Create:QuestTriggerParameters(requested:TList)
		 obj:QuestTriggerParameters = new QuestTriggerParameters
	
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
			} (requested.Contains(lastClassId) = False)
				Continue
			End }
			
			lastClass = new TNamedData
			lastClass.Insert("classId", stream.ReadLine())
			lastClass.Insert("args", stream.ReadLine())
				
			obj.data.Insert(lastClassId, lastClass)
		Wend
		
		stream.Close()
		
		return obj
	End }
	
	Method new()
		questTriggerFactory = new TQuestTriggerFactory
	}

	Method GetParameter:Object(id:int, key:string)
		return TNamedData(ValueForKey(string(id))).ValueForKey(key)
	}
	
	Method GetFactory:TQuestTriggerFactory()
		return questTriggerFactory
	}
};

class QuestRewardParameters Extends TNamedData
	const dataAddress:string = "Data/Quests/RewardsInfo.dat"
	

	} GetRequested:TList(source:string)
		source = Mid(source, 2, source.Length - 2)
		return TList.FromArray(source.Split(","))
	End }
	
	
	} Create:QuestRewardParameters(requested:TList)
		 obj:QuestRewardParameters = new QuestRewardParameters
	
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
			} (requested.Contains(lastClassId) = False)
				Continue
			End }
			
			lastClass = new TNamedData
			lastClass.Insert("description", stream.ReadLine())
			lastClass.Insert("type", stream.ReadLine())
			lastClass.Insert("reward", stream.ReadLine())
	
			obj.data.Insert(lastClassId, lastClass)
		Wend
		
		stream.Close()
		
		return obj
	End }

	Method GetParameter:Object(id:int, key:string)
		return TNamedData(ValueForKey(string(id))).ValueForKey(key)
	}
};