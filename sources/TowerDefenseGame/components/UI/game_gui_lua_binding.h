#ifndef GAME_GUI_LUA_BINDING_H
#define GAME_GUI_LUA_BINDING_H

#include "game_gui_main.h"
#include "../GUI/gui_lua_binding.h"

#define BEGIN_GAME_GUI_LUA_BINDING BEGIN_GAME_GUI namespace lua_binding {
#define END_GAME_GUI_LUA_BINDING } END_GAME_GUI

/* GameInfoWindow binding
 * Disabled by: GAME_GUI_LUA_NO_GAMEINFOWINDOW_BINDING
*/
#if !defined(GAME_GUI_LUA_NO_GAMEINFOWINDOW_BINDING)
    #include "gameinfowindow.h"

BEGIN_GAME_GUI_LUA_BINDING
    using TGameInfoWindow = std::shared_ptr<Game::GUI::TGameInfoWindow>;
    using TGameInfoWindowSource = Game::GUI::TGameInfoWindowSource;
END_GAME_GUI_LUA_BINDING

    LUAPP_ARG_CONVERT(Game::GUI::lua_binding::TGameInfoWindow, { return std::dynamic_pointer_cast<Game::GUI::TGameInfoWindow>(val.cast<GUI::lua_binding::TWidget>()); })
    LUAPP_RV_CONVERT (Game::GUI::lua_binding::TGameInfoWindow, { return context.ret(GUI::lua_binding::TWidget(val)); })
#endif


#endif // GAME_GUI_LUA_BINDING_H
