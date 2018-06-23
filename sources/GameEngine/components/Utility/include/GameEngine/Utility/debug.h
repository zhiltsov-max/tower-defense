#ifndef GAME_ENGINE_DEBUG_H
#define GAME_ENGINE_DEBUG_H

#include <iostream>
#include <memory>
#include <vector>

#include "GameEngine/Utility/common.h"
#include "GameEngine/Utility/exception.h"
#include "GameEngine/Infrastructure/string.h"


GE_BEGIN_ENGINE_NAMESPACE

enum class ELogMessageLevel : unsigned char {
	_min = 0,

	undefined = 0,
	Trace,
    Debug,
	Normal,
	Warning,
	Error,
	Fatal,

	_max = Fatal
};

class TLogger {
public:
    using TOutputStream = std::ostream;

    static TLogger& GetInstance();

    static const char* GetFileName(const char* path);

    void log(const TString& message, ELogMessageLevel level,
        const TString& position);

    void setStream(TOutputStream* os = nullptr);
    void setThreshold(ELogMessageLevel threshold = ELogMessageLevel::Normal);

private:
    using PLogger = std::unique_ptr<TLogger>;
    static PLogger instance;

    static const size_t DefaultBufferSize;
    ELogMessageLevel minLevel;

    std::vector<TString> buffer;
    TOutputStream* outputStream;

    TLogger(TOutputStream* os = nullptr);
    ~TLogger();

    void flush();

    TString toString(ELogMessageLevel level) const;
};


#define GE_LOG(message, level) \
    TLogger::GetInstance().log( \
        TString((message)), \
        (level), \
        TString(TLogger::GetFileName(__FILE__)) + ":" #__LINE__);

#define GE_THROW(message) \
    { \
        GE_LOG((message), ELogMessageLevel::Error); \
        throw TException((message)); \
    }

#define GE_ASSERT(expr, message) \
    if ((expr) == false) { \
        GE_THROW((message)); \
    }

#define GE_TRACE_LINE(message) \
    GE_LOG(TString(__func__) + TString((message)), \
        ELogMessageLevel::Trace);

#define GE_TRACE_FUNC \
    struct TTraceDummy { \
        TTraceDummy() { GE_TRACE_LINE(": Started"); } \
        ~TTraceDummy() { GE_TRACE_LINE(": Exited"); } \
    } [[maybe_unused]] traceDummy;

GE_END_ENGINE_NAMESPACE

#endif // GAME_ENGINE_DEBUG_H
