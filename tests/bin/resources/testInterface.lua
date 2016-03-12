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


defaultFont = "resources/font.ttf"

windowSource = WindowSource({
	name = "TestWindow1",
	allowMoving = true,
	color = Color(50, 100, 50, 255),
	enabled = true,
	headerColor = Color(255, 255, 255, 128),
	headerHeight = 20,
	headerText = Wstr("Test window"),
	headerTextColor = Color(0, 0, 255, 255),
	headerTextFont = Font(defaultFont, 18, FontStyle.regular),
	innerElementsPadding = Padding(10, 15, 5, 30),
	position = Coordinate(GetWindowWidth(), GetWindowHeight()) * 0.3,
	show = true,
	size = Size(400, 600),
	image = ImageSource({path = "resources/image.jpg"})
})
window = Window(windowSource)

uiparent = UIParent()
uiparent:AddChild(window)

button1source = PushButtonSource({
    name = "Button1",
    color = Color(255, 255, 0, 255),
    enabled = true,
    font = Font(defaultFont, 15, FontStyle.strikethrough),
    position = Coordinate(10, 10),
    show = true,
    size = Size(100, 50),
    text = Wstr("Button1"),
    textColor = Color(200, 200, 200, 255),
    textPosition = Coordinate(50, 25)
})
button1 = PushButton(button1source)
window:AddChild(button1)


button2Source = PushButtonSource({
    name = "Button2",
    color = Color(0, 255, 255, 255),
    enabled = true,
    font = Font(defaultFont, 15, FontStyle.underlined),
    position = Coordinate(40, 30),
    show = true,
    size = Size(100, 50),
    text = Wstr("Button2"),
    textColor = Color(200, 200, 200, 255),
    textPosition = Coordinate(50, 25)
})
button2 = PushButton(button2Source)
window:AddChild(button2)