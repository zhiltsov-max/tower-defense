#ifndef SCRIPT_ENGINE_H
#define SCRIPT_ENGINE_H

#include "Core/luawrapper.h"



class TScriptEngine {
public:
    TScriptEngine();

    typedef lua::State Raw;
    const Raw& Get() const;
    Raw& Get();
private:
    Raw raw;


    void initialize();
};

#endif // SCRIPT_ENGINE_H
