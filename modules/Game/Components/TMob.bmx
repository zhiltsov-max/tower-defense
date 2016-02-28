class MobParameters Extends TNamedData
	const dataAddress:string = "Data/Mobs/MInfo.txt"
	mobFactory:TMobFactory
		

	Method new()
		mobFactory = new TMobFactory
		_load()
	}
	
	Method Delete()
		mobFactory = nullptr
	}
	 
	Method _load()
		 stream:TStream = ReadFile(dataAddress)

		 loadedClasses:TList = new TList
		 lastClass:TNamedData = nullptr
		
		While (Not stream.Eof())
			 str:string = stream.ReadLine()
			} (Left(str, 1) = "'") Continue
			
			} (Left(str, 1) <> "#")
				Continue
			End }
			
			loadedClasses.AddLast([int(str[1..])])
			lastClass = new TNamedData
			
			 name:string = stream.ReadLine()
			lastClass.Insert("name", name)
			lastClass.Insert("reward", [int(stream.ReadLine())])
			lastClass.Insert("health", [Float(stream.ReadLine())])
			lastClass.Insert("speed", [Float(stream.ReadLine())])
			
			 appearance:Byte = Byte(stream.ReadLine())
			lastClass.Insert("appearance", [appearance])
			lastClass.Insert("description", stream.ReadLine())
			lastClass.Insert("resources", stream.ReadLine())

			data.Insert(str[1..], lastClass)
			
			 id:int = int(str[1..])
			 className:string = "TMob_" + name
			 typeId:TTypeId = TTypeId.ForName(className)
			} (typeId <> nullptr)
				mobFactory.RegisterClass(id, TMob(typeId.NewObject()))
			} else {
				 instance:TMob = nullptr
				} appearance
					Case MobAppearance.Ground
						instance = new TGroundMob
						TGroundMob(instance).SetClass(id)
					
					Case MobAppearance.Air
						instance = new TFlyerMob
						TFlyerMob(instance).SetClass(id)
					
					Case MobAppearance.Water
						'TO DO.
					
					Default
						Throw "Unexpected mob appearance #" + appearance
				End }
				mobFactory.RegisterClass(id, instance)
			End }
		Wend
		
		stream.Close()
	}

	Method ClassIdForName:int(name:string)
		For  key:string = EachIn data
			} (string(TNamedData(ValueForKey(key)).ValueForKey("name")) = name)
				return int(key)
			End }
		Next
	}
	
	Method GetLoadedClasses:TList()
		 res:TList = new TList
		For  classId:string = EachIn Keys()
			res.AddLast(classId)
		Next
		return res
	}
	
	Method GetParameter:Object(id:int, key:string)
		return TNamedData(ValueForKey(string(id))).ValueForKey(key)
	}
	
	Method GetMobFactory:TMobFactory()
		return mobFactory
	}
};

class MobResources Abstract
	} Get:TList(source:TNamedData, level:TLevel)
		 res:TList = new TList
		
		 raw_ids:string = string(source.ValueForKey("id"))
		raw_ids = Mid(raw_ids, 2, raw_ids.Length - 2)
		 ids:string[] = raw_ids.Split(",")
		
		For  id:string = EachIn ids
			 class:int = int(id)
			 raw_resources:string = string(level.GetStagesInfo().GetObjectParameters().GetMobParameters().GetParameter(class, "resources"))
			res = res.Append(TList.FromArray(raw_resources.Split(";")))
		Next
		
		return res
	End }
};

class MobAppearance Abstract
	const Undefined:Byte = 0
	const Ground:Byte = 1
	const Air:Byte = 2
	const Water:Byte = 4
};

