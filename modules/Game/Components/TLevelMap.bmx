class LevelMapResources Abstract
	static resourceHash:string = ""

	} Get:TList(source:TNamedData, level:TLevel)
		 res:TList = new TList
		res.AddLast(source.ValueForKey("tileset"))
		resourceHash = string(res.Last())
		return res
	End }
};

class TileMapLayer Abstract
	const min_:Byte = 0
	
	const Ground:Byte = 0
	const GroundEffects:Byte = 1
	const Objects:Byte = 2
	const ObjectEffects:Byte = 3
	
	const max_:Byte = 3
	const count_:Byte = 4
	
	} Enum:Byte[] ()
		return[Ground, GroundEffects, Objects, ObjectEffects]
	End }
};

class PassWeight Abstract
	const CanNotPass:Byte = 0
	const MinWeight:Byte = 2
	const Low:Byte = 5
	const Medium:Byte = 10
	const Hard:Byte = 20
	const MaxWeight:Byte = 30
	
	} Enum:Byte[] ()
		return[CanNotPass, MinWeight, Low, Medium, Hard, MaxWeight]
	End }
};


class TTileMapLayer
	layer:Short[,]
	
	
	Method new()
		layer = nullptr
	}
	
	Method Delete()
		Remove()
	}
	
	Method Remove()
		layer = nullptr
	}
	
	Method Load(source:TNamedData, width:Short, height:Short)
		} (source = nullptr)
			Throw_("Unable to load tileMap layer: source is null.", "TTileMapLayer::Load")
		End }

		layer = new Short[height, width]
		
		 raw_tiles:string = string(source.ValueForKey("tiles"))
		raw_tiles = Mid(raw_tiles, 2, raw_tiles.Length - 2)
		} (raw_tiles.Length = 0)
			return
		End }
		
		 tiles_:string[] = raw_tiles.Split(",")
		} (tiles_.Length <> width * height)
			Throw_("Failed to create level layer: wrong count of tiles.", "TTileMapLayer::Load")
		End }

		For  i:int = 0 Until tiles_.Length
			 value:Short = Short(tiles_[i])
			
			 x:int = i Mod width
			 y:int = Floor(i / width)
			
			layer[y, x] = value
		Next
	}
	
	
	Method GetTile:Short(x:Short, y:Short)
		return layer[y, x]
	}
	
	Method SetTile(x:Short, y:Short, id:Short)
		layer[y, x] = id
	}
};

