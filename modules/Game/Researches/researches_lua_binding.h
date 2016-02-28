#ifndef RESEARCHES_LUA_BINDING_H
#define RESEARCHES_LUA_BINDING_H

#define BEGIN_TD_LUA_BINDING namespace TD { namespace lua_binding {
#define END_TD_LUA_BINDING } }

#include "../../../Core/luawrapper.h"


BEGIN_TD_LUA_BINDING

/*
 * Research LUA binding.
*/
#include "research.h"

using TResearch = ::TResearch;
using TResearchID = ::TResearch::ID;
void bindTResearch(lua::State& state);

/*
 * Researches controller LUA binding.
*/
#include "researches_controller.h"

using TResearchesController = ::TResearches*;
using TResearchesTree = ::TResearchesTree*;
void bindTResearchesController(lua::State& state);
void bindTResearchesTree(lua::State& state);

#include "researches_tree_item_view.h"


void bindResearches(lua::State& state);

END_TD_LUA_BINDING

#endif // RESEARCHES_LUA_BINDING_H