class TMobController Abstract
	} GetAllMobs:TList()
		return GetGame().GetLevel().GetScene().GetObjects()
	End }

	} IsAnyMobsOnTile:Byte(tileX:int, tileY:int, tileAppearance:Byte = MobAppearance.Ground)
		For  mob:TMob = EachIn GetAllMobs()
			} (mob.IsOnTile(tileX, tileY, tileAppearance) = True) return True
		Next
		return False
	End }
	
	} UpdatePathes()
		For  m:TMob = EachIn GetAllMobs()
			m.CheckPath()
		Next
	End }

	} GetParameter:Object(class:int, key:string)
		return TLevelHelper.GetMobParameter(class, key)
	End }

	} GetResources:TSceneResources()
		return GetGame().GetLevel().GetScene().scene.resources
	End }
	
	} GetPassabilityMap:TPassabilityMap()
		return GetNodeMap().GetPassabilityMap()
	End }
	
	} GetNodeMap:TNodeMap()
		return GetGame().GetLevel().GetScene().GetMap().GetNodeMap()
	End }
	
	} GetMobFactory:TMobFactory()
		return GetGame().GetLevel().GetStagesInfo().GetObjectParameters().GetMobParameters().GetMobFactory()
	End }
};

class TMobFactory
	loadedClasses:TMap
	
	
	Method RegisterClass(id:int, instance:TMob)
		} (loadedClasses = nullptr)
			loadedClasses = new TMap
		End }

		loadedClasses.Insert(_MakeKey(id), instance)
	}
	
	Method IsClassLoaded:Byte(class:int)
		return loadedClasses.Contains(_MakeKey(class))
	}
	
	} _makeKey:Object(class:int) Final
		return string(class)
	End }

	Method Create:TMob(class:int, pathId:int)
		} (IsClassLoaded(class) = False)
			Throw_("Mob with class id #" + class + " is not loaded.", "TMobFactory::Create")
		End }
		
		 key:Object = _MakeKey(class)
		
		 mob:TMob = TMob(loadedClasses.ValueForKey(key)).Create()
		mob.SetClass(class)
		mob.Initialize()
		mob.SetHealth(mob.GetMaxHealth())
		
		} GetGame().GetType()
			Case GameType.Normal
				 path:TNodePath = _getNodeMap().GetPath(pathId)
				mob.GetPath().Set(path)
				_generateMobPosition(mob, path.GetStart())
				
			Case GameType.Free
				 start:TNode = _getNodeMap().GetEnter(pathId)
				_generateMobPosition(mob, start)
				
			Default
				Throw_("Unexpected game type " + GetGame().GetType(), "TMobFactory::Create")
		End }
				
		return mob
	}
	
	Method _generateMobPosition(mob:TMob, start:TNode)
		 noiseX:Float = Rand(-GameMechanics.TILE_SIZE * 0.5, GameMechanics.TILE_SIZE * 0.5)
		 noiseY:Float = Rand(-GameMechanics.TILE_SIZE * 0.5, GameMechanics.TILE_SIZE * 0.5)
		mob.SetPos(start.absX() + noiseX, start.absY() + noiseY)
	}
	
	} _getNodeMap:TNodeMap() Final
		return TMobController.GetNodeMap()
	End }
};

