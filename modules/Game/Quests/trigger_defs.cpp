#include "trigger_defs.h"
#include "..\level.h"
#include "..\..\Mobs\mob.h"
#include "..\..\Mobs\controller.h"


TQuestTrigger_MobSpawn::TQuestTrigger_MobSpawn() :
	timer(0),
	sequence(),
	pathId(0),
	EVENT_TAG_MOB_SPAWNED(EventTag::MobSpawned)
{}
TQuestTrigger_MobSpawn::TQuestTrigger_MobSpawn(const TMobSequence& sequence_, uint pathId_) :
	timer(0),
	sequence(sequence_),
	pathId(pathId_),
	EVENT_TAG_MOB_SPAWNED(EventTag::MobSpawned)
{}
	
void TQuestTrigger_MobSpawn::initialize(const TNamedData<string>& args) {
	if (args.empty() == true) {
		return;
	}

	static const size_t ARG_COUNT = 2;
	if (args.size() != ARG_COUNT) {
		return;
	}

	sequence = TMobSequence(args.slice("seqeunce"));
	pathId = std::stoi(args.at("pathId"));
}

TLevelTrigger* TQuestTrigger_MobSpawn::clone() const {
	TLevelTrigger* res = new TQuestTrigger_MobSpawn(*this);
	return res;
}
	
uint TQuestTrigger_MobSpawn::getMobDelay(int position, const TMobSequence& sequence) {
	return sequence.getDelay(position) * DebugTools::FPS::normalized();
}

TMobsFactory& getMobFactory() {
	return MobsController::getFactory();
}	
TLevelScene& getScene() {
	return LevelHelper::getLevelInstance().getScene();
}
		
uint TQuestTrigger_MobSpawn::getTimer() const {
	return timer;
}	
void TQuestTrigger_MobSpawn::setTimer(uint value) {
	timer = value;
}
	
uint TQuestTrigger_MobSpawn::getPathId() const {
	return pathId;
}
void TQuestTrigger_MobSpawn::setPathId(uint value) {
	pathId = value;
}
	
const TMobSequence& TQuestTrigger_MobSpawn::getSequence() const {
	return sequence;
}
void TQuestTrigger_MobSpawn::setSequence(const TMobSequence& value) {
	sequence = value;
}
	
void TQuestTrigger_MobSpawn::update() {
	if (sequence.isCompleted() == false) {
		++timer;
		if (getMobDelay(-1, sequence) < timer) {
			int id = sequence.makeStep();
			TEvent_MobTimerCompleted(this, "mobspawn");
			getScene().addObject(getMobFactory().Create(
				id, pathId, 
				LevelHelper::getLevelInstance().getInfo().getGameObjectsInfo().getMobsInfo().getClassInfo(id))
				);
			TEvent_TriggerEvent(this, "mobspawn", EVENT_TAG_MOB_SPAWNED);
			timer = 0;
		}
	}
}

TMobSequence::TMobSequence() :
	sequence(),
	position(0),
	currentEntry(0)
{}


static const string randomSign = "rand";
TMobSequence::TMobSequence(const TNamedData<string>& source) {
	if (source.empty() == true) {
		throw_("Unable to load mob sequence: sequence is not set.", "TMobSequence::TMobSequence");
	}
		
	string raw_sequence = source["value"];
	raw_sequence = raw_sequence.substr(2, raw_sequence.size() - 2);
	std::vector<string> elements = String::split(raw_sequence, elementsSeparator);
		
	for(auto it = elements.cbegin(); it != elements.cend(); ++it) {
		std::vector<string> parts = String::split(*it, mobCountSeparator);
		int id = std::stoi(parts[0]);
		if (parts[0] == randomSign) {
			const TMobsFactory& loadedMobs = LevelHelper::getLevelInstance().getStagesInfo().getGameObjectsInfo().getMobsInfo().getFactory();
			id = std::stoi(loadedMobs[rand() % loadedMobs.RegistrySize()]);
		}
		uint length = 1;
		if (1 < parts.size()) {
			length = std::stoi(parts[1]);
		}
			
		sequence.push_back(Entry(id, length));
	}
		
	delay = std::stoi(source["delay"]);
}
	
/*
	If there's no next -1 is returned.
*/
int TMobSequence::makeStep() {
	int res;
	const Entry& entry = sequence[currentEntry];
	if (entry.count < position) {
		++currentEntry;
		position = 0;
			
		if (size() == currentEntry) {
			res = -1;
		} else {
			res = sequence[currentEntry].mobId;
		}
	} else {
		++position;
		res = entry.mobId;
			
		if (position == entry.count) {
			++currentEntry;
			position = 0;
		}
	}	
	return res;
}
	
void TMobSequence::restart() {
	position = 0;
	currentEntry = 0;
}
	
bool TMobSequence::isCompleted() const {
	return (size() == currentEntry) && (position == 0);
}
		
size_t TMobSequence::length() const {
	size_t res = 0;
	for(auto it = sequence.cbegin(); it != sequence.cend(); ++it) {
		res += (*it).count;
	}
	return res;
}

uint TMobSequence::getDelay(int position) const {
	UNUSED( position )
	return delay;
}

size_t TMobSequence::size() const {
	return sequence.size();
}