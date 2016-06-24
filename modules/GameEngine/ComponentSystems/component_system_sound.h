#ifndef COMPONENT_SYSTEM_SOUND_H
#define COMPONENT_SYSTEM_SOUND_H

#include "GameEngine/component_system.h"
#include "GameEngine/engine_core.h"


namespace GE {

class CSSoundSystem : public TComponentSystem
{
public:
    virtual ~CSSoundSystem() = default;

    virtual void Update(const TTime& step) override;
    virtual void Play(const TTime& step);
};

class CSoundComponent : public TComponent /*Abstract*/
{
public:
    CSoundComponent(const ID& id);
    virtual ~CSoundComponent() = default;
};

} //namespace GE

#endif // COMPONENT_SYSTEM_SOUND_H