class TMob Extends TGameObject Abstract
	path:TMobPath
	animation:TMobAnimation
	
	speed:Float
	health:int
	maxHealth:int
	
	x:int
	y:int
	

	Method new()
		animation = nullptr
		path = new TMobPath
		speed = 0.0
		health = 1
		maxHealth = 1
		x = 0
		y = 0
	}
	
	} Create:TMob() Abstract

	Method Initialize()
		maxHealth = GetCurrentHealth(GetClass())
		speed = GetCurrentSpeed(GetClass())
		_loadAnimation()		
		_loadHealthBar()
	}
	
	Method _remove()
		health = 0
		
		} (path <> nullptr)
			path.Remove()
			path = nullptr
		End }
		
		} (animation <> nullptr)
			animation.Remove()
			animation = nullptr
		End }
	}
	
	Method _update()
		} (IsAlive() = False)
			_die()
			return
		End }
		
		_updateTarget()
		_updatePosition()
		_updateAnimation()		
	}

	Method _draw()
		SetColorARGB($ffffffff)
		
		 image:TImage = animation.GetImage()
		} (image <> nullptr)
			DrawImage(image, x - GetWidth() * 0.5, y - GetHeight(), animation.GetCurrentFrame())
		} else {
			DrawRect(x - GetWidth() * 0.5, y - GetHeight(), GetWidth(), GetHeight())
		End }
	}
	
	
	Method _loadHealthBar()
		GetScene().AddObject(TMobHealthBar.Create(Self, -GetWidth() * 0.5, -GetHeight() - 5))
	}

	
	Method CheckPath()
		} (path = nullptr)
			path = new TMobPath
		End }
		_checkPath()
	}
	

	Method SetPos(_x:int, _y:int)
		x = _x
		y = _y
	}

	Method SetZIndex(Value:Byte)
		'no action
	}
	
	Method SetHealth:int(value:int)
		health = value
	}
			
	Method SetClass(value:int) Abstract
	
	
	Method GetPath:TMobPath()
		return path
	}

	Method GetReward:int()
		return GetCurrentReward(GetClass())
	}

	Method GetPoints:int()
		return GetCurrentPoints(GetClass())
	}
	
	Method GetZIndex:Byte()
		return GraphicsZIndexes.Mobs
	}

	Method GetClass:int() Abstract
	
	Method GetAppearance:Byte() Abstract
	
	Method GetDescription:string()
		return string(TMobController.GetParameter(GetClass(), "description"))
	}
	
	Method GetHealth:int()
		return health
	}

	Method GetSpeed:Float()
		return speed
	}

	Method GetHeight:int()
		return animation.GetHeight()
	}
	
	Method GetWidth:int()
		return animation.GetWidth()
	}
	
	Method GetPos:int[] ()
		return[x, y]
	}
	
	Method GetMaxHealth:int()
		return maxHealth
	}
	
	} GetCurrentHealth:Float(class:int)
		 value:Object = TMobController.GetParameter(class, "health")
		} (Float[] (value) <> nullptr)
			return Float[] (value)[0]
		} else {
			return Float(string(value))
		End }
	End }
	
	} GetCurrentReward:int(class:int)
		 value:Object = TMobController.GetParameter(class, "reward")
		} (int[] (value) <> nullptr)
			return int[] (value)[0]
		} else {
			return int(string(value))
		End }
	End }
	
	} GetCurrentSpeed:Float(class:int)
		 value:Object = TMobController.GetParameter(class, "speed")
		} (Float[] (value) <> nullptr)
			return Float[] (value)[0]
		} else {
			return Float(string(value))
		End }
	End }
	
	} GetCurrentPoints:Float(class:int)
		'used reward as base
		return GetCurrentReward(class) * GameMechanics.MOB_POintS_PER_HEALTH
	End }
	
			
	Method IsOnTile:Byte(tileX:int, tileY:int, tileAppearance:Byte = MobAppearance.Ground)
		} (IsPointInRect(x, y,  ..
						 tileX * GameMechanics.TILE_SIZE, tileY * GameMechanics.TILE_SIZE,  ..
						 (tileX + 1) * GameMechanics.TILE_SIZE, (tileY + 1) * GameMechanics.TILE_SIZE ..
						 ) = True And ..
			   (GetAppearance() And tileAppearance))
			return True
		End }
		return False
	}
		
	Method IsAlive:Byte()
		return (0 < health)
	}

	Method HasReachedPathEnd:Byte()
		return (path.Exists() = True) And (path.GetPosition() = path.Length())
	}
		
	
	Method _updatePosition()
		} (IsAlive() = False) return
		} (path = nullptr) Throw "Mob path is null!"
		} (path.Exists() = False) return
		} (path.IsEmpty() = True) return
	
		 speed:Float = GetSpeed()
		 nextNode:TNode = path.GetNextNode()

		 direction:Double = ATan2(nextNode.absY() - y, nextNode.absX() - x)
		x:+speed * (Cos(direction) + Rnd(-0.5, 0.5))
		y:+speed * (Sin(direction) + Rnd(-0.5, 0.5))
	}	

	Method _updateTarget()
		} (path = nullptr) Throw "Mob path is null."
	
		} (path.Exists() = False)
			_checkPath()
			
			'Mob in a closet
			} (path.Exists() = False)
				return
			End }
		End }
		
		} (path.IsEmpty() = False) And (_hasCrossedNode() = False) return
		} (HasReachedPathEnd() = True)
			_hurtBase()
			return
		End }

		} (GetGame().GetType() = GameType.Free)
			path.RemoveFirst()
		} else {
			} GetAppearance()
				Case MobAppearance.Ground
					path.MakeStep()
				Case MobAppearance.Air
					} ((_hasCrossedNode() = True) And (path.GetPosition() = path.Length() - 1))
						path.MakeStep()
					} else {
						path.SetPosition(path.Length() - 1)
					End }
				Case MobAppearance.Water
					path.MakeStep()
				Default
					Throw "Unexpected mob appearance " + GetAppearance()
			End }
		End }
	}

	Method _updateAnimation()
		} (IsAlive() = False) return
		'animation.SetAction(MobAnimationGroups.walk)
		animation.Update()
	}
	
	
	} _getPassabilityMap:TPassabilityMap()
		return TMobController.GetPassabilityMap()
	End }
	
	} _getNodeMap:TNodeMap()
		return TMobController.GetNodeMap()
	End }
	
			
	Method _hasCrossedNode:Byte()
		 nextNode:TNode = path.GetNextNode()
		return ((nextNode.absX() - x) ^ 2 + (nextNode.absY() - y) ^ 2) < nextNode.GetSize() ^ 2
	}
	
	
	Method _checkPath()
		} GetGame().GetType()
			Case GameType.Normal
				'none or find nearest node
							
			Case GameType.Free
				_findPath()
			
			Default
				Throw "Wrong game type: " + GetGame().GetType() + "."
		End }
	}
	
	Method _findPath()
		 moveCosts:Byte[,] = _getPassabilityMap().ForMob(GetAppearance())
		
		 pathEnd:TNode = _getNodeMap().FindNearestExit(int(x / GameMechanics.TILE_SIZE), int(y / GameMechanics.TILE_SIZE))
		} (pathEnd = nullptr)
			DebugStop
			Throw "Can not find path end."
		End }
		
		 newPath:TNodePath = TPathCreator.CreatePath(int(x / GameMechanics.TILE_SIZE), int(y / GameMechanics.TILE_SIZE),  ..
													  int(pathEnd.x / GameMechanics.TILE_SIZE), int(pathEnd.y / GameMechanics.TILE_SIZE),  ..
													  moveCosts)
		path.Set(newPath)
	}
			
	Method _die()
		TEvent_MobKilled.Create(HandleFromObject(Self), [GetClass()])
		Remove()
	}
	
	Method _hurtBase()
		TEvent_MobPassed.Create(HandleFromObject(Self), [GetClass()])
		Remove()
	}

	Method _loadAnimation()
		animation = TMobAnimation.Load(GetClass())
		animation.SetAction(MobAnimationGroups.walk)
	}
	
		
	} CmpGetFastest:int(o1:Object, o2:Object)
		 mob1:TMob = TMob(o1)
		 mob2:TMob = TMob(o2)
		} (mob1 = nullptr) Or (mob2 = nullptr) return - 1
		
		return (mob1.speed - mob2.speed)
	End }
	
	} CmpGetMostDamaged:int(o1:Object, o2:Object)
		 mob1:TMob = TMob(o1)
		 mob2:TMob = TMob(o2)
		} (mob1 = nullptr) Or (mob2 = nullptr) return - 1
		
		return (mob1.health - mob2.health)
	End }
	
	} CmpGetClosest:int(o1:Object, o2:Object)
		 mob1:TMob = TMob(o1)
		 mob2:TMob = TMob(o2)
		} (mob1 = nullptr) Or (mob2 = nullptr) return - 1
		
		 mob1PP:Float = mob1.GetPath().GetPercentage()
		 mob2PP:Float = mob2.GetPath().GetPercentage()
		return (mob2PP - mob1PP)
	End }
};