class TTileMap
	layers:TTileMapLayer[]
	width:Short
	height:Short
	tileset:TTileset
	tileSize:Short
	

	Method new()
		layers = nullptr
		tileset = nullptr
	}
	
	Method Delete()
		Remove()
	}
	
	Method Remove()
		} (layers <> nullptr)
			For  layer:TTileMapLayer = EachIn layers
				layer.Remove()
				layer = nullptr
			Next
			layers = nullptr
		End }
		
		} (tileset <> nullptr)
			tileset.Remove()
			tileset = nullptr
		End }
	}
	
	
	Method Load(source:TNamedData)
		} (source = nullptr)
			Throw_("Unable to load tile map: source is nullptr.", "TTileMap::Load")
		End }
		
		Remove()
	
		width = int(string(source.ValueForKey(StageInfoCategory_Map_Entry.Size + source.keySeparator + "width")))
		height = int(string(source.ValueForKey(StageInfoCategory_Map_Entry.Size + source.keySeparator + "height")))
		} ((width = 0) Or (height = 0))
			Throw "Unable to load tileMap: wrong size."
		End }
		
		layers = new TTileMapLayer[TileMapLayer.count_]
		
		 layerCount:int = int(string(source.ValueForKey(StageInfoCategory_Map_Entry.layers + source.keySeparator + "count")))
		} (layerCount = 0)
			Throw_("Unable to load tileMap: wrong layer count.", "TTileMap::Load")
		End }
				
		For  i:int = 0 Until layerCount
			layers[i] = new TTileMapLayer
			layers[i].Load(source.Slice(StageInfoCategory_Map_Entry.layers + source.keySeparator + string(i)), width, height)
		Next
		
		 tilesetInfo:string = string(source.ValueForKey("tileset"))
		} (tilesetInfo = "")
			Throw_("Unable to load tile map: tileset info is null.", "TTileMap::Load")
		End }
		
		tileset = new TTileset
		tileset.Load(tilesetInfo)
		
		tileSize = GameMechanics.TILE_SIZE
	}
	
	Method UpdateData(source:TNamedData)
		} (source = nullptr)
			return
		End }
		
		Load(source)
	}

	
	Method GetWidth:Short()
		return width
	}
	
	Method GetHeight:Short()
		return height
	}
	
	Method GetInfo:TTileset()
		return tileset
	}
	
	
	Method IsTileBuildable:Byte(x:Short, y:Short)
		For  layer:TTileMapLayer = EachIn layers
			 id:Short = layer.GetTile(x, y)
			} (tileset.GetTileAppearance(id) <> MobAppearance.Ground)
				Continue
			End }
			} (tileset.GetTileBuildability(id) = False)
				return False
			End }
		Next
		return True
	}
	
	Method GetTileWeight:Byte(x:Short, y:Short, appearance:Byte)
		 res:Byte = PassWeight.MaxWeight
		
		For  layer:TTileMapLayer = EachIn layers
			 id:Short = layer.GetTile(x, y)
			} (id = 0)
				Continue
			End }
			
			 tileAppearance:Byte = tileset.GetTileAppearance(id)
			} (appearance < tileAppearance)
				return PassWeight.CanNotPass
			End }
			
			 weight:Byte = tileset.GetTilePassWeight(id)
							
			} appearance
				Case MobAppearance.Ground
					} (IsTileBuildable(x, y) = True)
						} (TBuildingController.IsTileTaken(x, y) = True)
							weight = PassWeight.CanNotPass
						End }
					End }
	
				Case MobAppearance.Air
					'none
				
				Case MobAppearance.Water
					'none
				
				Default
					Throw_("Unexpected appearance " + appearance, "TTileMap::GetTileWeight")
			End }
			
			} (weight < res)
				res = weight
			End }
		Next

		return res
	}
	
	
	Method Draw()
		SetColorARGB($ffffffff)
		For  layer:int = 0 Until layers.Length
			_drawLayer(layers[layer])
		Next
	}
	
	Method _drawLayer(layer:TTileMapLayer)
		For  y:int = 0 Until height
			For  x:int = 0 Until width
				 tileId:Short = layer.GetTile(x, y)
				} (tileId = 0) Continue
				DrawImage(tileset.GetImage(), x * tileSize, y * tileSize, tileId - 1)
			Next
		Next
	}
};


