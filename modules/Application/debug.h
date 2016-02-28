#ifndef DEBUG_H
#define DEBUG_H

#include <fstream>
#include "Core/core.h"



enum class LogMessageImportance : unsigned char {
	_min = 0,

	undefined = 0,	
	Unimportant,
	Usual,
	Important,
	Warning,
	Error,
	Critical,

	_max = Critical
};

struct DebugToolsInfo
{
    static constexpr const char* DEFAULT_DEBUG_LOG_PATH = "DebugLog.txt";
    string path;


    DebugToolsInfo(const string& path = DEFAULT_DEBUG_LOG_PATH) :
        path(path)
    {}
};

class TDebugTools
{
public:
    TDebugTools(const DebugToolsInfo& info = DebugToolsInfo());
    TDebugTools(const TDebugTools& other) = delete;
	

    void log(
        const string& message,
        LogMessageImportance importance = LogMessageImportance::Usual
    );

    void log(
        const wstring& message,
        LogMessageImportance importance = LogMessageImportance::Usual
    );

private:
    using DebugLog = std::wofstream;
    DebugLog debugLog;
};


void Throw(const string& message, const string& where_);


#if defined(THROW)
    #undef THROW
#endif
#define THROW(message) \
    Throw(std::string(message), \
        std::string("Error at ") + __FILE__ + ":" + \
        std::to_string(__LINE__) + ": ");

#if defined(ASSERT)
    #undef ASSERT
#endif
#define ASSERT(expr, message) \
    if ((expr) == false) {\
        THROW(message)\
    }


#endif //DEBUG_H
