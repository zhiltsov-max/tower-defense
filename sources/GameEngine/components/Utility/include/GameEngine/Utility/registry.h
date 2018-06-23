#ifndef GAME_ENGINE_REGISTRY_H
#define GAME_ENGINE_REGISTRY_H

#include <cstddef>
#include <map>
#include <sstream>

#include "GameEngine/Utility/common.h"
#include "GameEngine/Utility/debug.h"


GE_BEGIN_ENGINE_NAMESPACE

template<class Entry_, class Id_>
class TRegistry {
public:
    using TEntry = Entry_;
    using TId = Id_;

    void Register(const TId& id, const TEntry& entry);

    void Unregister(const TId& id);

    const TEntry& operator[](const TId& id) const {
        return data.at(id);
    }

    TEntry& operator[] (const TId& id) {
        return data.at(id);
    }

    bool IsRegistered(const TId& id) const {
        return data.count(id) != 0;
    }

    size_t Size() const {
        return data.size();
    }

    bool IsEmpty() const {
        return data.empty();
    }

    void Clear() {
        data.clear();
    }

protected:
    using Storage = std::map<TId, TEntry>;
    Storage data;
};

template<class Entry_, class Id_>
void TRegistry<Entry_, Id_>::Register(const TId& id, const TEntry& entry) {
    GE_ASSERT(IsRegistered(id) == false,
        "Class #" + std::to_string(id) + " already registered.");

    data[id] = entry;
}

template<class Entry_, class Id_>
void TRegistry<Entry_, Id_>::Unregister(const TId& id) {
    auto it = data.find(id);

    GE_ASSERT(it == data.end(),
        "Class #" + std::to_string(id) + " is not registered.");

    data.erase(it);
}

GE_END_ENGINE_NAMESPACE

#endif // GAME_ENGINE_REGISTRY_H
