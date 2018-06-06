#ifndef ABSTRACT_WINDOW_H
#define ABSTRACT_WINDOW_H

#include "widget.h"
#include "textarea.h"



BEGIN_GUI


struct TAbstractWindowSource : TWidgetSource
{
    bool enabled;
    bool allowMoving;

    float headerHeight;
    TColor headerColor;
    TTextAreaSource headerText;

    TColor color;

    TImageSource image;

    TPadding innerElementsPadding;
    TSize minSize;
    TSize maxSize;

    TAbstractWindowSource() = default;
};

class TAbstractWindow : public TWidget /*Abstract*/
{
public:
    typedef TImageContainer Image;


    ~TAbstractWindow() = default;

    virtual bool IsEnabled() const;
    virtual void SetEnabled(bool value);
    void Enable();
    void Disable();

    virtual bool IsMoveable() const;
    virtual void SetMoveability(bool value);

    virtual bool HasHeader() const;
    virtual float GetHeaderHeight() const;
    virtual void SetHeaderHeight(float value);

    virtual const TextString& GetTitle() const;
    virtual void SetTitle(const TextString& value);

    virtual const TFont& GetTitleFont() const;
    virtual void SetTitleFont(const TFont& value);

    virtual const TColor& GetTitleColor() const;
    virtual void SetTitleColor(const TColor& value);

    virtual const TColor& GetHeaderColor() const;
    virtual void SetHeaderColor(const TColor& value);

    virtual const TColor& GetColor() const;
    virtual void SetColor(const TColor& value);

    virtual bool HasImage() const;
    virtual const Image& GetImage() const;
    virtual void SetImage(Image&& value);

    virtual const TPadding& GetInnerPadding() const;
    virtual void SetInnerPadding(const TPadding& value);

    virtual bool IsResizable() const;
    virtual void SetMinSize(const TSize& value);
    virtual void SetMaxSize(const TSize& value);
    virtual const TSize& GetMinSize() const;
    virtual const TSize& GetMaxSize() const;
    virtual void SetSize(const TSize& value);

    virtual TPadding GetInnerBorder() const;

private:
    typedef TWidget parent_type;


    TColor _currentColor() const;
    TColor _currentHeaderColor() const;

protected:
    enum class State : uchar {
        _min = 0,
        undefined = 0,

        Normal = 1,
        Moving = 2,
        Disabled = 3,

        _max = Disabled
    };
    //Flags
    State state;
    bool allowMoving;
    //Header
    float headerHeight;
    TColor headerColor;
    typedef std::unique_ptr<TAbstractTextArea> HeaderText;
    HeaderText headerText;
    //Background
    TColor color;
    TColorModifier colorModifier;

    Image image;
    //Size
    TPadding innerElementsPadding;
    TSize minSize;
    TSize maxSize;
    //Temporary
    TCoordinate clickPosition;
    bool clicked;


    TAbstractWindow(const TAbstractWindowSource& source);
    TAbstractWindow(const TAbstractWindow& other) = delete;
    TAbstractWindow& operator=(const TAbstractWindow& other) = delete;

    virtual void _update() override;
    virtual void _updateChildren() override;
    virtual void _draw(TRenderTarget& target) override;

    virtual bool _isMouseOverHeader() const;

    virtual void _handle_mouseButtonPressed(
        const TEvent_MouseClick& event, bool& consume) override;
    virtual void _handle_mouseButtonReleased(
        const TEvent_MouseClick& event, bool& consume) override;
    virtual void _handle_mouseMove(
        const TEvent_MouseMoved& event, bool& consume) override;

    virtual void _OnMoveabilityChanged();
    virtual void _OnEnabled();
    virtual void _OnDisabled();
    virtual void _OnHeaderChanged();
    virtual void _OnImageChanged();

private:
    State _getState() const;
};


END_GUI

#endif // ABSTRACT_WINDOW_H
