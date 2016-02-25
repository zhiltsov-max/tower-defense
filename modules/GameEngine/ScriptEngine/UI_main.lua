function Debug_Write(text, importance)
	if (getmetatable(text) ~= TWideString) then
		text = Wstr(text)
	end
	if (not importance) then 
		importance = LogMessageImportance.Usual
	end
	e_print(text, Wstr("lua"), importance)
end

function Debug_PrintTable(table, prefix)
	prefix = prefix or ""
	Debug_Write(prefix..tostring(table))
	if (getmetatable(table) ~= nil) then
		Debug_PrintTable(getmetatable(table).__index, prefix..". ")
	end
	if (type(table) == "table") then
		for k, v in pairs(table) do
			Debug_Write(prefix..". '"..tostring(k).."' = '"..tostring(v).."'")
		end
	end
	Debug_Write("")
end


function GetWindowWidth()
	return 800  -- placeholder
end

function GetWindowHeight()
	return 600  -- placeholder
end