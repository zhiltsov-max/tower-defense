#ifndef IMAGEBOX_H
#define IMAGEBOX_H

#include "gui_main.h"
#include "menuobject.h"

BEGIN_GUI

struct TImageBoxSource : TMenuObjectSource
{
    TImageSource image;
    TColor color;
};

class TImageBox : public TMenuObject
{
public:
    typedef TImageContainer Image;

    TImageBox(const TImageBoxSource& source);
    TImageBox(const TImageBox& other) = delete;
    TImageBox& operator=(const TImageBox& other) = delete;
    ~TImageBox() = default;

    const TColor& GetColor() const;
    void SetColor(const TColor& value);

    bool HasImage() const;
    const Image& GetImage() const;
    void SetImage(Image&& value);
private:
    typedef TMenuObject parent_t;
protected:
    Image image;

    TColor color;
    TColorModifier colorModifier;

    TColor _currentColor() const;
    virtual void _draw(TRenderTarget& target) override;

    virtual void _OnImageChanged();
};

END_GUI

#endif // IMAGEBOX_H
