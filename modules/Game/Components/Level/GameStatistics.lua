TStatistics = {}
	function TStatistics.Create(keys)
		local statistics = {}
		setmetatable(statistics, TStatistics)

		if (keys ~= nil) then
			for i,v in ipairs(keys) do
				statistics[v] = 0
			end
		end

		return statistics
	end

	Statistics = TStatistics.Create


	function TStatistics:Register_metric(name)
		local id = statistics[name]
		if (id == nil) then
			id = #statistics + 1
			statistics[name] = id
		end
		return id
	end

	function TStatistics:Unregister_metric(name)
		local id = statistics[name]
		if (id ~= nil) then
			statistics[name] = nil
		end
	end

	function TStatistics:Get_metric(name)
		return statistics[name]
	end

	function TStatistics:Set_metric(name, value)
		statistics[name] = value
	end

