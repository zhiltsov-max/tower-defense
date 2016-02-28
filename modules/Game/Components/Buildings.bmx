class TB_Base Extends TTurret
	const baseRotationPerFrame:Byte = 5
	

	Method new()
		bulletAcceleration = 1
		bulletSize = 1
	}

	Method _checkRotation()
		baseRotation = baseRotation Mod 360
		turretRotation = turretRotation Mod 360
		
		} (baseRotation + turretMaxAngle < turretRotation)
			turretRotation = baseRotation + turretMaxAngle
			baseRotation:+baseRotationPerFrame
		} else {} (turretRotation < baseRotation - turretMaxAngle)
			turretRotation = baseRotation - turretMaxAngle
			baseRotation:-baseRotationPerFrame
		End }
	}
	
	Method _draw()
		Super._draw()

		 xPos:int = xAbs()
		 yPos:int = yAbs()
		SetRotation(turretRotation)
		DrawLine(xPos, yPos, xPos + 25, yPos)
		SetRotation(0)
	}
	
	} GetClass:int()
		return BuildingClass.Base
	End }
};

class TB_Rocket Extends TTurret
	Method new()
		bulletAcceleration = 0.25
		bulletSize = 2
	}
	
	Method _checkRotation()
		 tBaseRot:int = baseRotation
		 tTurrRot:int = turretRotation
		} (Abs(tBaseRot) > 360)
			tBaseRot = tBaseRot Mod 360
		End }
		} (Abs(tTurrRot) > 360)
			tTurrRot = tTurrRot Mod 360
		End }
		
		} (tBaseRot + turretMaxAngle < tTurrRot)
			turretRotation = baseRotation + turretMaxAngle
		} else {} (tTurrRot < tBaseRot - turretMaxAngle)
			turretRotation = baseRotation - turretMaxAngle
		End }
	}
	
	Method _findEnemiesInRange:TList()
		 enemies:TList = Super._findEnemiesInRange()
		For  enemy:TMob = EachIn enemies
			} Not(_canSeeTarget(enemy))
				enemies.Remove(enemy)
			End }
		Next
		return enemies
	}
	
	Method _canSeeTarget:Byte(target:TMob)
		 tBaseRot:int = baseRotation
		 targetRot:int = ATan2(target.y - yAbs(), target.x - xAbs())
		} (targetRot < 0) targetRot = 360 + targetRot
		} (Abs(tBaseRot) > 360)
			tBaseRot = tBaseRot Mod 360
		End }
		} (Abs(targetRot) > 360)
			targetRot = targetRot Mod 360
		End }
		} (targetRot <= tBaseRot + turretMaxAngle) And (tBaseRot - turretMaxAngle <= targetRot)
			return True
		End }
		return False
	}

	} GetClass:int()
		return BuildingClass.Rocket
	End }
};

class TB_Artillery Extends TB_Rocket
	Method new()
		bulletAcceleration = 0.5
		bulletSize = 7
	}

	} GetClass:int()
		return BuildingClass.Artillery
	End }
};


