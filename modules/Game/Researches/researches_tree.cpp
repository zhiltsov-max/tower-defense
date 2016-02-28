#include "researches_tree.h"
#include "Core/core.h"



namespace TD {

TResearchesTree::TResearchesTree() :
    data()
{
    data.emplace(TResearch(0));
}

void TResearchesTree::Insert(const ID& parentResearch,
    const TResearch& research)
{
    ASSERT( Contains(parentResearch) == true ,
            "Parent research is unknown.")
    ASSERT( Contains(research.GetID()) == false ,
            "Research already exists.")

    auto& entry = data[research.GetID()];
    entry.prev.emplace_back(parentResearch);
}

void TResearchesTree::Remove(const ID& id) {
    auto& it = data.find(id);
    if (it == data.end()) {
#if defined(_DEBUG)
        ERROR("Attempt to remove an unexisting item.");
#else
        return;
#endif // _DEBUG
    }

    data.erase(it);

    for (auto& entry : data) {
        std::remove_if(entry.prev.begin(), entry.prev.end(),
            [&](const TreeEntry& e){
                return e.data.GetID() == id;
            }
        );
    }
}

bool TResearchesTree::Contains(const ID& id) const {
    return data.count(id) != 0;
}

const TResearch& TResearchesTree::GetResearch(const ID& id) const {
    return data.at(id).data;
}

TResearch& TResearchesTree::GetResearch(const ID& id) {
    return data.at(id).data;
}

list<TResearch *const> TResearchesTree::GetPrevResearches(const TResearch::ID& id) const {
    list<TResearch *const> result;
    for(const auto& entry : at(id).prev) {
        result.emplace_back(&entry);
    }
    return result;
}

list<TResearch *> TResearchesTree::GetPrevResearches(const TResearch::ID& id) {
    list<TResearch *> result;
    for(auto& entry : at(id).prev) {
        result.emplace_back(&entry);
    }
    return result;
}

} // namepsace TD
