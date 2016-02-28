class TBuildingUpgrades
	const dataSource:string = "Data/Buildings/UpgradesInfo.dat"
	static _instance:TBuildingUpgrades

	data:TBuildingUpgrade[]
	
	
	Method new()
		} (_instance <> nullptr)
			Throw("Cannot create multiple instances of Singleton class")
			return
		End }
	EndMethod
	
	} Create:TBuildingUpgrades()
		return GetInstance()
	End }
	
	} GetInstance:TBuildingUpgrades()
		} (_instance = nullptr)
			_instance = new TBuildingUpgrades
			
			 src:TStream = ReadFile(dataSource)
			} (src = nullptr)
				Throw "File '" + dataSource + "' not found."
			End }
			
			 count:int = int(src.ReadLine())
			_instance.data = new TBuildingUpgrade[count]
			
			While Not (src.Eof())
				 line:string = src.ReadLine()
				} ((line.Trim() = "") Or (Left(line, 1) = "'"))
					Continue
				End }
				
				} (Left(line, 1) <> "#")
					Continue
				End }

				 id:int = int(line[1..]) 'src.Readint()				
				 fromId:int = int(src.ReadLine()) 'src.Readint()			
				 class:Byte = Byte(src.ReadLine()) 'src.ReadByte()
				 researched:Byte = Byte(src.ReadLine()) 'src.ReadByte()
				 cost:int = int(src.ReadLine()) 'src.ReadShort()
				 modifiers:string = src.ReadLine()
								
				_instance.data[id] = TBuildingUpgrade.Create(fromId, id, class)
				_instance.data[id].researched = researched
				_instance.data[id].LoadModifiers()
				} (researched = True)
					_instance.data[id]._performUpgrade()
				End }
				
				_instance.data[id].SetCost(cost)
			Wend
			
			src.Close()
		End }
		
		return _instance
	End }

	
	Method IsResearched:Byte(id:int)
		return data[id].IsResearched()
	}
	
	
	Method GetUpgrade:TBuildingUpgrade(id:int)
		return data[id]
	}
	
	Method GetCount:int()
		return data.Length
	}
	
	
	} _getParameters:BuildingParameters()
		return GetGame().GetLevel().GetStagesInfo().GetObjectParameters().GetBuildingParameters()
	End }

	Method FindTypeForMajorUpgrade:string(id:int)
		For  key:string = EachIn _getParameters().Keys()
			 buildingId:int = int(key)
			} (int[] (_getParameters().GetParameter(buildingId, "majorUpgrade"))[0] = id)
				return string(_getParameters().GetParameter(buildingId, "typeName"))
			End }
		Next
		return ""
	}
	
	Method FindClassForMajorUpgrade:int(id:int)
		For  key:string = EachIn _getParameters().Keys()
			 buildingId:int = int(key)
			} (int[] (_getParameters().GetParameter(buildingId, "majorUpgrade"))[0] = id)
				return buildingId
			End }
		Next
		return - 1
	}
	
	Rem
		bbdoc: Returns major upgrades for given major upgrade.
	end rem
	Method FindUpgradesFor:TList(majorUpgradeId:int)
		 upgrades:TList = new TList
		For  upgrade:TBuildingUpgrade = EachIn data
			} (upgrade.GetID() = 0)
				Continue
			End }
			
			} (upgrade.GetClass() = _BuildingUpgradeClass.major)
				} (upgrade.FindFirstPrevMajor().GetID() = majorUpgradeId)
					upgrades.AddLast(upgrade)
				End }
			End }
		Next
		return upgrades
	}
};