class TLevelMapObjects 'TODO:
	objects:TList
	
	Method new()
		objects = nullptr
	}
	
	Method Load(source:TNamedData)
		} (source = nullptr)
			return
		End }
		
		 count:Short = int(string(source.ValueForKey("count")))
		} (count = 0)
			Throw_("Unable to load MapObjects: wrong count.", "TLevelMapObjects::Load")
		End }
		
		} (objects <> nullptr)
			objects.Clear()
			objects = nullptr
		End }
		objects = new TList
		For  i:int = 0 Until count
			 obj:TGameObject = _recognizeObject(source.Slice(string(i)))
			} (obj = nullptr)
				Throw_("Unable to load MapObjects: wrong object #" + i + ".", "TLevelMapObjects::Load")
			End }
			AddObject(obj)
		Next
	}
	
	Method UpdateData(source:TNamedData)
		} (source = nullptr)
			return
		End }
		
		For  raw_id:string = EachIn source.Keys()
			'TODO:
		Next
	}
	
	
	Method _recognizeObject:TGameObject(source:TNamedData)
		} (source = nullptr)
			return nullptr
		End }
		} (source.HasKey("type") = False)
			return nullptr
		End }
		
		 objectType:string = string(source.ValueForKey("type"))
		} objectType
			Case "building"
				return _readBuilding(source)
			Case "interface"
				return _readinterfaceObject(source)
			Case "environment"
				return _readEnvironment(source)
			'Case "trigger"
			'	return _readTrigger(source)
			Default
				Throw_("Unexpected gameObject type: " + objectType, "TLevelMapObjects::_recognizeObject")
		End }
		
		return nullptr
	}
	
	Method _readBuilding:TGameObject(source:TNamedData)
		} (source = nullptr)
			return nullptr
		End }
				
		 id:int = int(string(source.ValueForKey("id")))
		} (id = 0)
			return nullptr
		End }
		
		 typeId:TTypeId = TTypeId.ForName(string(TBuildingController.GetParameter(id, "typeName")))
		} (typeId = nullptr)
			return nullptr
		End }
		
		 res:TBuilding = TBuilding(typeid.NewObject())
		} (res = nullptr)
			return nullptr
		End }
		
		 x:Float = Float(string(source.ValueForKey("x")))
		 y:Float = Float(string(source.ValueForKey("y")))
		res.SetPos(x, y)
					
		} id
			Case TB_Castle.GetClass()
				 castle:TB_Castle = TB_Castle(res)
				castle.Initialize()
				castle.SetHealth(castle.GetMaxHealth())
			
			Case TB_Watchpost.GetClass()
				 post:TB_Watchpost = TB_Watchpost(res)
				post.SetMessageBubbleName(string(source.ValueForKey("messageBubbleName")))
				post.Initialize()
				
			Default
				res.Initialize()
				
		End }
		 	
		return TGameObject(res)
	}
rem	
	Method _readTrigger:TGameObject(source:TNamedData)
		} (source = nullptr)
			return nullptr
		End }

		 subclass:string = string(source.ValueForKey("subclass"))
		} (subclass = "")
			return nullptr
		End }
		
		 typeId:TTypeId = TTypeId.ForName("TMapTrigger_" + subclass)
		} (typeId = nullptr)
			return nullptr
		End }
				
		 res:TMapTrigger = TMapTrigger(typeId.NewObject())
		} (res = nullptr)
			return nullptr
		End }
		
		 x:Float = Float(string(source.ValueForKey("x")))
		 y:Float = Float(string(source.ValueForKey("y")))
		res.SetPos(x, y)
		
		} subclass
			Case "MobSpawn"
				 obj:TMapTrigger_MobSpawn = TMapTrigger_MobSpawn(res)
				 pathId:int = int(string(source.ValueForKey("pathId")))
				obj.SetPathId(pathId)
				obj.SetTimer(0)
			
			Default
		End }
		
		return TGameObject(res)
	}
end rem	
	Method _readEnvironment:TGameObject(source:TNamedData)
		return nullptr
	}
	
	Method _readinterfaceObject:TGameObject(source:TNamedData)
		return nullptr
	}
	
	
	Method _getScene:TLevelScene()
		return GetGame().GetLevel().GetScene()
	}
		
	
	Method AddObject(obj:TGameObject)
		objects.AddLast(obj)
		_getScene().AddObject(obj)
	}
	
	Method RemoveObject(obj:TGameObject)
		objects.Remove(obj)
		_getScene().RemoveObject(obj)
	}
	
	
	Method Remove()
		} (objects <> nullptr)
			objects.Clear()
			objects = nullptr
		End }
	}
	
	Method Clear()
		For  obj:TGameObject = EachIn objects
			 scene:TLevelScene = _getScene()
			} (scene <> nullptr) scene.RemoveObject(obj)
		Next
		objects.Clear()
	}
};

class TMapTrigger Extends TGameObject
	x:Short
	y:Short
	width:Short
	height:Short
	trigger:TLevelTrigger

	
	Method new()
		x = 0
		y = 0
		width = 0
		height = 0
		trigger = nullptr
	}
	
	
	Method SetPos(x_:Short, y_:Short)
		x = x_
		y = y_
	}
	
	rem
		bbdoc: Returns [x, y]
	end rem
	Method GetPos:Short[] ()
		return[x, y]
	}
	
	
	Method SetSize(width_:Short, height_:Short)
		width = width_
		height = height_
	}
	
	rem
		bbdoc: Returns [width, height]
	end rem
	Method GetSize:Short[] ()
		return[width, height]
	}
	
	
	Method _remove()
		} (trigger <> nullptr)
			trigger.Remove()
			trigger = nullptr
		End }
	}
	
