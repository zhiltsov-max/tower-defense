#ifndef GAME_ENGINE_CONTEXT_H
#define GAME_ENGINE_CONTEXT_H

namespace GE {

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

} // namespace GE

#endif // GAME_ENGINE_CONTEXT_H
