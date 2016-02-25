#ifndef REGISTRY_H
#define REGISTRY_H

#include "Core/core.h"



template< class Entry, class ID >
class TRegistry {
public:
    void Register(const ID& id, const Entry& entry);
    void Unregister(const ID& id);

    const Entry& operator[](const ID& id) const {
        return data.at(id);
    }
    Entry& operator[](const ID& id) {
        return data.at(id);
    }

    bool IsRegistered(const ID& id) const {
        return data.count(id) != 0;
    }
private:
    using Data = std::map<ID, Entry>;
    Data data;
};


template< class Entry, class ID >
void TRegistry<Entry, ID>::Register(const ID& id, const Entry& entry) {
    if (IsRegistered(id) == true) {
#if defined(_DEBUG)
        THROW("Class #" + std::to_string(id) + " already registered.");
#else
        return;
#endif
    }
    data[id] = entry;
}

template< class Entry, class ID >
void TRegistry<Entry, ID>::Unregister(const ID& id) {
    auto it = data.find(id);
    if (it == data.end()) {
#if defined(_DEBUG)
        THROW("Class #" + std::to_string(id) + " is not registered.");
#else
        return;
#endif
    }
    data.erase(it);
}

#endif // REGISTRY_H
