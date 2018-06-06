#include "mob_factory.h"


void TMobFactory::Register(TMob::ClassId classId, TMob* prototype, TMob::Info::Loader* loader) {
	if (IsRegistered(classId) == true) {
#if _DEBUG_
        Throw("Mob class #" + std::to_string((long long)classId) + " already registered.", "TMobFactory::Register");
#else
		return;
#endif
	}
	if ((prototype == nullptr) || (loader == nullptr)) {
#if _DEBUG_
        Throw("Mob class #" + std::to_string((long long)classId) + " prototype is null.", "TMobFactory::Register");
#else
		return;
#endif		
	}
	data[classId].prototype = std::unique_ptr<TMob>(prototype);
	data[classId].loader = std::unique_ptr<TMob::Info::Loader>(loader);
}
	
bool TMobFactory::IsRegistered(TMob::ClassId classId) const {
	return data.count(classId) != 0;
}

void _generateMobPosition(TMob* mob, TMob::Path::Node const* start) {
	float noiseX = rnd(-GameMechanics::TILE_SIZE * 0.5, GameMechanics::TILE_SIZE * 0.5);
	float noiseY = rnd(-GameMechanics::TILE_SIZE * 0.5, GameMechanics::TILE_SIZE * 0.5);
	mob->setPos(Point2ui(start->absPos().x() + noiseX, start->absPos().y() + noiseY));
}

TMob* TMobFactory::Create(uint classId, uint pathId, TMob::Info const* source) {
	TMob* res = data.at(classId)->prototype->clone();
	res->initialize(source);
	res->setHealth(res->getMaxHealth());

	switch (MobController::getPathSelectionPolicy()) {
	case PathSelectionPolicy::Dynamic:
		{
			auto path = MobController::getNodeMap().getPath(pathId);
			res->getPath().set(path);
			_generateMobPosition(res, path->getStart());
			break;
		}	

	case PathSelectionPolicy::Static:
		{
			TMob::Path::Node const* start = MobController::getNodeMap().getEnter(pathId);
			_generateMobPosition(res, start);
			break;
		}
				
	default:
#if _DEBUG_
        Throw("Unexpected path selection policy.", "TMobFactory::Create");
#endif
	}

	return res;
}

size_t TMobFactory::RegistrySize() const {
	return data.size();
}

uint TMobFactory::GetClassId(size_t pos) const {
	auto it = data.cbegin();
	while ((it != data.cend()) && (0 < pos)) {
		++it;
	}
	return (*it).first->getClass();
}

TMob::Info::Loader const* TMobFactory::GetInfoLoader(TMob::ClassId classId) const {
	return data.at(classId).loader.get();
}
