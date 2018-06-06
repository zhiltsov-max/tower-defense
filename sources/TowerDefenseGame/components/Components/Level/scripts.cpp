#include "scripts.h"
#include "..\..\Application\application.h"


static const string levelDir = "Data/Levels/";

TLevelScripts::TLevelScripts(const Info& source) :
    state()
{
    initState();

    if (source.empty() == true) {
        return;
    }

    if (source.contains("pathes") == true) {
        string pathes_raw = *source["pathes"].as<string>();
        pathes_raw = pathes_raw.substr(2, pathes_raw.size() - 2);
        std::vector<string> pathes = String::split(pathes_raw, ',');
        for(const auto& entry : pathes) {
            execFile(entry);
        }
    }
}


void TLevelScripts::updateData(const Info& source) {
    if (source.empty() == true) {
        return;
    }

    if (source.contains("pathes") == true) {
        string pathes_raw = *source["pathes"].as<string>();
        pathes_raw = pathes_raw.substr(2, pathes_raw.size() - 2);
        std::vector<string> pathes = String::split(pathes_raw, ',');
        for(const auto& entry : pathes) {
            execFile(entry);
        }
    }
}


void TLevelScripts::update() {
    exec(StageScript_Value[StageScript::OnStageUpdate]);
}

void TLevelScripts::execFile(const string& source) {
    if (source.empty() == true) {
        return;
    }

    state.runFile(levelDir + source);
}

void TLevelScripts::execString(const string& data) {
    state.runString(data);
}

Retval TLevelScripts::exec(const string& name) {
    auto ctx = lua::Context(state);

    //find function
    try {
        lua::Valset ret = ctx.global["HasActiveFunction"].pcall(name);
        if (ret.cast<bool>() == false) {
#if _DEBUG_
            error(ctx, "Function '" + name + "' was not found.", "TLevelScripts::exec");
#else
            return ctx.ret();
#endif
        }
    } catch (std::exception& e) {
#if _DEBUG_
        throw_("LUA function call 'HasActiveFunction' failed: " + e.what(), "TLevelScripts::exec");
#else
        return ctx.ret();
#endif
    }

    //get function
    try {
        return ctx.global["GetActiveFunction"].pcall(name);
    } catch (std::exception& e) {
#if _DEBUG_
        throw_("LUA function call 'GetActiveFunction' failed: " + e.what(), "TLevelScripts::exec");
#else
        return ctx.ret();
#endif
    }

    return ctx.ret();
}

Retval TLevelScripts::getScript(const string& name) {
    return lua::Context(state).global[name];
}

bool TLevelScripts::hasScript(const string& name) const {
    int stackStartPos = lua_gettop(state);
    lua_getglobal(state, name);
    bool res = lua_isfunction(state, lua_gettop());
    lua_pop(state, lua_gettop() - stackStartPos);
    return res;
}

void TLevelScripts::error(lua::Context& c, const string& message, const string& where_) {
    DebugTools::log("@TLevelScripts::" + where + ": Error!~n~t" + message, LogMessageImportance::Error);
    interface::showErrorsFromLUA(state);
}

void TLevelScripts::initState() {
    state->runFile("Modules/interfaceClasses.lua");
    state->runFile("Modules/GameinterfaceClasses.lua");
    LuaBindings::ImportInterfaceFunctions(state);
}




void TLevelScripts::Info::Loader::load(TLevelScripts::Info* info, std::istream& source) const {
    if (info == nullptr) {
        throw_("Storage is null.", "TLevelScripts::Info::Loader::load");
    }

    string buffer;

    std::getline(source, buffer);
    (*info)["pathes"].as<string>() = new string(buffer);
}