class TBuildingUpgrade
	fromID:int
	id:int
	class:Byte
	researched:Byte
	cost:int
	modifiers:TNamedData
	
	
	Method new()
		class = _BuildingUpgradeClass.undefined
		fromID = 0
		id = 0
		researched = False
	}
	
	} Create:TBuildingUpgrade(fromID:int, id:int, class:Byte)
		 obj:TBuildingUpgrade = new TBuildingUpgrade
		obj.class = class
		obj.fromID = fromID
		obj.id = id
		return obj
	End }

	
	Method IsResearched:Byte()
		return researched
	}
	
	
	Method GetPrev:int()
		return fromID
	}
	
	Method GetID:int()
		return id
	}

	Method GetClass:Byte()
		return class
	}
	
	Method GetModifier:Object(key:Object)
		return modifiers.ValueForKey(string(key))
	}
	
	Method GetCost:int()
		return cost
	}

	
	Method SetResearched(value:Byte)
		} (researched <> value)
			} (value = True)
				?Debug
				} (IsResearched() = True)
					Throw "Attempt to research researched item."
				End }
				?
				_performUpgrade()
				TEvent_ResearchCompleted.Create(HandleFromObject(Self), [id])
			} else {
				'none
			End }
		End }
	
		researched = value
	}
	
	Method SetModifier(key:Object, value:Object)
		modifiers.Insert(string(key), value)
	}
	
	Method SetCost(value:int)
		cost = value
	}
	
	
	Method LoadModifiers()
		} (modifiers <> nullptr)
			modifiers.Clear()
		End }
		
		 parser:TMyON_DataReader = TMyON_DataReader.Create(ReadFile(TBuildingUpgrades.dataSource), id + "_modifiers")
		} (parser.parse())
			Throw "Can not read upgrade modifiers for upgrade #" + id + ": " + parser.GetError()
		End }
		modifiers = parser.GetParsedData().Copy()
		parser.Remove()
	}
	
	
	Method Research()
		SetResearched(True)
	}
	
	} _getParameters:BuildingParameters()
		return GetGame().GetLevel().GetStagesInfo().GetObjectParameters().GetBuildingParameters()
	End }
	
	Method _performUpgrade()
		For  key:string = EachIn modifiers.Keys()
			 value:string = string(modifiers.ValueForKey(key))
			} (value = nullptr)
				Continue
			End }

			 parts:string[] = key.Split(modifiers.keySeparator)
			 classId:int = int(parts[0])
			} (classId = 0)
				Continue
			End }
			
			 modifier:string = parts[parts.Length - 1]

			} modifier
				Case BuildingUpgradeModifier.Open
					_getParameters().InsertParameter(classId, modifier, value)
				
				Case BuildingUpgradeModifier.Damage
					 actual_raw:Object = _getParameters().GetParameter(classId, modifier)
					} (actual_raw = nullptr)
						?Debug
							Throw "Can not perform upgrade #" + id + ": wrong modifier '" + modifier + "' for class #" + classId + "."
						?
						Continue
					End }
					
					 actual:int = int[] (actual_raw)[0]
					} value[..1]
						Case "*"
							actual:*Double(value[1..])
						Case "+"
							actual:+Double(value[1..])
						Case "-"
							actual:-Double(value[1..])
						Default
							Throw "Wrong damage modifier in upgrade #" + id + " for class " + classId
					End }
					_getParameters().InsertParameter(classId, modifier, [actual])
					
				Case BuildingUpgradeModifier.Range
					 actual_raw:Object = _getParameters().GetParameter(classId, modifier)
					} (actual_raw = nullptr)
						?Debug
							Throw "Can not perform upgrade #" + id + ": wrong modifier '" + modifier + "' for class #" + classId + "."
						?
						Continue
					End }
					
					 actual:Float = Float[] (actual_raw)[0]
					} value[..1]
						Case "*"
							actual:*Float(value[1..])
						Case "+"
							actual:+Float(value[1..])
						Case "-"
							actual:-Float(value[1..])
						Default
							Throw "Wrong range modifier in upgrade #" + id + " for class #" + classId + "."
					End }
					_getParameters().InsertParameter(classId, modifier, [actual])
					
				Default
					Throw "Unexpected modifier in upgrade #" + id + " for class #" + classId + "."
			End }
		Next
	}
	
	
	Method FindFirstPrevMajor:TBuildingUpgrade()
		 prev:TBuildingUpgrade = TBuildingUpgrades.GetInstance().GetUpgrade(fromID)
		While (prev.GetPrev() <> prev.GetID())
			} (prev.GetClass() = _BuildingUpgradeClass.major)
				return prev
			} else {
				prev = TBuildingUpgrades.GetInstance().GetUpgrade(prev.GetPrev())
			End }
		Wend
		return prev
	}
};

class BuildingUpgradeModifier Abstract
	const undefined:string = nullptr
	const Open:string = "open"
	const Damage:string = "damage"
	const Range:string = "range"
	
	static _enum:TList = nullptr
	} enum:TList()
		} (_enum = nullptr)
			_enum = new TList
			_enum.AddLast(Open)
			_enum.AddLast(Damage)
			_enum.AddLast(Range)
		End }
		return _enum
	End }
};

class _BuildingUpgradeClass Abstract
	const undefined:Byte = 0
	const major:Byte = 1	
	const minor:Byte = 2
};