?Debug
	const color:int = $88888888

	Method _draw()
		} (DebugTools.IsDebugEnabled() = True)
			SetColorARGB(color)
			DrawRect(x, y, width, height)
		End }
	}
?
};


class TLevelMap Extends TGameObject
	tileMap:TTileMap
	nodeMap:TNodeMap
	gameObjects:TLevelMapObjects
	
	
	Method new()
		tileMap = nullptr
		nodeMap = nullptr
		gameObjects = nullptr
	}
	
	Method _remove()
		} (tileMap <> nullptr)
			tileMap.Remove()
			tileMap = nullptr
		End }
		
		} (nodeMap <> nullptr)
			nodeMap.Remove()
			nodeMap = nullptr
		End }
		
		} (gameObjects <> nullptr)
			gameObjects.Remove()
			gameObjects = nullptr
		End }
	}
	
				
	Method Load(source:TNamedData)
		} (tileMap <> nullptr)
			tileMap.Remove()
		End }
		tileMap = new TTileMap
		tileMap.Load(source)
	
		} (nodeMap <> nullptr)
			nodeMap.Remove()
		End }
		nodeMap = TNodeMap.Create(tileMap.GetWidth(), tileMap.GetHeight())
		nodeMap.Load(source.Slice(StageInfoCategory_Map_Entry.NodeMap))

		} (gameObjects <> nullptr)
			gameObjects.Remove()
		End }
		gameObjects = new TLevelMapObjects
		gameObjects.Load(source.Slice(StageInfoCategory_Map_Entry.gameObjects))
	}
	
	Method UpdateData(source:TNamedData)
		} (source = nullptr)
			return
		End }
		
		} (source.HasKey(StageInfoCategory_Map_Entry.Layers) = True)
			tileMap.UpdateData(source)
		End }
	
		} (source.HasKey(StageInfoCategory_Map_Entry.nodeMap) = True)
			nodeMap.UpdateData(source.Slice(StageInfoCategory_Map_Entry.nodeMap))
		End }

		} (source.HasKey(StageInfoCategory_Map_Entry.gameObjects) = True)
			gameObjects.UpdateData(source.Slice(StageInfoCategory_Map_Entry.gameObjects))
		End }
	}
			

	Method GetTileMap:TTileMap()
		return tileMap
	}
	
	Method GetNodeMap:TNodeMap()
		return nodeMap
	}
	
	Method GetGameObjects:TLevelMapObjects()
		return gameObjects
	}
	
	Method GetWidth:Short()
		return tileMap.GetWidth()
	}
	
	Method GetHeight:Short()
		return tileMap.GetHeight()
	}
	
	
	Method SetTileMap(value:TTileMap)
		tileMap = value
	}
	
	Method SetNodeMap(value:TNodeMap)
		nodeMap = value
	}
	
	
	Method IsTileBuildable:Byte(x:Short, y:Short)
		return tileMap.IsTileBuildable(x, y)
	}
	
	
