local TEventRegistry = {}
	local function TEventRegistry.Create(events)
		local obj = {}
		setmetatable(obj, TEventRegistry)

		if (events ~= nil) then
			for i,v in ipairs(events) do
				obj:RegisterEvent(v)
			end
		end

		return obj
	end

	local EventRegistry = TEventRegistry.Create

	local function TEventRegistry:RegisterEvent(name)
		local id = self[name]
		if (id == nil) then
			id = #self + 1
			self[name] = id
		end
		return id
	end

	local function TEventRegistry:GetEventId(name)
		return self[name]
	end

	local function TEventRegistry:UnregisterEvent(name)
		local id = self[name]
		if (id ~= nil) then
			self[name] = nil
		end
	end


TEvent = {}
	function TEvent.Create(id, context)
		local obj = {}
		setmetatable(obj, TEvent)
		obj.id = id
		obj.context = context
		return obj
	end

	Event = TEvent.Create

	function TEvent:GetId()
		return self.id
	end

	function TEvent:GetContext()
		return self.context
	end


local TEventQueue = {}
	local function TEventQueue.Create()
		local obj = {}
		setmetatable(obj, TEventQueue)
		obj.first = 0
		obj.last = 0

		return obj
	end

	local EventQueue = TEventQueue.Create

	local function TEventQueue:Enqueue(event)
		local last = self.last + 1
		self[last] = event
		self.last = last
	end

	local function TEventQueue:Dequeue()
		if (self.last < self.first) then
			error("Queue is empty.")
		end
		local result = self[self.first]
		self[self.first] = nil
		self.first += 1
		return result
	end

	local function TEventQueue:Empty()
		return self.last == self.first
	end


local TEventListeners = {}
	local function TEventListeners.Create()
		local obj = {}
		setmetatable(obj, TEventListeners)
		obj.first = 0
		obj.last = 0

		return obj
	end

	local EventListeners = TEventListeners.Create

	local function TEventListeners:Insert(listener)
		local last = self.last + 1
		self[last] = event
		self.last = last
	end

	local function TEventListeners:Remove(listener)
		if (self.Empty() == false) then
			for i,entry in ipairs(self) do
				if (listener == entry) then
					entry = nil
					break
				end
			end
		end
	end

	local function TEventListeners:Empty()
		return self.last == self.first
	end


local TEventDispatcher = {}
	local function TEventDispatcher.Create()
		local obj = {}
		setmetatable(obj, TEventDispatcher)
		return obj
	end

	local EventDispatcher = TEventDispatcher.Create

	local function TEventDispatcher:AddListener(listener, eventId)
		local listeners = self[eventId]
		if (listeners == nil) then
			listeners = self:RegisterEvent(eventId)
		end
		listeners:Insert(listener)
	end

	local function TEventDispatcher:RemoveListener(listener, eventId)
		local listeners = self[eventId]
		if (listeners == nil) then
			error("Event #"..eventId.." is not registered.")
		end
		listeners:Remove(listener)
	end

	local function TEventDispatcher:RegisterEvent(eventId)
		local listeners = self[eventId]
		if (listeners ~= nil) then
			error("Event #"..eventId.." is already registered.")
		end
		listeners = EventListeners()
	end

	local function TEventDispatcher:UnregisterEvent(eventId)
		local listeners = self[eventId]
		if (listeners ~= nil) then
			self[eventId] = nil
		end
	end

	local function TEventDispatcher:Notify(event)
		local listeners = self[event:GetId()]
		if (listeners == nil) then
			error("Event #"..eventId.." is not registered.")
		end
		for i, listener in ipairs(listeners) do
			listener:Notify(event)
		end
	end


TEventController = {}
	function TEventController.Create()
		local obj = {}
		setmetatable(obj, TEventController)
		obj.eventRegistry = EventRegistry()
		obj.eventQueue = EventQueue()
		obj.eventDispatcher = EventDispatcher()
		return obj
	end

	EventController = TEventController.Create

	function TEventController:RegisterEvent(event)
		local id = self.eventRegistry:RegisterEvent(event)
		self.eventDispatcher:RegisterEvent(id)
	end

	function TEventController:UnregisterEvent(event)
		local id = self.eventRegistry:GetEventId(event)
		if (id ~= nil) then
			self.eventRegistry:UnregisterEvent(event)
			self.eventDispatcher:UnregisterEvent(id)
		end
	end

	function TEventController:EmitEvent(event)
		self.eventQueue:Enqueue(event)
	end

	function TEventController:Update()
		while (self.eventQueue:Empty() == false) do
			local event = self.eventQueue:Dequeue()
			eventDispatcher:Notify(event)
		end
	end