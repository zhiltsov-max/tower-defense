#ifndef LEVEL_LUA_BINDING_H
#define LEVEL_LUA_BINDING_H

#include "Core/luawrapper.h"
#include "Game/Level/level.h"


#define BEGIN_TD_LUA_BINDING namespace TD { namespace lua_binding {
#define END_TD_LUA_BINDING } }

BEGIN_TD_LUA_BINDING


using TLevel = TD::TLevel *;
using TClock = TD::TLevelClock *;
using TScene = TD::TLevelScene *;

using TSceneComponent = GE::TComponent *;
using TSceneComponentID = GE::TComponent::ID;
using TSceneComponentCreateArgs = GE::TComponentCreateArgs *;
using TSceneComponentHandle = TD::TLevelScene::ComponentHandle;
using TSceneComponentPath = TD::TLevelScene::ComponentPath;
using TSceneComponentName = TD::TLevelScene::ComponentName;

using TSceneObject = TD::TLevelScene::Object;
using TSceneObjectHandle = TD::TLevelScene::ObjectHandle;
using TSceneObjectName = TD::TLevelScene::ObjectName;


void loadLevel(lua::State& state, TLevel level);
void loadStage(lua::State& state, TLevel level);

void bindTLevel(lua::State& state);
void bindTLevelScene(lua::State& state);

void bindToLUA(lua::State& state);


END_TD_LUA_BINDING

#endif // LEVEL_LUA_BINDING_H
