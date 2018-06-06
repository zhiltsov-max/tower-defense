#include "debug.h"

#include <ios>
#include <iostream>

#include "application.h"



TDebugTools::TDebugTools(const DebugToolsInfo& info) {
    debugLog.rdbuf()->pubsetbuf(nullptr, 0); //make unbuffered I/O
    debugLog.open(info.path, std::ios_base::trunc);

    ASSERT(debugLog.is_open() == true,
        "Unable to open file '" + info.path + "'.");
}
	
void TDebugTools::log(const std::string& message,
    LogMessageImportance importance)
{
    log(String::toWide(message), importance);
}

void TDebugTools::log(const std::wstring& message,
    LogMessageImportance importance)
{
#if defined(_DEBUG)
    std::wcerr << message << std::endl;
#endif
    debugLog << L"Log message {" << (int)importance <<
        L"}: " << message << std::endl;
}



void Throw(const string& message, const string& where_) {
    if (app() != nullptr) {
        app()->getDebugTools().log("[@" + where_ + "]: " +
            message, LogMessageImportance::Critical);
    }

    throw exception(message);
}
