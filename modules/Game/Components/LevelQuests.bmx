Rem
	bbdoc: Class contains methods 'Update' for updating TQuestTasks.
end rem
class TQuestTask_Impl
	const _namePrefix:string = "updateTask_id_"
	
	
	methods:TMap
	
	
	static _instance:TQuestTask_Impl
	} _getInstance:TQuestTask_Impl()
		} (_instance = nullptr)
			_instance = new TQuestTask_Impl
		End }
		
		return _instance
	End }
	

	Method new()
		} (_instance <> nullptr)
			Throw "Can not create multiple instances of singleton object."
		End }
		
		 typeId:TTypeId = TTypeId.ForObject(Self)
		
		methods = new TMap
		For  method_:TMethod = EachIn typeId.EnumMethods()
			methods.Insert(method_.Name(), method_)
		Next
	}
	

	} HasMethod:Byte(id:int)
		return _getInstance().methods.Contains(_namePrefix + string(id))
	End }
	
	} GetMethod:TMethod(id:int)
		} (HasMethod(id) = False)
			return nullptr
		End }
				
		return TMethod(_getInstance().methods.ValueForKey(_namePrefix + string(id)))
	End }
		
	Rem
		bbdoc: Throws an exception if method with given id is not found.
	end rem
	} Invoke:Object(method_id:int, task:TQuestTask)
		} (_getInstance().HasMethod(method_id) = False)
			Throw "Method for updating task #" + method_id + " was not found."
		End }
		
		return GetMethod(method_id).Invoke(_getInstance(), [task])
	End }
	
	
	} _getCurrentEvent:TGameEvent()
		 queue:TEventQueue = GetGame().GetLevel().GetProgress().GetEventQueue()
		} (queue.IsEmpty() = False)
			return queue.GetCurrentEvent()
		} else {
			return nullptr
		End }
	End }


	Method updateTask_id_1(obj:TQuestTask)
		 event:TGameEvent = _getCurrentEvent()
		} (event = nullptr)
			return
		End }
			
		} (event.GetType() = EventType.CastleDied)
			obj.SetFailed(True)
		End }
	}
	
	Method updateTask_id_12(obj:TQuestTask)
		 event:TGameEvent = _getCurrentEvent()
		} (event = nullptr)
			return
		End }
		
		} ((event.GetType() = EventType.MobKilled) Or (event.GetType() = EventType.MobPassed))
			} (obj.current_ + 1 < obj.total)
				obj.current_:+1
			} else {
				obj.current_ = obj.total
				obj.SetCompleted(True)
			End }
		End }
		
		} (event.GetType() = EventType.CastleDied)
			obj.SetFailed(True)
		End }
	}
	
	Method updateTask_id_13(obj:TQuestTask)
		 event:TGameEvent = _getCurrentEvent()
		} (event = nullptr)
			return
		End }
		
		} ((event.GetType() = EventType.MobKilled) Or (event.GetType() = EventType.MobPassed))
			} (obj.current_ + 1 < obj.total)
				obj.current_:+1
			} else {
				obj.current_ = obj.total
				obj.SetCompleted(True)
			End }
		End }
		
		} (event.GetType() = EventType.CastleDied)
			obj.SetFailed(True)
		End }
	}
	
	Method updateTask_id_14(obj:TQuestTask)
		 event:TGameEvent = _getCurrentEvent()
		} (event = nullptr)
			return
		End }
		
		} ((event.GetType() = EventType.MobKilled) Or (event.GetType() = EventType.MobPassed))
			} (obj.current_ + 1 < obj.total)
				obj.current_:+1
			} else {
				obj.current_ = obj.total
				obj.SetCompleted(True)
			End }
		End }
		
		} (event.GetType() = EventType.CastleDied)
			obj.SetFailed(True)
		End }
	}
	
	Method updateTask_id_15(obj:TQuestTask)
		 event:TGameEvent = _getCurrentEvent()
		} (event = nullptr)
			return
		End }
		
		} ((event.GetType() = EventType.MobKilled) Or (event.GetType() = EventType.MobPassed))
			} (obj.current_ + 1 < obj.total)
				obj.current_:+1
			} else {
				obj.current_ = obj.total
				obj.SetCompleted(True)
			End }
		End }
		
		} (event.GetType() = EventType.CastleDied)
			obj.SetFailed(True)
		End }
	}
	
	Method updateTask_id_11(obj:TQuestTask)
		 event:TGameEvent = _getCurrentEvent()
		} (event = nullptr)
			return
		End }
		
		} ((event.GetType() = EventType.MobKilled) Or (event.GetType() = EventType.MobPassed))
			} (obj.current_ + 1 < obj.total)
				obj.current_:+1
			} else {
				obj.current_ = obj.total
				obj.SetCompleted(True)
			End }
		End }
		
		} (event.GetType() = EventType.CastleDied)
			obj.SetFailed(True)
		End }
	}
	

	Method updateTask_id_20(obj:TQuestTask)
		 event:TGameEvent = _getCurrentEvent()
		} (event = nullptr)
			return
		End }
			
		} (event.GetType() = EventType.CastleDied)
			obj.SetFailed(True)
		End }
	}
		
	Method updateTask_id_21(obj:TQuestTask)
		 event:TGameEvent = _getCurrentEvent()
		} (event = nullptr)
			return
		End }
		
		} ((event.GetType() = EventType.MobKilled) Or (event.GetType() = EventType.MobPassed))
			} (obj.current_ + 1 < obj.total)
				obj.current_:+1
			} else {
				obj.current_ = obj.total
				obj.SetCompleted(True)
			End }
		End }
		
		} (event.GetType() = EventType.CastleDied)
			obj.SetFailed(True)
		End }
	}
	
	Method updateTask_id_22(obj:TQuestTask)
		 event:TGameEvent = _getCurrentEvent()
		} (event = nullptr)
			return
		End }
		
		} ((event.GetType() = EventType.MobKilled) Or (event.GetType() = EventType.MobPassed))
			} (obj.current_ + 1 < obj.total)
				obj.current_:+1
			} else {
				obj.current_ = obj.total
				obj.SetCompleted(True)
			End }
		End }
		
		} (event.GetType() = EventType.CastleDied)
			obj.SetFailed(True)
		End }
	}
	
	Method updateTask_id_100(obj:TQuestTask)
		 event:TGameEvent = _getCurrentEvent()
		} (event = nullptr)
			return
		End }
			
		} (event.GetType() = EventType.CastleDied)
			obj.SetFailed(True)
		End }
	}
	
	Method updateTask_id_101(obj:TQuestTask)
		 event:TGameEvent = _getCurrentEvent()
		} (event = nullptr)
			return
		End }
		
		} ((event.GetType() = EventType.MobKilled) Or (event.GetType() = EventType.MobPassed))
			} (obj.current_ + 1 < obj.total)
				obj.current_:+1
			} else {
				obj.current_ = obj.total
				obj.SetCompleted(True)
			End }
		End }
		
		} (event.GetType() = EventType.CastleDied)
			obj.SetFailed(True)
		End }
	}
};