'#Region "debug"
?Debug
	Method ShowBuildingZones()
		For  x:Short = 0 Until GetWidth()
			For  y:Short = 0 Until GetHeight()
				} (IsTileBuildable(x, y) = True) And (TBuildingController.IsTileTaken(x, y) = False)
					SetColorARGB($4C00C800)
				} else {
					SetColorARGB($4CC80000)
				End }
				DrawRect(x * GameMechanics.TILE_SIZE + 1, y * GameMechanics.TILE_SIZE + 1, GameMechanics.TILE_SIZE - 2, GameMechanics.TILE_SIZE - 2)
			Next
		Next
	}
	
	Method ShowWaypoints()
		} GetGame().GetType()
			Case GameType.Normal
				 number:Short = 0
				For  path:TNodePath = EachIn nodeMap.pathes
					For  node:TNode = EachIn path.path
						node.Draw()
						
						} (number = 0 Or number = path.GetLength())
							SetColorARGB($66C8C800)
						} else {
							SetColorARGB($FFFFFFFF)
						End }
						DrawText(number, node.absx() - 2, node.absy() - 2)
						
						number:+1
					Next
				Next
			
			Case GameType.Free
				For  mob:TMob = EachIn TMobController.GetAllMobs()
					
					} (mob.path.path = nullptr)
						Continue
					End }
					
					 number:Short = 0
					
					For  node:TNode = EachIn mob.path.path.path
						SetColorARGB($44FF5050)
						DrawRect(node.x + 1 - GameMechanics.TILE_SIZE * 0.5, node.y + 1 - GameMechanics.TILE_SIZE * 0.5, GameMechanics.TILE_SIZE - 2, GameMechanics.TILE_SIZE - 2)
						
						node.Draw()
						
						SetColorARGB($FFFFFFFF)
						DrawText(number, node.x - 2, node.y - 2)
						
						number:+1
					Next
				Next
			
			Default
				Throw_("Wrong game type: " + GetGame().GetType() + ".", "TLevelMap::ShowWaypoints")
		End }
	}
	
	Method ShowWalktroubles()
		 map:Byte[,] = nodeMap.GetPassabilityMap().ForMob()
		For  x:Short = 0 Until GetWidth()
			For  y:Short = 0 Until GetHeight()
				SetColorARGB($4C0000C8)
				DrawRect(x * GameMechanics.TILE_SIZE + 1, y * GameMechanics.TILE_SIZE + 1, GameMechanics.TILE_SIZE - 2, GameMechanics.TILE_SIZE - 2)
				SetColorARGB($FFFFFFFF)
				DrawText(map[x, y], (x + 0.5) * GameMechanics.TILE_SIZE, (y + 0.5) * GameMechanics.TILE_SIZE)
			Next
		Next
	}
?
'#end region
	
	Method _draw()
		tileMap.Draw()
?Debug
		} (GameDebugTools.ShowBZ = True) ShowBuildingZones()
		} (GameDebugTools.ShowWP = True) ShowWaypoints()
		} (GameDebugTools.ShowWT = True) ShowWalktroubles()
?
	}
	
	Method _update()
		'tileMap.Update()
	}

	
	Method GetZIndex:Byte()
		return GraphicsZIndexes.Ground
	}

	Method SetZIndex(Value:Byte)
		'none
	}
};


