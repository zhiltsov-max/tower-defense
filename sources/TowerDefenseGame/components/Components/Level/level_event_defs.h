#ifndef LEVEL_EVENT_DEFS_H
#define LEVEL_EVENT_DEFS_H

#include "level_event.h"

enum class EventTag {
	_min = 0,
	undefined = 0,
	
	//Main events: 0..99
	GameStarted = 1,
	GameEnded = 2,
	
	//Building events: 100..199
	BuildingCreated = 100,
	BuildingSold = 101,
	BuildingUpgraded = 102,
	
	CastleDied = 150,
	
	//Mob events: 200..299
	MobKilled = 200,
	MobPassed = 201,
	MobTimerCompleted = 202,
	MobSpawned = 203,
	
	//Research events: 300..349
	ResearchCompleted = 300,
	
	_max = 300
};

#define DECLARE_EVENT( NAME, TAG ) \
    class TEvent_ ## NAME : public TLevelEvent \
	{ \
	public: \
		TEvent_ ## NAME(void const* sender, const string& message = "") : \
            TLevelEvent(sender, message) {} \
		const Tag& getTag() const { \
			return TAG; \
		} \
	};

DECLARE_EVENT( GameStarted, EventTag::GameStarted )
DECLARE_EVENT( GameEnded, EventTag::GameEnded )

DECLARE_EVENT( BuildingCreated, EventTag::BuildingCreated )
DECLARE_EVENT( BuildingSold, EventTag::BuildingSold )
DECLARE_EVENT( BuildingUpgraded, EventTag::BuildingUpgraded )
	
DECLARE_EVENT( CastleDied, EventTag::CastleDied )
	
DECLARE_EVENT( MobKilled, EventTag::MobKilled )
DECLARE_EVENT( MobPassed, EventTag::MobPassed )
DECLARE_EVENT( MobTimerCompleted, EventTag::MobTimerCompleted )

DECLARE_EVENT( ResearchCompleted, EventTag::ResearchCompleted )

class TEvent_TriggerEvent : public TLevelEvent
{
public:
	TEvent_TriggerEvent(void const* sender, const string& message = "", Tag tag_ = EventType::undefined) :
        TLevelEvent(sender, message),
		tag(tag_)
	{}
		
	void setTag(Tag value) {
		tag = value;
	}

	const Tag& getTag() const {
		return tag;
	}
private:
	Tag tag;
};

#endif //LEVEL_EVENT_DEFS_H
