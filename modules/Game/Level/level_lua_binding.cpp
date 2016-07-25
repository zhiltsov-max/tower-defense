#include "level_lua_binding.h"


using namespace lua;


LUAPP_ARG_CONVERT(TD::lua_binding::TLevel,
    { return static_cast<TD::lua_binding::TLevel>(val.cast<LightUserData>()); }
)
LUAPP_RV_CONVERT (TD::lua_binding::TLevel,
    { return context.ret(static_cast<lua::LightUserData>(val)); }
)

LUAPP_ARG_CONVERT(TD::lua_binding::TClock,
    { return static_cast<TD::lua_binding::TClock>(val.cast<LightUserData>()); }
)
LUAPP_RV_CONVERT (TD::lua_binding::TClock,
    { return context.ret(static_cast<lua::LightUserData>(val)); }
)

LUAPP_ARG_CONVERT(TD::lua_binding::TScene,
    { return static_cast<TD::lua_binding::TScene>(val.cast<LightUserData>()); }
)
LUAPP_RV_CONVERT (TD::lua_binding::TScene,
    { return context.ret(static_cast<lua::LightUserData>(val)); }
)


BEGIN_TD_LUA_BINDING

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


TClock eTLevel_GetClock(TLevel self) {
    return &self->GetClock();
}

TScene eTLevel_GetScene(TLevel self) {
    return &self->GetScene();
}

Retval exportTLevel(Context& ctx) {
    ctx.global["TLevel"] = Table::records(ctx,
        "GetClock",     eTLevel_GetClock,
        "GetScene",     eTLevel_GetScene,

        "initialize_preScene",  nil,
        "initialize_postScene", nil
    );

    return ctx.ret();
}

void bindTLevel(State& state) {
    state.call(mkcf<exportTLevel>);
}

END_TD_LUA_BINDING


LUAPP_ARG_CONVERT(TD::lua_binding::TSceneComponent,
    { return static_cast<TD::lua_binding::TSceneComponent>(val.cast<LightUserData>()); }
)
LUAPP_RV_CONVERT (TD::lua_binding::TSceneComponent,
    { return context.ret(static_cast<lua::LightUserData>(val)); }
)

LUAPP_ARG_CONVERT(TD::lua_binding::TSceneComponentCreateArgs,
    { return static_cast<TD::lua_binding::TSceneComponentCreateArgs>(val.cast<LightUserData>()); }
)
LUAPP_RV_CONVERT (TD::lua_binding::TSceneComponentCreateArgs,
    { return context.ret(static_cast<lua::LightUserData>(val)); }
)

LUAPP_ARG_CONVERT(TD::lua_binding::TSceneComponentID,
    { return static_cast<TD::lua_binding::TSceneComponentID>(val.cast<int>()); }
)
LUAPP_RV_CONVERT (TD::lua_binding::TSceneComponentID,
    { return context.ret(static_cast<int>(val)); }
)

LUAPP_USERDATA(TD::lua_binding::TSceneComponentHandle, "TSceneComponentHandle")
LUAPP_USERDATA(TD::lua_binding::TSceneComponentPath, "TSceneComponentPath")
LUAPP_USERDATA(TD::lua_binding::TSceneObject, "TSceneObject")


BEGIN_TD_LUA_BINDING

TSceneObject eTSceneObject_Create() {
    return TSceneObject();
}

TSceneComponentHandle
eTSceneObject_AtName(TSceneObject& self, const TSceneComponentName& name) {
    return self[name];
}

TSceneComponentHandle
eTSceneObject_AtHandle(TSceneObject& self,
    const TSceneComponentHandle& handle)
{
    return self[handle];
}

TSceneComponentHandle
eTSceneObject_RemoveComponentWithName(TSceneObject& self,
    const TSceneComponentName& name)
{
    return self.RemoveComponent(name);
}

TSceneComponentHandle
eTSceneObject_RemoveComponentWithHandle(TSceneObject& self,
    const TSceneComponentHandle& handle)
{
    return self.RemoveComponent(handle);
}

bool eTSceneObject_HasComponentWithName(TSceneObject& self,
    const TSceneComponentName& name)
{
    return self.HasComponent(name);
}

bool
eTSceneObject_HasComponentWithHandle(TSceneObject& self,
    const TSceneComponentHandle& handle)
{
    return self.HasComponent(handle);
}