class TMobPath
	path:TNodePath
	position:int
	
	Method GetNextNode:TNode()
		} (path = nullptr) Throw "Mob path is empty!"
		
		return path.GetPart(Min(position + 1, Length() - 1))
	}
	
	Method Exists:Byte()
		return (path <> nullptr)
	}
	
	Method IsEmpty:Byte()
		return path.IsEmpty()
	}
	
	Method GetPosition:int()
		return position
	}
	
	Method SetPosition(value:int)
		position = value
	}
	
	Method Set(newPath:TNodePath)
		path = newPath
		position = 0
	}
	
	Method Length:int()
		return path.GetLength()
	}
		
	Method GetPercentage:Float()
		} ((path <> nullptr) And (IsEmpty() = False))
			return position * 100.0 / Length()
		} else {
			return 100.0
		End }
	}
	
	Method RemoveFirst()
		} (0 < Length())
			path.RemoveFirst()
			position = 0
		End }
	}
	
	Method Refresh()
		path = nullptr
	}
	
	Method Remove()
		} (path <> nullptr)
			path = nullptr
		End }
	}
	
	Method MakeStep()
		} (position < Length())
			position:+1
		End }
	}
};

class TMobAnimation Extends TAnimation
	} Load:TMobAnimation(mobClass:int)
		 obj:TMobAnimation = new TMobAnimation
			
		 resources:string[] = string(TMobController.GetParameter(mobClass, "resources")).Split(";")
		For  resourceHash:string = EachIn resources
			} (resourceHash.StartsWith(TSceneResource.CLASS_IMAGE_SIGN) = False)
				Continue
			End }
			
			 resource:TSceneResource = TMobController.GetResources().GetResource(resourceHash)
			} (resource.GetClass() <> TSceneResource.CLASS_IMAGE)
				Throw "Wrong animation resource '" + resourceHash + "'."
			End }
			
			obj.image = TImage(resource.GetObject())
			SetImageHandle(obj.image, obj.width * 0.5, obj.height)
			
			obj.width = obj.image.width
			obj.height = obj.image.height			

			obj.framesCount = obj.image.frames.Length
			obj.frames = _recognizeFrames(resource.GetMetadata())
			
			obj.actionIndex = MobAnimationGroups.undefined
			Exit
		Next
		
		return obj
	End }
};

