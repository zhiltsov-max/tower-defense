#include "researches_tree_view.h"



namespace TD {


std::unique_ptr<TComponent> CResearchesTreeView::Create(const TComponentCreateArgs* args) {

}

CResearchesTreeView::CResearchesTreeView() :
    parent_type(ComponentID<CResearchesTreeView>::value)
{

}


} // namespace TD
