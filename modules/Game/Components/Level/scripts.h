#ifndef LEVELSCRIPTS_H
#define LEVELSCRIPTS_H

#include "../Info/objectinfo.h"
#include "../../Core/luawrapper.h"

enum class StageScript {
	OnStageInit,
	OnStageUpdate,
	OnStageEnd
};

static const string StageScript_Value[] = {
    "OnStageInit",
    "OnStageUpdate",
    "OnStageEnd"
};


class TLevelScripts
{
public:
	class Info;

    TLevelScripts(const Info& source);
    TLevelScripts(const TLevelScripts& other) = delete;
    TLevelScripts& operator=(const TLevelScripts& other) = delete;
    ~TLevelScripts() = default;
	
    void updateData(const Info& source);
    void update();
	
    void execFile(const string& source);
    void execString(const string& data);
	
    typedef lua::Retval Retval;
	/*
        Invokes an active(game) function with given name.
	*/
    Retval exec(const string& name);
    Retval getScript(const string& name);
    bool hasScript(const string& name) const;
private:
    lua::State* state;

    void error(lua::Context& c, const string& message, const string& where_);

    void initState();
};

class TLevelScripts::Info : public TObjectInfo 
{
public:
	class Loader;
private:
	typedef TObjectInfo parent_t;
};

class TLevelScripts::Info::Loader : public TGameObjectInfoLoader 
{
public:
	void load(TLevelScripts::Info* info, std::istream& source) const;
protected:
	typedef TGameObjectInfoLoader parent_t;
};

#endif