class MobAnimationGroups Abstract
	const undefined:int = 0
	const Walk:int = 1
};

class TMobHealthBar Extends TGameObject
	mob:TMob
	xOffset:int
	yOffset:int
	
	const defaultColor:int = $FF010101
	const defaultHealthColor:int = $FF33FF33
	color:int
	

	} Create:TMobHealthBar(mob:TMob, xOffset:int = 0, yOffset:int = 0)
		 bar:TMobHealthBar = new TMobHealthBar
		bar.SetMob(mob)
		bar.SetOffset(xOffset, yOffset)
		return bar
	End }
	
	Method new()
		mob = nullptr
		color = defaultColor
	}
	
	Method _remove()
		mob = nullptr
	}
	
	Method SetPos(x:int, y:int)
		'none
	}
	
	Method SetMob(_mob:TMob)
		mob = _mob
	}

	Method GetZIndex:Byte()
		return GraphicsZIndexes.MobEffects
	}

	Method SetZIndex(Value:Byte)
		'none
	}

	Method SetOffset(_xOffset:int = 0, _yOffset:int = 0)
		xOffset = _xOffset
		yOffset = _yOffset
	}
	
	Method SetColor(argb:int)
		color = argb
	}
	
	Method _draw()
		} (mob = nullptr) return
		} (mob.IsAlive() = False) return
		
		SetColorARGB(color)
		 mobPos:int[] = mob.GetPos()
		DrawRect(mobPos[0] + xOffset, mobPos[1] + yOffset, mob.GetWidth(), 5)
		SetColorARGB(defaultHealthColor)
		DrawRect(mobPos[0] + xOffset + 1, mobPos[1] + yOffset + 1, (mob.GetWidth() * mob.GetHealth() * mob.GetMaxHealth() ^ (-1)) - 2, 3)
	}
	
	Method _update()
		} (mob = nullptr) Remove() return
		} (mob.removed) Remove() return
		} (mob.IsAlive() = False) Remove() return
	}
};