Retval exportTSceneObject(Context& ctx) {
    ctx.global["TSceneObject"] = Table::records(ctx,
        "create", eTSceneObject_Create,
        "atName", eTSceneObject_AtName,
        "atHandle", eTSceneObject_AtHandle,
        "getHandle", GE::TSceneObject::GetHandle,
        "addComponent", GE::TSceneObject::AddComponent,
        "removeComponentWithName", eTSceneObject_RemoveComponentWithName,
        "removeComponentWithHandle", eTSceneObject_RemoveComponentWithHandle,
        "hasComponentWithName", eTSceneObject_HasComponentWithName,
        "hasComponentWithHandle", eTSceneObject_HasComponentWithHandle,
        "hasComponents", GE::TSceneObject::HasComponents
    );

    ctx.global["SceneObject"] = eTSceneObject_Create;
    ctx.global["TSceneObject"]["__index"] = ctx.global["TSceneObject"];
    ctx.global["TSceneObject"].mt() = ctx.global["TSceneObject"];

    return ctx.ret();
}


TSceneComponentHandle
eTScene_CreateComponent(TScene self, const TSceneComponentID& id,
    TSceneComponentCreateArgs args)
{
    return self->CreateComponent(id, args);
}

void eTScene_RemoveComponentWithHandle(TScene self,
    const TSceneComponentHandle& handle)
{
    self->RemoveComponent(handle);
}

void eTScene_RemoveComponentWithPath(TScene self,
    const TSceneComponentPath& path)
{
    self->RemoveComponent(self->FindComponent(path));
}

TSceneComponentHandle
eTScene_FindComponent(TScene self, const TSceneComponentPath& path) {
    return self->FindComponent(path);
}

bool
eTScene_HasComponentWithPath(TScene self, const TSceneComponentPath& path) {
    return self->FindComponent(path) !=
        TD::TLevelScene::ComponentHandle::Undefined;
}

bool
eTScene_HasComponentWithHandle(TScene self,
    const TSceneComponentHandle& handle)
{
    return self->GetComponent(handle) != nullptr;
}

TSceneComponent
eTScene_GetComponent(TScene self, const TSceneComponentHandle& handle) {
    return self->GetComponent(handle);
}

TSceneObjectHandle
eTScene_FindSceneObject(TScene self, const TSceneObjectName& name) {
    return self->FindSceneObject(name);
}

TSceneObject
eTScene_GetSceneObject(TScene self, const TSceneObjectHandle& handle) {
    return self->GetSceneObject(handle);
}

bool eTScene_HasObjectWithName(TScene self, const TSceneObjectName& name) {
    return self->HasObject(name);
}

bool
eTScene_HasObjectWithHandle(TScene self, const TSceneObjectHandle& handle) {
    return self->HasObject(handle);
}

TSceneObjectHandle
eTScene_AddSceneObject(TScene self, const TSceneObjectName& name,
    const TSceneObject& sceneObject)
{
    return self->AddSceneObject(name, sceneObject);
}

TSceneObject
eTScene_RemoveSceneObjectWithName(TScene self, const TSceneObjectName& name) {
    return self->RemoveSceneObject(name);
}

TSceneObject
eTScene_RemoveSceneObjectWithHandle(TScene self,
    const TSceneObjectHandle& handle)
{
    return self->RemoveSceneObject(handle);
}

void eTScene_Clear(TScene self) {
    self->Clear();
}

bool eTScene_IsEmpty(TScene self) {
    return self->IsEmpty();
}

Retval exportTScene(Context& ctx) {
    ctx.global["TScene"] = Table::records(ctx,
        "createComponent", eTScene_CreateComponent,
        "removeComponentWithHandle", eTScene_RemoveComponentWithHandle,
        "removeComponentWithPath", eTScene_RemoveComponentWithPath,
        "findComponent", eTScene_FindComponent,
        "getComponent", eTScene_GetComponent,
        "hasComponentWithPath", eTScene_HasComponentWithPath,
        "hasComponentWithHandle", eTScene_HasComponentWithHandle,
        "addObject", eTScene_AddSceneObject,
        "removeObjectWithHandle", eTScene_RemoveSceneObjectWithHandle,
        "removeObjectWithName", eTScene_RemoveSceneObjectWithName,
        "findObject", eTScene_FindSceneObject,
        "getObject", eTScene_GetSceneObject,
        "hasObjectWithName", eTScene_HasObjectWithName,
        "hasObjectWithHandle", eTScene_HasObjectWithHandle,
        "isEmpty", eTScene_IsEmpty,
        "clear", eTScene_Clear
    );

    ctx.global["TScene"]["__index"] = ctx.global["TScene"];
    ctx.global["TScene"].mt() = ctx.global["TScene"];

    return ctx.ret();
}

void bindTScene(State& state) {
    state.call(mkcf<exportTScene>);
}


void bindToLUA(State& state) {
    bindTLevel(state);
    bindTScene(state);
}

END_TD_LUA_BINDING