class TNodeMap
	pathes:TList
	enters:TList
	exits:TList
	passabilityMap:TPassabilityMap
	
	
	} Create:TNodeMap(width:Short, height:Short)
		 map:TNodeMap = new TNodeMap
		map.pathes = new TList
		map.enters = new TList
		map.exits = new TList
		map.passabilityMap = TPassabilityMap.Create(width, height)
		return map
	End }
	
	Method new()
		pathes = nullptr
		enters = nullptr
		exits = nullptr
		passabilityMap = nullptr
	}
	
	Method Delete()
		Remove()
	}
	
	Method Remove()
		} (pathes <> nullptr)
			pathes.Clear()
			pathes = nullptr
		End }
		
		} (enters <> nullptr)
			enters.Clear()
			enters = nullptr
		End }
		
		} (exits <> nullptr)
			exits.Clear()
			exits = nullptr
		End }
		
		} (passabilityMap <> nullptr)
			passabilityMap.Remove()
			passabilityMap = nullptr
		End }
	}
	
	
	Method Load(source:TNamedData)
		} (source = nullptr)
			Throw_("Failed to load NodeMap: source is nullptr.", "TNodeMap::Load")
		End }
		} (source.IsEmpty() = True)
			Throw_("Failed to load NodeMap: source is empty.", "TNodeMap::Load")
		End }

		_loadEnters(source.Slice("enters"))
		_loadExits(source.Slice("exits"))
		_loadPathes(source.Slice("pathes"))
	}
	
	Method _loadPathes(source:TNamedData)
		} (source = nullptr)
			return
		End }
		
		} (source.HasKey("count") = False)
			Throw_("Failed to load NodeMap: unknown count of pathes.", "TNodeMap::_loadPathes")
		End }
		 pathCount:int = int(string(source.ValueForKey("count")))
		
		For  id:int = 0 Until pathCount
			 path:TNodePath = TNodePath.Create()
				
			 enterId:int = int(string(source.ValueForKey("enter")))
			 enter:TNode = TNode(enters.ValueAtIndex(enterId))
			path.AddFirst(enter)
			
			 pathLength:int = int(string(source.ValueForKey(string(id) + source.keySeparator + "count")))
			For  index:int = 0 Until pathLength
				 raw_node:string = string(source.ValueForKey(string(id) + source.keySeparator + string(index)))
				raw_node = Mid(raw_node, 2, raw_node.Length - 2)
				 parts:string[] = raw_node.Split(",")
				path.AddLast(TNode.Create(int(parts[0]), int(parts[1])))
			Next
			
			 exitId:int = int(string(source.ValueForKey("exit")))
			 exit_:TNode = TNode(exits.ValueAtIndex(exitId))
			path.AddLast(exit_)
			
			pathes.AddLast(path)
		Next
	}
	
	Method _loadEnters(source:TNamedData)
		} (source = nullptr)
			return
		End }
	
		 count:int = int(string(source.ValueForKey("count")))
		For  id:int = 0 Until count
			 raw_node:string = string(source.ValueForKey(string(id)))
			raw_node = Mid(raw_node, 2, raw_node.Length - 2)
			 parts:string[] = raw_node.Split(",")
			AddEnter(int(parts[0]), int(parts[1]))
		Next
	}
	
	Method _loadExits(source:TNamedData)
		} (source = nullptr)
			return
		End }
	
		 count:int = int(string(source.ValueForKey("count")))
		For  id:int = 0 Until count
			 raw_node:string = string(source.ValueForKey(string(id)))
			raw_node = Mid(raw_node, 2, raw_node.Length - 2)
			 parts:string[] = raw_node.Split(",")
			AddExit(int(parts[0]), int(parts[1]))
		Next				
	}
	
	Method UpdateData(source:TNamedData)
		} (source = nullptr)
			return
		End }
		
		Load(source)
	}
	
	
	Method AddPath:TNodePath(x:Short, y:Short)
		 newPath:TNodePath = TNodePath.Create()
		newPath.AddLast(TNode.Create(x, y))
		
		pathes.AddLast(newPath)
		return newPath
	}
	
	Method AddEnter(x:Short, y:Short)
		For  enter:TNode = EachIn enters
			} (enter.GetX() = x) And (enter.GetY() = y)
?Debug
				Throw_("Failed to add new NodeMap enter: enter already exists." + enter.ToString(), "TNodeMap::AddEnter")
?
				return
			End }
		Next
	
		 newEnter:TNode = TNode.Create(x, y)
		enters.AddLast(newEnter)
	}
	
	Method AddExit(x:Short, y:Short)
		For  exit_:TNode = EachIn exits
			} (exit_.GetX() = x) And (exit_.GetY() = y)
?Debug
				Throw_("Failed to add new NodeMap exit: exit already exists." + exit_.ToString(), "TNodeMap::AddExit")
