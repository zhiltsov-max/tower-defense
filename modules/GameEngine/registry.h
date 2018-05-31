#ifndef REGISTRY_H
#define REGISTRY_H

#include <sstream>
#include "Core/core.h"


namespace GE {

template< class Entry_, class ID_ >
class TRegistry
{
public:
    using Entry = Entry_;
    using ID = ID_;

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
    using Data = std::map<ID, Entry>;
    Data data;
};

template< class Entry, class ID >
void TRegistry<Entry, ID>::Register(const ID& id, const Entry& entry) {
    if (IsRegistered(id) == true) {
        std::stringstream ss;
        ss << "Class #" << id << " already registered.";
        THROW(ss.str())
    }

    data[id] = entry;
}

template< class Entry, class ID >
void TRegistry<Entry, ID>::Unregister(const ID& id) {
    auto it = data.find(id);
    if (it == data.end()) {
        std::stringstream ss;
        ss << "Class #" << id << " is not registered.";
        THROW(ss.str());
    }
    data.erase(it);
}

} // namespace GE

#endif // REGISTRY_H
