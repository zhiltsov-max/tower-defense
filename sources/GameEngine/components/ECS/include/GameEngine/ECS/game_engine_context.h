#ifndef GAME_ENGINE_CONTEXT_H
#define GAME_ENGINE_CONTEXT_H

#include "GameEngine/utility.h"


GE_BEGIN_ENGINE_NAMESPACE

class TGameEngine;
class TScene;
struct TGameEngineContext
{
    TGameEngine* engine;
    TScene* scene;

    TGameEngineContext(TGameEngine* engine = nullptr, TScene* scene = nullptr) :
        engine(engine),
        scene(scene)
    {}
};

GE_END_ENGINE_NAMESPACE

#endif // GAME_ENGINE_CONTEXT_H
