#ifndef COMPONENT_SYSTEM_LOGICS_H
#define COMPONENT_SYSTEM_LOGICS_H

#include "GameEngine/ECS/component_system.h"
#include "GameEngine/ECS/game_engine_context.h"


GE_BEGIN_ENGINE_NAMESPACE

class CSLogicsSystem :
    public TComponentSystem
{
public:
    virtual ~CSLogicsSystem() = default;

    virtual void Update(const TTime& step, Context& context) override;
    virtual void HandleMessage(const TMessage& message,
        const TComponentHandle& sender, Context& context) override;
};

class CLogicsComponent :
    public TComponent
{
public:
    CLogicsComponent(const ID& id);
    virtual ~CLogicsComponent() = default;
};

GE_END_ENGINE_NAMESPACE

#endif // COMPONENT_SYSTEM_LOGICS_H
