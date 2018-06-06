#ifndef RESEARCHES_TREE_ITEM_H
#define RESEARCHES_TREE_ITEM_H

#include "GameEngine/GUI/widget.h"
#include "GameEngine/GUI/pushbutton.h"
#include "GameEngine/GUI/imagebox.h"
#include "research.h"



namespace TD {


class TResearches;
class TLevelProgress;

struct TResearchesTreeItemSource : TWidgetSource {
    TResearchInstance research;
    TResearches* controller;
    TLevelProgress* progress;

    TPushButtonSource button;
    TImageBoxSource imageBox;
};

class TResearchesTreeItemView : public TWidget
{
public:
    using TResearchInstance = TResearch*;
    using TResearchesControllerInstance = TResearches*;
    using TProgressInstance = TLevelProgress*;

    enum class State : uint {
        _min = 0,

        Disabled = 0,
        Enabled,
        CanNotResearch,
        CanResearch,
        Researched,

        _count
    };


    TResearchesTreeItemView(const TResearchesTreeItemSource& source);
    void Initialize(const TResearchesTreeItemSource& source);

    const State& GetState() const;
    void SetState(const State& value);

    void SetControllerInstance(const TResearcesControllerInstance& value);
    void SetProgressInstance(const TProgressInstance& value);

    static void slot_PrevItemResearched(TWidget* obj_, void* args);
    static void slot_TryResearch(TWidget* obj_, void* args);
    static void slot_ImageBoxClicked(TWidget* obj_, void* args);

protected:
    virtual list<Signal> _enumSignals() const override;
    virtual list<Slot> _enumSlots() const override;

    virtual void _draw(TRenderTarget& target) override;

    void _OnDisabled();
    void _OnEnabled();
    void _OnResearched();

private:
    using parent_type = TWidget;

    static constexpr TColor COLOR_LINE_DARK = 0x80A0A0A0;
    static constexpr TColor COLOR_LINE_BRIGHT = 0xA0D0D0D0;

    static const TColorModifier COLOR_MODIFIER_ENABLED  { 1.0, 1.0, 1.0 };
    static const TColorModifier COLOR_MODIFIER_DISABLED { 0.7, 0.7, 0.7 };

    static const SignalID SIGNAL_ITEM_RESEARCHED;

    static const SignalID SLOT_IMAGE_BOX_CLICKED;
    static const SignalID SLOT_PREV_ITEM_RESEARCHED;
    static const SignalID SLOT_TRY_RESEARCH;


    State m_state;
    TResearchInstance m_research;

    TResearchesControllerInstance e_controller;
    TProgressInstance e_progress;


    bool _hasEnoughCredits() const;

    std::weak_ptr<const TAbstractButton> _getButton() const;
    std::weak_ptr<TAbstractButton> _getButton();

    std::weak_ptr<const TImageBox> _getImageBox() const;
    std::weak_ptr<TImageBox> _getImageBox();

    std::weak_ptr<const TResearchesTree> _getTree() const;
    std::weak_ptr<TResearchesTree> _getTree();

    const TResearch& _getResearch() const;
    TResearch& _getResearch();

    list<std::weak_ptr<TResearchesTreeItemView>> _getPrevResearches() const;

    const TResearches& _getController() const;

    void _drawConnections(TRenderTarget& target);
};


} // namespace TD

#endif // RESEARCHES_TREE_ITEM_H
