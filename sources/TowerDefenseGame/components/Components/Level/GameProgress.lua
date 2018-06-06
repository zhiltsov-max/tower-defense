--[[
	Module: Progress
	Description: see docs
]]--
require("GameQuests")
require("GameResearches")
require("GameEvents")


TProgress = {}
	function TProgress.Create() 
		newObj = {}
		setmetatable(newObj, TProgress)
		return newObj
	end
	Progress = TProgress.Create
		
	function TProgress:Load(info)
		newObj.eventController = EventController()
		newObj.researches = Researches(info["researches"])
		newObj.quests = Quests(info["quests"])
		newObj.credits = stoi(info["credits"])
		newObj.points = stoi(info["points"])
	end
	
	function TProgress:Update() 
		self.eventController:Update()
	end

	function TProgress:GetCredits()
		return self.credits 
	end

	function TProgress:GetPoints()
		return self.points
	end

    function TProgress:GetResearches()
    	return self.researches
    end

	function TProgress:GetQuests()
		return self.quests
	end

	function TProgress:GetEventController()
		return self.eventController
	end
