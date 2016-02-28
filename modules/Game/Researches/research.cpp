#include "research.h"



namespace TD {


TResearch::TResearch(const TResearch::ID& id) :
    id(id)
{}

const TResearch::ID& TResearch::GetID() const {
    return id;
}

void TResearch::SetResearched(bool value) {
    researched = value;
}

bool TResearch::IsResearched() const {
    return researched;
}


} // namespace TD