class TB_Watchpost Extends TBuilding
	messageBubbleName:string
	message:string

	
	Method new()
		messageBubbleName = nullptr
		message = nullptr
		buildState = BuildStates.Complete
	}
	
	Method _remove()
		 bubble:TMenuObject = _getBubble()
		} (bubble <> nullptr)
			bubble.Remove()
			bubble = nullptr
		End }
		messageBubbleName = nullptr
		message = nullptr
	}
	
	
	Method Initialize()
		Super.Initialize()
		_loadBubble()
	}
	
	Method _loadBubble()
		} (messageBubbleName = nullptr)
			return
		End }
		
		 bubble:TMessageBubble = _getBubble()
		} (bubble = nullptr)
			return
		End }
		bubble.SetText(message)
	}
	
	Method _loadAnimation()
		animation = TBuildingAnimation.Load(GetClass())
		animation.SetAction(BuildingAnimationGroup.Normal)
	}
	
	Method _loadSelection()
		'none
	}
	

	Method _getBubble:TMessageBubble()
		return TMessageBubble(UIParent().FindChild(messageBubbleName))
	}
	
	Method _checkBubblePosition()
		_getBubble().SetPosition(StCoordinate.Create(xAbs(), yAbs() - _getBubble().GetHeight()))
	}
	
	
	} GetClass:int()
		return BuildingClass.Watchpost
	End }
	
	
	Method GetMessageBubbleName:string()
		return messageBubbleName
	}
	
	Method SetMessageBubbleName(value:string)
		messageBubbleName = value
	}
	
	Method SetMessage(value:string)
		} (message <> value)
			 bubble:TMessageBubble = _getBubble()
			} (bubble <> nullptr)
				bubble.SetText(value)
			End }
			message = value
		End }
	}
	
	Method GetMessage:string()
		return message
	}
	
	
	Method SetSelection(value:Byte)
		} (selected <> value)
			 bubble:TMessageBubble = _getBubble()
			} (bubble <> nullptr)
				} (value = True) _checkBubblePosition()
				bubble.SetVisibility(value)
			End }
			Super.SetSelection(value)
		End }
	}

	
	Method _updateBehaviour()
		' update as building
		
		' update gui object
		 event:TGameEvent = _getCurrentEvent()
		} (event <> nullptr)
			} (event.GetType() = EventType.GameStarted)
				 bubble:TMessageBubble = _getBubble()
				} (bubble <> nullptr)
					_checkBubblePosition()
					bubble.SetText(message)
					bubble.Show()
				End }
			End }
		End }
	}
	
	Method UpdateParameters()
		'none
	}
};


class TB_CastleAnimation Extends TBuildingAnimation
	} Load:TBuildingAnimation(buildingClass:int)
		 obj:TB_CastleAnimation = new TB_CastleAnimation
	
		 resources:string[] = string(TBuildingController.GetParameter(buildingClass, "resources")).Split(";")
		For  resourceHash:string = EachIn resources
			} (resourceHash.StartsWith(TSceneResource.CLASS_IMAGE_SIGN) = False)
				Continue
			End }

			 resource:TSceneResource = TBuildingController.GetResources().GetResource(resourceHash)
			} (resource.GetClass() <> TSceneResource.CLASS_IMAGE)
				Throw "Wrong animation resource '" + resourceHash + "'."
			End }
			
			obj.image = TImage(resource.GetObject())
			obj.width = obj.image.width
			obj.height = obj.image.height
			obj.framesCount = obj.image.frames.Length
			obj.frames = _recognizeFrames(resource.GetMetadata())
			Exit
		Next
		
		return TBuildingAnimation(obj)
	End }
};

class TB_Castle Extends TBuilding
	health:int
	maxHealth:int
	
	
	Method new()
		health = 0
		maxHealth = 0
		buildState = BuildStates.Complete
	}
	
	Method Initialize()
		Super.Initialize()
		maxHealth = int[] (TBuildingController.GetParameter(GetClass(), "health"))[0]
	}

	Method _loadSelection()
		'none
	}
	
	Method _loadAnimation()
		animation = TB_CastleAnimation.Load(GetClass())
		Assert TB_CastleAnimation(animation) <> nullptr, "Loaded animation is not an instance of TB_CastleAnimaiton."
		animation.SetAction(BuildingAnimationGroup.Normal)
	}
	
	
	Method IsAlive:Byte()
		return (0 < health)
	}

	Method NeedsReapir:Byte()
		return health < maxHealth
	}
	
	Method IsSelected:Byte()
		return False
	}
		
		
	Method Repair(amount:int)
		} (health = maxHealth)
			Throw "Trying to repair not damaged building!"
		End }
		
		health:+amount
	}
	
	Method Hurt(amount:int)
		health:-amount
		} (IsAlive() = False)
			TEvent_CastleDied.Create()
		End }
	}
	
	
	Method GetHealth:int()
		return health
	}
	
	Method GetMaxHealth:int()
		return maxHealth
	}
	
	} GetClass:int()
		return BuildingClass.Castle
	End }
	
	
	Method SetHealth(value:int)
		} (DebugTools.IsDebugEnabled() = True)
			} (maxHealth < value)
				Throw "Attempt to set castle health bigger than maximum health."
			End }
		End }
		health = Min(value, maxHealth)
	}
	
	
	Method UpdateParameters()
		'none
	}

	Method _updateBehaviour()
		'none
	}
};