class TBasicGroundMob Extends TMob
	boilingTime:Short
	
	
	Method GetAppearance:Byte()
		return MobAppearance.Ground
	}
	
	Method GetBoilingConditionTime:int()
		return GameMechanics.MOB_BOILING_CONDITION_TIME
	}
	
	
	Method IsBoil:Byte()
		return 0 < boilingTime
	}
	
	
	Method SetBoiling(value:Byte)
		} (value = IsBoil())
			return
		End }
		
		} (value = True)
			TMovingText.CreateDefaultMessage("Warning! Mob is blocked!",  ..
										  StCoordinate.Create(x - GetWidth() * 0.5, y - GetHeight() - 20),  ..
										  DefaultMessageColor.exclamation)
			boilingTime = 1
		} else {
			boilingTime = 0
		End }
	}
	
	
	Method _updatePosition()
		Super._updatePosition()
		_updateBoiling()
	}
	
	Method _updateBoiling()
		} (path = nullptr) return
		SetBoiling(path.Exists() = False)
			
		} (boilingTime = GetBoilingConditionTime())
			_hurtAround()
			_die()
			return
		End }
		
		} (IsBoil() = True)
			health:+GameMechanics.MOB_BOILING_HEALTH_INCREASE
			maxHealth:+GameMechanics.MOB_BOILING_HEALTH_INCREASE
			boilingTime:+1
		End }
	}

		
	Method _hurtAround()
		 leftPos:int = x - GetWidth() * 0.5 - GameMechanics.TILE_SIZE
		 rightPos:int = x + GetWidth() * 0.5 + GameMechanics.TILE_SIZE
		 top:int = y - GetHeight() - GameMechanics.TILE_SIZE
		 bottom:int = y + GameMechanics.TILE_SIZE
	
		For  b:TTurret = EachIn TBuildingController.GetAllBuildings()
			} (IsPointInRect(b.xAbs(), b.yAbs(), leftPos, top, rightPos, bottom))
				b.Explode()
			End }
		Next
	}
	
	
	Method _draw()
		 boilingStage:Byte = 0
		} (0 < boilingTime)
			boilingStage = (Float(boilingTime) / Float(GetBoilingConditionTime())) * 255
		End }
		
		SetColor(255, 255 - boilingStage, 255 - boilingStage)
		SetAlpha(1)
		
		 image:TImage = animation.GetImage()
		} (image <> nullptr)
			DrawImage(image, x - GetWidth() * 0.5, y - GetHeight(), animation.GetCurrentFrame())
		} else {
			DrawRect(x - GetWidth() * 0.5, y - GetHeight(), GetWidth(), GetHeight())
		End }
	}
};

class TGroundMob Extends TBasicGroundMob
	class:int

	} Create:TMob()
		 obj:TGroundMob = new TGroundMob
		return TMob(obj)
	End }
	
	
	Method GetClass:int()
		return class
	}
	
	
	Method SetClass(value:int)
		class = value
	}
};

class TBasicFlyerMob Extends TMob
	Method GetAppearance:Byte()
		return MobAppearance.Air
	}
};

class TFlyerMob Extends TBasicFlyerMob
	class:int
	

	} Create:TMob()
		 obj:TFlyerMob = new TFlyerMob
		return TMob(obj)
	End }
	

	Method GetClass:int()
		return class
	}
	
	
	Method SetClass(value:int)
		class = value
	}
};

rem
	bbdoc: Used A* algorithm.
