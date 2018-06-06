--[[
	Module: Staging
	Description: Declares and implements staging tools for level.
]]--

TStageLoader = {}
	function TStageLoader:Create()
		newObj = {}
		setmetatable(newObj, self)
		return newObj
	end

	function TStageLoader:Load(level, info)
		-- none, level-specific
	end