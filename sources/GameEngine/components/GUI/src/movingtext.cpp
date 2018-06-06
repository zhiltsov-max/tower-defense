#include "movingtext.h"
#include "Application/application.h"


BEGIN_GUI

TMovingText::TMovingText(const TMovingTextSource& source) :
    parent_type(source),    
    speed(source.speed),
    allowFading(source.allowFading),
    lifeTime(source.lifeTime),
    createTime(app()->getTime())
{}

void TMovingText::_update() {
    parent_type::_update();
    if (allowFading == true) {
        auto currentTime = app()->getTime() - createTime;
        if (lifeTime * thresholdTime < currentTime) {
            colorModifier.aMod = 1.0;
        } else {
            colorModifier.aMod = 1.0 - double(currentTime) / double(lifeTime);
        }

        if (lifeTime <= currentTime) {
            SetVisibility(false);
            parent.lock()->RemoveChild(name);
            return;
        }
    }

    position += speed;
}

TWidgetRef TMovingText::CreateDefaultMessage(
    const TextString& message,
    const TCoordinate& position,
    const TColor& color)
{
    TMovingTextSource src;
    src.lifeTime = (time_t)1.5f * 1000.f;
    src.speed = TCoordinate(0.f, -1.f);

    src.text = message;
    src.font = TFont("Calibri.ttf", 20, TCustomFont::Style::Bold);
    src.size = TSize(100.f, 22.f);
    src.textColor = TColor(color);
    src.position = position + TCoordinate(-src.font.GetTextWidth(message) * 0.5f, 0.f);

    src.borderColor = TColor(20, 20, 20);
    src.borderOffset = TCoordinate(2.f, 2.f);
    src.borderSize = 1;

    src.show = true;

    src.margin = TPadding();
    src.name = "InGameUpfloatingMessage" + app()->getTime();

    src.allowFading = true;

    TWidgetRef ref(new TMovingText(src));
    return ref;
}



void TMovingText::SetLifeTime(Time value) {
    lifeTime = value;
}

TMovingText::Time TMovingText::GetLifeTime() const {
    return lifeTime;
}


void TMovingText::SetFadeability(bool value) {
    allowFading = value;
}

bool TMovingText::IsFadeable() const {
    return allowFading;
}


const TCoordinate& TMovingText::GetSpeed() const {
    return speed;
}

void TMovingText::SetSpeed(const TCoordinate& value) {
    speed = value;
}

END_GUI
