#ifndef RESEARCHES_TREE_VIEW_H
#define RESEARCHES_TREE_VIEW_H

#include "Game/Components/components_list.h"



namespace TD {


class CResearchesTreeView : public CUiComponent
{
public:
    static std::unique_ptr<TComponent> Create(const TComponentCreateArgs* args);


    CResearchesTreeView();
    virtual ~CResearchesTreeView();

    virtual void Update() override;
    virtual void HandleMessage(const TMessage& message) override;
    virtual void Subscribe(TComponentSystem* system) override;
    virtual void Unsubscribe(TComponentSystem* system) override;

private:
    using parent_type = CUiComponent;
};


template<>
struct ComponentID< CResearchesTreeView > {
    static constexpr ComponentID value = ComponentID::ResearchesTreeView;
};

template<>
struct ComponentClass< CResearchesTreeView > {
    static constexpr ComponentClass value = ComponentClass::ui;
};


} // namespace TD

#endif // RESEARCHES_TREE_VIEW_H
