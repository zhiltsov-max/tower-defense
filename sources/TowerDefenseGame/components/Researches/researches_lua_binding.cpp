#include "researches_lua_binding.h"

using namespace lua;

BEGIN_TD_LUA_BINDING

LUAPP_USERDATA(TResearch, "TResearch")

void eTResearch_Destroy(TResearch& self) {
    self.~TResearch();
}

Retval exportTResearch(Context& ctx) {
    ctx.mt<TResearch>() = Table::records(ctx,
        "__gc",             eTResearch_Destroy,

        "GetID",            TResearch::GetID,
        "GetCost",          TResearch::GetCost,
        "GetDescription",   TResearch::GetDescription,

        "IsResearched",     TResearch::IsResearched,
        "SetResearched",    TResearch::SetResearched

    );
    ctx.global["TResearch"] = ctx.mt<TResearch>();
    return ctx.ret();
}

void bindTResearch(State& state) {
    state.call(mkcf<exportTResearch>);
}

void bindTResearchesController(State& state) {
    state.call(mkcf<exportTResearchesController>);
}

void bindTResearchesTree(State& state) {
    state.call(mkcf<exportTResearchesTree>);
}

void bindResearches(State& state) {
    bindTResearch(state);
    bindTResearchesTree(state);
    bindTResearchesController(state);
}

/*
#define BIND_CLASS( NAME, EXTERNAL_NAME ) \
BEGIN_TD_LUA_BINDING \
    NAME e##NAME##_Create (){return NAME ();} \
    void e##NAME##_Destroy(NAME &self){NAME.~NAME();} \
    Retval export##NAME(Context& ctx) { \
        ctx.mt<NAME>() = Table::records(ctx, \
            "Create",   e##NAME##_Create, \
            "__gc",     e##NAME##_Destroy \
        ); \
        ctx.global[EXTERNAL_NAME] = ctx.mt<NAME>(); \
        return ctx.ret(); \
    } \
END_TD_LUA_BINDING
*/

END_TD_LUA_BINDING
