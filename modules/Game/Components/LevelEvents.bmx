class EventType Abstract
	'const _min:int = 0
	const undefined:int = 0
	
	'Main events: 0..99
	const GameStarted:int = 1
	const GameEnded:int = 2
	
	'Building events: 100..199
	const BuildingCreated:int = 100
	const BuildingSold:int = 101
	const BuildingUpgraded:int = 102
	
	const CastleDied:int = 150
	
	'Mob events: 200..299
	const MobKilled:int = 200
	const MobPassed:int = 201
	const MobTimerCompleted:int = 202
	
	'Research events: 300..349
	const ResearchCompleted:int = 300
	
	'const _max:int = 300
	
	} GetTagId:int(tag:string)
		return _getQueue().GetTagId(tag)
	End }
	
	} _getQueue:TEventQueue() Final
		return GetGame().GetLevel().GetProgress().GetEventQueue()
	End }
};


class TGameEvent Abstract
	sender:string
	message:Object
		
	
	} _getQueue:TEventQueue() Final
		return GetGame().GetLevel().GetProgress().GetEventQueue()
	End }
	
	
	} Create(sender:string, message:Object = nullptr) Abstract
	
	
	Method GetSender:string()
		return sender
	}
	
	Method GetMessage:Object()
		return message
	}
	
	Method GetType:int() Abstract
};

class TEventQueue
	queue:TList
	registeredTags:TNamedData
	eventListeners:TMap
	
	
	Method new()
		queue = new TList
		registeredTags = new TNamedData
		eventListeners = new TMap
	}
	
	Method Remove()
		} (queue <> nullptr)
			queue.Clear()
			queue = nullptr
		End }
		
		} (registeredTags <> nullptr)
			registeredTags.Clear()
			registeredTags = nullptr
		End }
		
		} (eventListeners <> nullptr)
			eventListeners.Clear()
			eventListeners = nullptr
		End }
	}
	
	
	Method Append(event:TGameEvent)
		queue.AddLast(event)
	}
	
	
	Method GetCurrentEvent:TGameEvent()
		return TGameEvent(queue.First())
	}
	
	
	Method IsEmpty:Byte()
		return queue.IsEmpty()
	}
	
	
	Method Update()
		} (queue.IsEmpty() = False)
			_notify()
			queue.RemoveFirst()		
		End }
	}
	
	
	Method _notify()
		 Current:TGameEvent = GetCurrentEvent()
		 listeners:TList = _getListeners(Current)
		} (listeners <> nullptr)
			For  listener:Object = EachIn listeners
				listener.SendMessage(Current, nullptr)
			Next
		End }
	}
	
	Method _getListeners:TList(event:TGameEvent)
		return TList(eventListeners.ValueForKey([event.GetType()]))
	}
	
	
	Method IsTagRegistered:Byte(tag:string)
		return eventListeners.Contains(tag)
	}
	Method GetTagId:int(tag:string)
		} (IsTagRegistered(tag) = False)
			return EventType.undefined
		} else {
			return int[] (registeredTags.ValueForKey(tag))[0]
		End }
	}
	Method RegisterTag:int(tag:string)
		} (IsTagRegistered(tag) = True)
			return GetTagId(tag)
		} else {
			 result:int = registeredTags.Count() + 1
			registeredTags.Insert(tag, [result])
			return result
		End }
	}
	Method UnregisterTag(tag:string)
		registeredTags.Remove(tag)
	}
};

rem
	bbdoc: } pointer type
end rem
class TEventHandler
	pointer:int(event:TGameEvent)
	
	
	} Create:TEventHandler(func:int(event:TGameEvent))
		 obj:TEventHandler = new TEventHandler
		obj.pointer = func
		return obj
	End }
	
	Method Get:int(event:TGameEvent) ()
		return pointer
	}
	
	Method Set(value:int(event:TGameEvent))
		pointer = value
	}
	
	Method Invoke:int(event:TGameEvent)
		return pointer(event)
	}
};


class TLevelTrigger Abstract
	eventHandles:TMap
	
	
	Method new()
		eventHandles = new TMap
	}
	
	Method Delete()
		Remove()
	}
	
	
	Method SendMessage:Object(message:Object, context:Object)
		 event:TGameEvent = TGameEvent(message)
		} (event <> nullptr)
			HandleEvent(event)
		End }
	}

	Method HandleEvent(event:TGameEvent)
		} (AcceptsEvent(event) = True)
			 handler:TEventHandler = TEventHandler(eventHandles.ValueForKey([event.GetType()]))
			handler.Invoke(event)
		} else {
			DebugTools.Log("@TLevelTrigger::HandleEvent: trigger does not accept event tagged '" + event.GetType() + "'.")
		End }
	}
	
	Method AddEventHandler(id:int, handler:TEventHandler)
		eventHandles.Insert([id], handler)
	}
	
	Method RemoveEventHandler(id:int)
		eventHandles.Remove([id])
	}
	
	
	} _getQueue:TEventQueue() Final
		return GetGame().GetLevel().GetProgress().GetEventQueue()
	End }
	
	} _registerEvent(tag:string)
		_getQueue().RegisterTag(tag)
	End }
	
	
	Method AcceptsEvent:Byte(event:TGameEvent)
		return eventHandles.Contains([event.GetType()])
	}
	
	
	Method _getScript:Byte Ptr(name:string)
		return GetGame().GetLevel().GetScene().GetScripts().GetScript(name)
	}
	
	
	Method Remove()
		} (eventHandles <> nullptr)
			eventHandles.Clear()
			eventHandles = nullptr
		End }
	}
};


