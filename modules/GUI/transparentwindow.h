#ifndef TRANSPARENTWINDOW_H
#define TRANSPARENTWINDOW_H

#include "window.h"

BEGIN_GUI

struct TTransparentWindowSource : TWindowSource
{
    double thresholdOpacity;
    double maxOpacity;
    double minOpacity;
    double opacityChangingSpeed;
};

class TTransparentWindow : public TWindow
{
public:
    TTransparentWindow(const TTransparentWindowSource& source);
    TTransparentWindow(const TTransparentWindow& other) = delete;
    TTransparentWindow& operator=(const TTransparentWindow& other) = delete;
    ~TTransparentWindow() = default;

    void SetThresholdOpacity(double value = 128.0);
    double GetThresholdOpacity() const;

    void SetMinOpacity(double value);
    void SetMaxOpacity(double value);
    double GetMinOpacity() const;
    double GetMaxOpacity() const;
protected:
    typedef TWindow parent_type;

    double thresholdOpacity;
    double maxOpacity;
    double minOpacity;
    double opacityChangingSpeed; // % per sec.

    virtual void _update() override;
    virtual void _updateOpacity();

    virtual void _drawChildren(TRenderTarget& target) override;
};

END_GUI

#endif // TRANSPARENTWINDOW_H
