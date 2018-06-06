#ifndef RESEARCHES_TREE_H
#define RESEARCHES_TREE_H

#include "research.h"



namespace TD {


class TResearchesTree
{
public:
    using ID = TResearch::ID;



    TResearchesTree();

    void Insert(const ID& parentResearch, const TResearch& research);
    void Remove(const ID& id);

    const TResearch& GetResearch(const ID& id) const;
    TResearch& GetResearch(const ID& id);

    bool Contains(const ID& id) const;

    list<TResearch * const> GetPrevResearches(const ID& id) const;
    list<TResearch *>      GetPrevResearches(const ID& id);

private:
    using Research = TResearch;

    struct TreeEntry {
        Research data;
        list<TreeEntry> prev;

        TreeEntry(const Research& research) :
            data(research),
            prev()
        {}
    };

    using Data = std::map<ID, TreeEntry>;
    Data data;
};


} // namespace TD

#endif // RESEARCHES_TREE_H
