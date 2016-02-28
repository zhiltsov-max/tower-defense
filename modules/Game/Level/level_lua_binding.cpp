#include "level_lua_binding.h"



using namespace lua;

BEGIN_TD_LUA_BINDING


LUAPP_ARG_CONVERT(TD::lua_binding::TLevel, { return static_cast<lua::LightUserData>(val); })
LUAPP_RV_CONVERT (TD::lua_binding::TLevel, { return context.ret(static_cast<lua::LightUserData>(val)); })

LUAPP_ARG_CONVERT(TD::lua_binding::TLevelState, { return static_cast<uint>(val); })
LUAPP_RV_CONVERT (TD::lua_binding::TLevelState, { return context.ret(static_cast<uint>(val)); })

LUAPP_ARG_CONVERT(TD::lua_binding::TLevelAction, { return static_cast<uint>(val); })
LUAPP_RV_CONVERT (TD::lua_binding::TLevelAction, { return context.ret(static_cast<uint>(val)); })

LUAPP_ARG_CONVERT(TD::lua_binding::TLevelInfo, { return static_cast<lua::LightUserData>(val); })
LUAPP_RV_CONVERT (TD::lua_binding::TLevelInfo, { return context.ret(static_cast<lua::LightUserData>(val)); })

LUAPP_ARG_CONVERT(TD::lua_binding::TLevelScene, { return static_cast<lua::LightUserData>(val); })
LUAPP_RV_CONVERT (TD::lua_binding::TLevelScene, { return context.ret(static_cast<lua::LightUserData>(val)); })


void loadLevel(State& state, TLevel level) {
    Context ctx(state.getRawState(), Context::initializeExplicitly);
    Value initialize = ctx.global["TLevel"]["initialize"];
    if (initialize.is<Nil>() == false) {
        initialize.pcall(level);
    }
}

void loadStage(State& state, TLevel level) {
    Context ctx(state.getRawState(), Context::initializeExplicitly);
    Value initialize = ctx.global["TStage"]["initialize"];
    if (initialize.is<Nil>() == false) {
        initialize.pcall(level);
    }
}


const TLevelState& eTLevel_GetState(TLevel self) {
    return self->getState();
}
void eTLevel_SetState(TLevel self, const TLevelState& value) {
    self->setState(value);
}
const TLevelAction& eTLevel_GetAction(TLevel self) {
    return self->getAction();
}
void eTLevel_SetAction(TLevel self, const TLevelAction& value) {
    self->setAction(value);
}
TClock eTLevel_GetClock(TLevel self) {
    return self->getClock().get();
}
TLevelScene eTLevel_GetScene(TLevel self) {
    return &self->getScene();
}

Retval exportTLevel(Context& ctx) {
    ctx.global["TLevel"] = Table::records(ctx,
        "GetState",     eTLevel_GetState,
        "SetState",     eTLevel_SetState,
        "GetAction",    eTLevel_GetAction,
        "SetAction",    eTLevel_SetAction,
        "GetClock",     eTLevel_GetClock,
        "GetInfo",      eTLevel_GetInfo,
        "GetScene",     eTLevel_GetScene,

        "initialize_preScene",  nil,
        "initialize_postScene", nil
    );

    ctx.global["TLevel"]["Action"] = Table::records(ctx,
        "Exit",         0,
        "Pause",        1,
        "Statistics",   2,
        "Loading",      3,
        "Play",         4
    );

    ctx.global["TLevel"]["State"] = Table::records(ctx,
        "NotRunning",   0,
        "Running",      1,
        "Failed",       2,
        "Completed",    3
    );

    return ctx.ret();
}

void bindTLevel(State& state) {
    state.call(mkcf<exportTLevel>);
}


void bindToLUA(State& state) {
    bindTLevel(state);
    bindTLevelScene(state);
}


END_TD_LUA_BINDING
