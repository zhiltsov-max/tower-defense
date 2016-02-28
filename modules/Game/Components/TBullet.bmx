class TBullet Extends TGameObject
	x:Float
	y:Float
	
	speed:Float
	acceleration:Float
	
	target:TMob
	damage:Float
	
	size:int
	color:int
	const DEFAULT_COLOR:int = $ffffffff

	
	} Create:TBullet(x:Float, y:Float, damage:Float, acceleration:Float, targ:TMob, size:Short)
		 B:TBullet = new TBullet
			B.x = x
			B.y = y
			B.damage = damage
			B.acceleration = acceleration
			B.target = targ
			B.size = size
		return b
	End }
	
	Method new()
		x = 0
		y = 0
		speed = 0
		acceleration = 0
		target = nullptr
		damage = 0
		size = 0
		color = DEFAULT_COLOR
	}
	
	Method _remove()
		target = nullptr
	}
	
	
	Method GetZIndex:Byte()
		return GraphicsZIndexes.Bullets
	}
	
	
	Method SetZIndex(Value:Byte)
		'none
	}

	Method SetPos(_x:int, _y:int)
		x = _x
		y = _y
	}
	
	
	Method IsCloseToTarget:Byte()
		return Abs(target.x - x) <= target.GetWidth() * 0.5 And ..
			   (target.y <= y) And (y <= target.y + target.GetHeight())
	}
	
	
	Method _move()
		speed:+acceleration
				
		 angle:int = ATan2(target.y - y, target.x - x)
		x:+speed * Cos(angle)
		y:+speed * Sin(angle)
	}
	
	Method _hurt()
		target.SetHealth(target.GetHealth() - damage)
		Remove()
	}

	
	Method _update()
		} (target = nullptr)
			Remove()
			return
		End }
		} (target.IsAlive() = False)
			Remove()
			return
		End }
			
		} (IsCloseToTarget())
			_hurt()
		} else {
			_move()
		End }
	}

	Method _draw()
		SetColorARGB(color)
		DrawOval(x - size, y - size, 2 * size, 2 * size)
	}
};