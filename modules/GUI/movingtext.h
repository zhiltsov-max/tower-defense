#ifndef MOVINGTEXT_H
#define MOVINGTEXT_H

#include "simpletext.h"

BEGIN_GUI

struct TMovingTextSource : TSimpleTextSource
{
    TCoordinate speed;
    bool allowFading;
    uint lifeTime; //msec
};

class TMovingText : public TSimpleText
{
public:
    typedef uint Time;

    static TWidgetRef CreateDefaultMessage(const TextString& message, const TCoordinate& position, const TColor& color = (uint)DefaultMessageColor::information);

    TMovingText(const TMovingTextSource& source);
    TMovingText(const TMovingText& other) = delete;
    TMovingText& operator=(const TMovingText& other) = delete;
    ~TMovingText() = default;

    void SetLifeTime(Time value);
    Time GetLifeTime() const;

    void SetFadeability(bool value);
    bool IsFadeable() const;

    const TCoordinate& GetSpeed() const;
    void SetSpeed(const TCoordinate& value);
private:
    typedef TSimpleText parent_type;
protected:
    const float thresholdTime = 0.5f;

    TCoordinate speed;
    bool allowFading;

    Time lifeTime; //msec
    //Temporary
    const Time createTime;

    virtual void _update() override;
};

END_GUI

#endif // MOVINGTEXT_H