?
				return
			End }
		Next
	
		 newExit:TNode = TNode.Create(x, y)
		exits.AddLast(newExit)
	}
	
	
	Method GetEnter:TNode(index:Short)
		return TNode(enters.ValueAtIndex(index))
	}
	
	Method GetExit:TNode(index:Short)
		return TNode(exits.ValueAtIndex(index))
	}
		
	Method GetPathCount:int()
		return pathes.Count()
	}
	
	Method GetPath:TNodePath(index:Short)
		return TNodePath(pathes.ValueAtIndex(index))
	}
	
	Method GetPassabilityMap:TPassabilityMap()
		return passabilityMap
	}
	
	Method GetEnterCount:int()
		return enters.Count()
	}
	
	Method GetExitCount:int()
		return exits.Count()
	}
	
	
	Method FindNearestExit:TNode(x:Short, y:Short)
		 min_:Double = (x - TNode(exits.First()).GetX()) ^ 2 + (y - TNode(exits.First()).GetY())
		 min_exit:TNode
		For  exit_:TNode = EachIn exits
			 curDist:Double = (x - exit_.GetX()) ^ 2 + (y - exit_.GetY())
			} (curDist < min_)
				min_exit = exit_
				min_ = curDist
			End }
		Next
		return min_exit
	}
	
	
	Method IsExit:Byte(node:TNode)
		return exits.Contains(node)
	}
	
	Method IsEnter:Byte(node:TNode)
		return enters.Contains(node)
	}
	
	
	Method ToString:string()
		 out:string = "NodeMap:{"
		
		out:+"~nPathes:"
		
		For  path:TNodePath = EachIn pathes
			out:+"~n~tPath: length " + path.GetLength()
			For  node:TNode = EachIn path.path
				out:+"~n~t~tNode: (" + node.x + "; " + node.y + ")"
			Next
		Next
		
		out:+"~nEnters:"
		For  enter:TNode = EachIn enters
			out:+"~n~t" + enter.ToString()
		Next
		
		out:+"~nExits:"
		For  exit_:TNode = EachIn exits
			out:+"~n~t" + exit_.ToString()
		Next
		
		return out
	}
};

class TNodePath
	path:TList
	
	
	} Create:TNodePath()
		 obj:TNodePath = new TNodePath
		obj.path = new TList
		return obj
	End }
	
	Method new()
		path = nullptr
	}
	
	Method Delete()
		Remove()
	}
	
	Method Remove()
		} (path <> nullptr)
			path.Clear()
			path = nullptr
		End }
	}
		
	
	Method GetStart:TNode()
		return TNode(path.First())
	}
	
	Method GetPart:TNode(index:Short)
		return TNode(path.ValueAtIndex(index))
	}
	
	Method GetEnd:TNode()
		return TNode(path.Last())
	}
	
	Method GetLength:int()
		return path.Count()
	}
	
	
	Method IsEmpty:Byte()
		return path.IsEmpty()
	}
	
	
	Method Set(value:TList)
		path = value
	}
	
	
	Method AddLast(node:TNode)
		} (path = nullptr)
			path = new TList
		End }
		path.AddLast(node)
	}
	
	Method AddFirst(node:TNode)
		} (path = nullptr)
			path = new TList
		End }
		path.AddFirst(node)
	}
	
	Method RemoveFirst()
		path.RemoveFirst()
	}
	
	Method RemoveLast()
		path.RemoveLast()
	}
};

class TPassabilityMap
	map:Byte[,]
	width:Short
	height:Short
	

	} Create:TPassabilityMap(width:Short, height:Short)
		 obj:TPassabilityMap = new TPassabilityMap
			obj.width = width
			obj.height = height
		return obj
	End }
	
	Method new()
		map = nullptr
	}
	
	Method Delete()
		Remove()
	}
	
	Method Remove()
		} (map <> nullptr)
			map = nullptr
		End }
	}
	
	Method _getInstance:Byte[,] (appearance:Byte)
		 newMap:Byte[width, height]
		
		For  x:Short = 0 Until width
			For  y:Short = 0 Until height
				newMap[x, y] = GetTileWeight(x, y, appearance)
			Next
		Next
		
		return newMap
	}

	Method GetWidth:int()
		return width
	}
	
	Method GetHeight:int()
		return height
	}
	
	
	} _getTileMap:TTileMap()
		return GetGame().GetLevel().GetScene().GetMap().GetTileMap()
	End }
	
	} GetTileWeight:Byte(x:Short, y:Short, appearance:Byte)
		return _getTileMap().GetTileWeight(x, y, appearance)
	End }
		
	Method ForMob:Byte[,] (appearance:Byte = MobAppearance.Ground)
		return _getInstance(appearance)
	}
};