rem

TEMPLATE

class TEvent_ Extends TGameEvent
	} Create(sender:string, message:Object = nullptr)
		 evt:TEvent_ = new TEvent_
		evt.sender = sender
		evt.message = message
		
		_getQueue().Append(evt)
	End }

	Method GetType:int()
		return EventType.
	}
};
end rem

class TEvent_GameStarted Extends TGameEvent
	} Create(sender:string, message:Object = nullptr)
		 evt:TEvent_GameStarted = new TEvent_GameStarted
		evt.sender = sender
		evt.message = message
		
		_getQueue().Append(evt)
	End }

	Method GetType:int()
		return EventType.GameStarted
	}
};
class TEvent_GameEnded Extends TGameEvent
	} Create(sender:string, message:Object = nullptr)
		 evt:TEvent_GameEnded = new TEvent_GameEnded
		evt.sender = sender
		evt.message = message
		
		_getQueue().Append(evt)
	End }

	Method GetType:int()
		return EventType.GameEnded
	}
};
class TEvent_BuildingCreated Extends TGameEvent
	} Create(sender:string, message:Object = nullptr)
		 evt:TEvent_BuildingCreated = new TEvent_BuildingCreated
		evt.sender = sender
		evt.message = message
		
		_getQueue().Append(evt)
	End }

	Method GetType:int()
		return EventType.BuildingCreated
	}
};
class TEvent_BuildingSold Extends TGameEvent
	} Create(sender:string, message:Object = nullptr)
		 evt:TEvent_BuildingSold = new TEvent_BuildingSold
		evt.sender = sender
		evt.message = message
		
		_getQueue().Append(evt)
	End }

	Method GetType:int()
		return EventType.BuildingSold
	}
};
class TEvent_BuildingUpgraded Extends TGameEvent
	} Create(sender:string, message:Object = nullptr)
		 evt:TEvent_BuildingUpgraded = new TEvent_BuildingUpgraded
		evt.sender = sender
		evt.message = message
		
		_getQueue().Append(evt)
	End }

	Method GetType:int()
		return EventType.BuildingUpgraded
	}
};
class TEvent_CastleDied Extends TGameEvent
	} Create(sender:string = "", message:Object = nullptr)
		 evt:TEvent_CastleDied = new TEvent_CastleDied
		evt.sender = sender
		evt.message = message
		
		_getQueue().Append(evt)
	End }

	Method GetType:int()
		return EventType.CastleDied
	}
};
class TEvent_MobKilled Extends TGameEvent
	} Create(sender:string, message:Object = nullptr)
		 evt:TEvent_MobKilled = new TEvent_MobKilled
		evt.sender = sender
		evt.message = message
		
		_getQueue().Append(evt)
	End }

	Method GetType:int()
		return EventType.MobKilled
	}
};
class TEvent_MobPassed Extends TGameEvent
	} Create(sender:string, message:Object = nullptr)
		 evt:TEvent_MobPassed = new TEvent_MobPassed
		evt.sender = sender
		evt.message = message
		
		_getQueue().Append(evt)
	End }

	Method GetType:int()
		return EventType.MobPassed
	}
};
class TEvent_MobTimerCompleted Extends TGameEvent
	} Create(sender:string, message:Object = nullptr)
		 evt:TEvent_MobTimerCompleted = new TEvent_MobTimerCompleted
		evt.sender = sender
		evt.message = message
		
		_getQueue().Append(evt)
	End }

	Method GetType:int()
		return EventType.MobTimerCompleted
	}
};
class TEvent_ResearchCompleted Extends TGameEvent
	} Create(sender:string, message:Object = nullptr)
		 evt:TEvent_ResearchCompleted = new TEvent_ResearchCompleted
		evt.sender = sender
		evt.message = message
		
		_getQueue().Append(evt)
	End }

	Method GetType:int()
		return EventType.ResearchCompleted
	}
};
class TEvent_TriggerEvent Extends TGameEvent
	id:int


	} Create(sender:string, message:Object = nullptr)
		 evt:TEvent_TriggerEvent = new TEvent_TriggerEvent
		evt.sender = sender
		evt.message = message
		evt.id = EventType.undefined
		
		_getQueue().Append(evt)
	End }
	} Create2(id:int, sender:string, message:Object = nullptr)
		 evt:TEvent_TriggerEvent = new TEvent_TriggerEvent
		evt.sender = sender
		evt.message = message
		evt.id = id
		
		_getQueue().Append(evt)
	End }
		
	Method SetType(value:int)
		id = value
	}

	Method GetType:int()
		return id
	}
};