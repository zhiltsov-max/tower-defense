-- Классы игрового меню
	--
	UpgradesTree = {}
		setmetatable(UpgradesTree, {__index = TransparentWindow})


		function UpgradesTree:New(source)
			source = source or {}
			setmetatable(source, self)
			self.__index = UpgradesTree
			return source
		end

		function UpgradesTree:Create()
			bCreateUpgradesTree(self)
			self.id = lastUpgradesTreeId
			return self.id
		end

	--
	UpgradesTreeItem = {}
		setmetatable(UpgradesTreeItem, {__index = MenuObject})
		UpgradesTreeItem.dataId = 0

		UpgradesTreeItem.button = PushButton:New()
		UpgradesTreeItem.imagePathBox = ImageBox:New()

		UpgradesTreeItem.size = Size:New()


		function UpgradesTreeItem:New(source)
			source = source or {}
			setmetatable(source, self)
			self.__index = UpgradesTreeItem
			return source
		end

		function UpgradesTreeItem:Create()
			bCreateUpgradesTreeItem(self)
			self.id = lastUpgradesTreeItemId
			return self.id
		end

	--
	UpgradesTreeItems = {
		UpgradesTreeItem:New({
			name = "Item_0",
			position = Coordinate:New({x = 0, y = 0}), dataId = 0, 
			button = {name = "Button"},
			imageBox = {name = "ImageBox", imagePath = "Data/Buildings/Base.png"}
		}),

		UpgradesTreeItem:New({
			name = "Item_1",
			position = Coordinate:New({x = 1, y = 0}), dataId = 1, 
			button = {name = "Button"},
			imageBox = {name = "ImageBox", imagePath =  "Data/Buildings/Base.png"}
		}),

		UpgradesTreeItem:New({
			name = "Item_2",
			position = Coordinate:New({x = 2, y = 0}), dataId = 2, 
			button = {name = "Button"},
			imageBox = {name = "ImageBox", imagePath = "Data/Buildings/Base.png"}
		}),

		UpgradesTreeItem:New({
			name = "Item_3",
			position = Coordinate:New({x = 1, y = 1}), dataId = 3, 
			button = {name = "Button"},
			imageBox = {name = "ImageBox", imagePath = "Data/Buildings/Rocket.png"}
		}),

		--["Rocket_RotatingTurret"] 	= UpgradesTreeItem:New({cost = 250, position = Coordinate:New({x = 2, y = 1}),, imagePath = "Data/Buildings/Rocket.png"}),
		UpgradesTreeItem:New({
			name = "Item_4",
			position = Coordinate:New({x = 2, y = 2}), dataId = 4, 
			button = {name = "Button"},
			imageBox = {name = "ImageBox", imagePath = "Data/Buildings/Art.png"}	
		})
	}

	--
	PopUpWindow = {}
		setmetatable(PopUpWindow, {__index = TransparentWindow})
		PopUpWindow.upgradeButton = PushButton:New()
		PopUpWindow.sellButton = PushButton:New()
		PopUpWindow.textBox = RichTextBox:New()

		function PopUpWindow:New(source)
			local source = source or {}
			setmetatable(source, {__index = self})
			self.__index = PopUpWindow
			return source
		end

		function PopUpWindow:Create()
			bCreatePopUpWindow(self)
			self.id = lastPopUpWindowId
			return self.id
		end

	GameInfoWindow = {}
		setmetatable(GameInfoWindow, {__index = Window})
		GameInfoWindow.textBox = RichTextBox:New()

		function GameInfoWindow:New(source)
			local source = source or {}
			setmetatable(source, {__index = self})
			self.__index = GameInfoWindow
			return source
		end

		function GameInfoWindow:Create()
			bCreateGameInfoWindow(self)
			self.id = lastGameInfoWindowId
			return self.id
		end

	MessageBubble = {}
		setmetatable(MessageBubble, {__index = MessageBox})
		MessageBubble.style = 4

		function MessageBubble:New(source)
			local source = source or {}
			setmetatable(source, {__index = self})
			self.__index = MessageBubble
			return source
		end

		function MessageBubble:Create()
			bCreateMessageBubble(self)
			self.id = lastMessageBubbleId
			return self.id
		end