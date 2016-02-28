#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include "level_code.h"



class TGameEngine;

namespace TD {


class TLevel;

class TLevel::Loader
{
public:
    void load(TLevel& level,
        TLevelCode& code,
        TGameEngine* engine);
private:
    void loadInfo(TLevel& level, TLevelCode& code);

    /* Level LUA loader.
    It have to implement all level-specific behaviour of loading process
    i.e. new game objects/components import, method overrides,
    scene loading, progress managing, etc.
    */
    void loadScript(TLevel& level);

    void loadScene(TLevel& level);
};


} // namespace TD

#endif // LEVEL_LOADER_H
