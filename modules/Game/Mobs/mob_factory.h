#ifndef MOB_FACTORY_H
#define MOB_FACTORY_H

#include "mob.h"
#include "mob_info.h"


class TMobFactory
{
public:
    void Register(TMob::ClassId classId, TMob* prototype, TMob::Info::Loader* loader);
	size_t RegistrySize() const;
    bool IsRegistered(TMob::ClassId classId) const;
	uint GetClassId(size_t pos) const;
    TMob::Info::Loader const* GetInfoLoader(TMob::ClassId classId) const;

	TMob* Create(uint classId, uint pathId, TMob::Info const* source);
private:
	struct Entry {
		std::unique_ptr<TMob> prototype;
		std::unique_ptr<TMob::Info::Loader> loader;
		Entry(TMob* prototype_, TMob::Info::Loader* loader_) :
			prototype(prototype_), loader(loader_)
		{}
	};
    typedef std::map<TMob::ClassId, Entry> Data;
	Data data;
};

#endif //MOB_FACTORY_H
