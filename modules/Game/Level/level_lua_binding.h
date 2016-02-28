#ifndef LEVEL_LUA_BINDING_H
#define LEVEL_LUA_BINDING_H

#include "Core/luawrapper.h"
#include "level.h"



#define BEGIN_TD_LUA_BINDING namespace TD { namespace lua_binding {
#define END_TD_LUA_BINDING } }

BEGIN_TD_LUA_BINDING


using TLevel = ::TLevel*;
using TLevelState = ::TLevel::State;
using TLevelAction = ::TLevel::Action;
using TClock = ::TLevel::Clock::Time;
using TScript = string;
using TLevelInfo = ::TLevelInfo*;
using TLevelScene = ::CSceneController*;

void loadLevel(lua::State& state, TLevel level);
void loadStage(lua::State& state, TLevel level);

void bindTLevel(lua::State& state);
void bindTLevelScene(lua::State& state);

void bindToLUA(lua::State& state);


END_TD_LUA_BINDING

#endif // LEVEL_LUA_BINDING_H