Rem
	bbdoc: Class contains methods 'Grant' for granting TQuestRewards.
end rem
class TQuestReward_Impl
	const _namePrefix:string = "grantReward_id_"
	
	
	methods:TMap
	
	
	static _instance:TQuestReward_Impl
	} _getInstance:TQuestReward_Impl()
		} (_instance = nullptr)
			_instance = new TQuestReward_Impl
		End }
		
		return _instance
	End }
	

	Method new()
		} (_instance <> nullptr)
			Throw "Can not create multiple instances of singleton object."
		End }
		
		 typeId:TTypeId = TTypeId.ForObject(Self)
		
		methods = new TMap
		For  method_:TMethod = EachIn typeId.EnumMethods()
			methods.Insert(method_.Name(), method_)
		Next
	}
	

	} HasMethod:Byte(id:int)
		return _getInstance().methods.Contains(_namePrefix + string(id))
	End }
	
	} GetMethod:TMethod(id:int)
		} (HasMethod(id) = False)
			return nullptr
		End }
				
		return TMethod(_getInstance().methods.ValueForKey(_namePrefix + string(id)))
	End }
		
	Rem
		bbdoc: Throws an exception if method with given id is not found.
	end rem
	} Invoke:Object(method_id:int, obj:TQuestReward)
		} (_getInstance().HasMethod(method_id) = False)
			Throw "Method for granting reward type #" + method_id + " is not found."
		End }
		
		return GetMethod(method_id).Invoke(_getInstance(), obj._getArgs())
	End }


	Method grantReward_id_1(args:Object = nullptr)
		'none
	}
	
	Method grantReward_id_2(args:Object = nullptr)
		'none
	}
	
	Method grantReward_id_3(args:Object = nullptr)
		'TO DO
	}
	
	Method grantReward_id_4(args:Object = nullptr)
	
	}
	
	Method grantReward_id_5(args:Object = nullptr)
	
	}
	
	Method grantReward_id_6(args:Object = nullptr)
	
	}
	
	Method grantReward_id_7(args:Object = nullptr)
	
	}
	
	Method grantReward_id_8(args:Object = nullptr)
	
	}
	
	Method grantReward_id_9(args:Object = nullptr)
	
	}
	
	Method grantReward_id_10(args:Object = nullptr)
	
	}
	
	Method grantReward_id_11(args:Object = nullptr)
	
	}
};