#ifndef GAME_ENGINE_DEBUG_H
#define GAME_ENGINE_DEBUG_H

#include <memory>
#include <fstream>

#include "GameEngine/Utility/exception.h"
#include "GameEngine/Utility/string.h"


namespace GE {

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
    using TOutputStream = std::wostream;

    static TLogger& GetInstance();

    static const char* GetFileName(const char* path);

    void initialize(TOutputStream* os = nullptr, ELogMessageLevel minLevel);

    void log(const TTextString& message,
        ELogMessageLevel level = ELogMessageLevel::Normal,
        const TTextString& position);

    void setStream(TOutputStream* os);
    void setThreshold(ELogMessageLevel threshold);

private:
    using PLogger = std::unique_ptr<TLogger>;
    static PLogger instance;

    static const size_t DefaultBufferSize;
    ELogMessageLevel minLevel;

    vector<TTextString> buffer;
    TOutputStream* outputStream;

    TLogger(TOutputStream* os = nullptr);
    ~TLogger();

    void flush();

    TTextString toString(ELogMessageLevel level) const;
};


#define GE_LOG(message, level) \
    TLogger::GetInstance().log( \
        TTextString((message)), \
        level, \
        TLogger::GetFileName(__FILE__) + ":" + __LINE__);

#define GE_THROW(message) \
    { \
        GE_LOG((message), ELogMessageLevel::Error); \
        throw exception((message)); \
    }

#define GE_ASSERT(expr, message) \
    if ((expr) == false) { \
        GE_THROW((message)); \
    }

#define GE_TRACE_LINE(message) \
    GE_LOG(__func__ + TTextString((message)), ELogMessageLevel::Trace);

#define GE_TRACE_FUNC \
    struct TTraceDummy { \
        TTraceDummy() { GE_TRACE_LINE(": Started"); } \
        ~TTraceDummy() { GE_TRACE_LINE(": Exited"); } \
    } [[maybe_unused]] traceDummy;

} // namespace GE

#endif // GAME_ENGINE_DEBUG_H