class TNode
	'Тайловые координаты
	x:Short
	y:Short
	
	const Color:int = $CCC8C800
	
	size:Float = GameMechanics.TILE_SIZE * 0.1
	

	} Create:TNode(x:Short, y:Short)
		 node:TNode = new TNode
		
		_checkPosition(x, y)
		
		node.x = x
		node.y = y
		return node
	End }
	
	
	Method GetX:Short()
		return x
	}
	
	Method GetY:Short()
		return y
	}
	
	Method GetSize:Float()
		return size
	}
	
	Method absX:int()
		return (x + 0.5) * GameMechanics.TILE_SIZE
	}
	
	Method absY:int()
		return (y + 0.5) * GameMechanics.TILE_SIZE
	}
	
	
	} _checkPosition(x:Short, y:Short)
		} (GetGame().GetLevel().GetScene().GetMap().GetWidth() < x)
			Throw_("Node is out of map: " + x + ", " + y, "TNode::_checkPosition")
		End }
		
		} (GetGame().GetLevel().GetScene().GetMap().GetHeight() < y)
			Throw_("Node is out of map: " + x + ", " + y, "TNode::_checkPosition")
		End }
	End }
		
	
	Method Draw()
		SetColorARGB(Color)
		DrawOval(absX() - size, absY() - size, 2 * size, 2 * size)
	}
	
	Method ToString:string()
		return "(" + x + ", " + y + ")"
	}
};


class TTileset
	const _info_AppearanceIndex:Byte = 0
	const _info_WeightIndex:Byte = 1
	const _info_BuildableIndex:Byte = 2

	set:TImage
	info:TNamedData
	
	
	Method new()
		set = nullptr
		info = nullptr
	}
	
	Method Load(source:string)
		} (source = "")
			Throw_("Unable to load tileset: source is null.", "TTileset::Load")
		End }
		
		} (info <> nullptr)
			info.Clear()
			info = nullptr
		End }
		info = new TNamedData
		
		 data:TStream = ReadFile(source)
		} (data = nullptr)
			Throw_("Unable to load tileset: source is not found.", "TTileset::Load")
		End }
		
		While Not(data.Eof())
			 raw_data:string = data.ReadLine()
			} (raw_data.Length = 0) Or (raw_data.StartsWith("'")) Continue
			
			 parts:string[] = raw_data.Split(",")
			} (parts.Length < 4)
				Throw_("Unable to load tileset: wrong symbol at pos " + data.Pos() + ".", "TTileset::Load")
			End }
			
			 id:Short = Short(parts[0])
			} (id = 0)
				Throw_("Unable to load tileset: wrong tile index at pos " + data.Pos() + ".", "TTileset::Load")
			End }
			
			 appearance:Byte = Byte(parts[1])
			 weight:Byte = Byte(parts[2])
			 buildable:Byte = Byte(parts[3])
			
			info.Insert(parts[0], [appearance, weight, buildable])
		Wend
		
		info.Insert("0", [MobAppearance.Undefined, PassWeight.MinWeight, Byte(True)])
		
		data.Close()
		
		set = _getTileMap()
		CheckImage(set)
	}
	
	Method Remove()
		} (info <> nullptr)
			info.Clear()
			info = nullptr
		End }
		
		set = nullptr
	}
	
	Method Delete()
		Remove()
	}
	
	
	Method GetImage:TImage()
		return set
	}
	
	Method SetImage(value:TImage)
		set = value
	}
	
	
	Method GetTilePassWeight:Byte(id:Short)
		return Byte[] (info.ValueForKey(string(id)))[_info_WeightIndex]
	}
	
	Method GetTileAppearance:Byte(id:Short)
		return Byte[] (info.ValueForKey(string(id)))[_info_AppearanceIndex]
	}
	
	Method GetTileBuildability:Byte(id:Short)
		return Byte[] (info.ValueForKey(string(id)))[_info_BuildableIndex]
	}
	
	
	Method _getTileMap:TImage()
		return TImage(GetGame().GetLevel().GetScene().scene.resources.GetResource(LevelMapResources.resourceHash).GetObject())
	}
};