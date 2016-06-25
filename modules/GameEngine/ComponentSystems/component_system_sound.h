#ifndef COMPONENT_SYSTEM_SOUND_H
#define COMPONENT_SYSTEM_SOUND_H

#include "GameEngine/component_system.h"


namespace GE {

class CSSoundSystem : public TComponentSystem
{
public:
    virtual ~CSSoundSystem() = default;

    virtual void Update(const TTime& step, Context& context) override;
    virtual void Play(const TTime& step, Context& context);
};

class CSoundComponent : /*Abstract*/
    public TComponent
{
public:
    CSoundComponent(const ID& id);
    virtual ~CSoundComponent() = default;
};

} //namespace GE

#endif // COMPONENT_SYSTEM_SOUND_H