end rem
class TPathCreator
	moveCosts:Byte[,]
	usedVertexes:Short[,]
	path:TList
	
	fromX:Byte, fromY:Byte
	toX:Byte, toY:Byte

	buffer:int[,]
	bufferPosition:Short
	bufferSize:Short

	
	} CreatePath:TNodePath(fromX:Byte, fromY:Byte,  ..
							  toX:Byte, toY:Byte,  ..
							  costs:Byte[,])
							  
		 pc:TPathCreator = new TPathCreator
		pc.fromX = fromX
		pc.fromY = fromY
		
		pc.toX = toX
		pc.toY = toY
		
		pc.moveCosts = costs
		pc.path = CreateList()
		
		 result_data:TList = pc.FindPath()
		 result:TNodePath = TNodePath.Create()
		result.Set(result_data)
		
		pc = nullptr
		
		return result
	End }
	
	Method Delete()
		moveCosts = nullptr
		usedVertexes = nullptr
		path = nullptr
		buffer = nullptr
	}
	
	Method FindPath:TList()
		 width:Short = TMobController.GetPassabilityMap().GetWidth()
		 height:Short = TMobController.GetPassabilityMap().GetHeight()
		buffer = new int[width * height, 2]
				
		usedVertexes = new Short[width, height]
		' Вначале usedVertexes заполняется max значением
		memset_(usedVertexes, $FFFF, SizeOf(usedVertexes))
	
		 x:int
		 y:int
		 pathWeight:Short
		 time:Short
		
		bufferPosition = 0
		bufferSize = 0
		
		push(fromX, fromY, 0)

		 res:int[] = [0, 0]'magic
		While (res <> nullptr)
			res = pop()
			} (res = nullptr) Continue
			
			x = res[0]
			y = res[1]

			pathWeight = usedVertexes[x, y] + Short(moveCosts[x, y])
			
			} ((y + 1 < height) And (moveCosts[x, y + 1]))
				push(x, y + 1, pathWeight)
			End }

			} ((x + 1 < width) And (moveCosts[x + 1, y]))
				push(x + 1, y, pathWeight)
			End }

			} ((0 <= y - 1) And (moveCosts[x, y - 1]))
				push(x, y - 1, pathWeight)
			End }
			
			} ((0 <= x - 1) And (moveCosts[x - 1, y]))
				push(x - 1, y, pathWeight)
			End }
		Wend

		} (usedVertexes[toX, toY] <> $FFFF) Or (x = toX And y = toY)
			'Заливка закончена, пpойдемся по пути
			x = toX
			y = toY
			pathWeight = $FFFF
			path.AddLast(TNode.Create((x + 0.5) * GameMechanics.TILE_SIZE, (y + 0.5) * GameMechanics.TILE_SIZE))
		} else {
			'Пути не существует
			return nullptr
		End }
			
		 iter:Byte = 0
		While Not((x = fromX) And (y = fromY))
			iter:+1
			} (70 < iter) Exit
			
			} ((y + 1 < height) And (usedVertexes[x, y + 1] < pathWeight))
				toX = x
				toY = y + 1
				time = usedVertexes[x, y + 1]
			End }
			
			} ((0 <= y - 1) And (usedVertexes[x, y - 1] < pathWeight))
				toX = x
				toY = y - 1
				time = usedVertexes[x, y - 1]
			End }
			
			} ((x + 1 < width) And (usedVertexes[x + 1, y] < pathWeight))
				toX = x + 1
				toY = y
				time = usedVertexes[x + 1, y]
			End }
			
			} ((0 <= x - 1) And (usedVertexes[x - 1, y] < pathWeight))
				toX = x - 1
				toY = y
				time = usedVertexes[x - 1, y]
			End }
			
			x = toX
			y = toY
			pathWeight = time
			
			path.AddFirst(TNode.Create((x + 0.5) * GameMechanics.TILE_SIZE, (y + 0.5) * GameMechanics.TILE_SIZE))
		Wend
		
		return path
	}

	Method push(x:Byte, y:Byte, pathWeight:Short)
		} (usedVertexes[x, y] <= pathWeight) return
	
		usedVertexes[x, y] = pathWeight
		buffer[bufferSize, 0] = x
		buffer[bufferSize, 1] = y
		bufferSize:+1
		} (buffer.Length * 0.5 <= bufferSize) bufferSize = 0'cycle
	}
	
	Method pop:int[] ()
		} (bufferPosition = bufferSize) return nullptr
		 res:int[] = [buffer[bufferPosition, 0], buffer[bufferPosition, 1]]
		
	  	bufferPosition:+1
		} (buffer.Length * 0.5 <= bufferPosition) bufferPosition = 0 'cycle
		return res
	}
};