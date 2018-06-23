#include <ios>
#include <iostream>

#include "GameEngine/Utility/debug.h"


GE_BEGIN_ENGINE_NAMESPACE

TLogger::PLogger TLogger::instance { nullptr };
const size_t TLogger::DefaultBufferSize = 512;

TLogger& TLogger::GetInstance() {
    if (instance == nullptr) {
        instance = std::make_unique<TLogger>(nullptr);
    }
    return instance;
}

TLogger::TLogger(TOutputStream* os) {
    ASSERT(instance == nullptr, "Expected uninitialized logger.");

    outputStream = os;

    buffer.reserve(DefaultBufferSize);
}

void TLogger::initialize(TOutputStream* os, ELogMessageLevel minLevel) {
    GetInstance()->setStream(os);
    GetInstance()->setThreshold(minLevel);
}

void TLogger::flush() {
    if (outputStream != nullptr) {
        for (auto& line : buffer) {
            outputStream << line;
        }
        outputStream.flush();
        buffer.clear();
    }
}

void TLogger::setStream(TOutputStream* os) {
    flush();
    outputStream = os;
}

void TLogger::log(const TString& message, ELogMessageLevel level,
    const TString& position)
{
    if (static_cast<int>(level) < static_cast<int>(minLevel)) {
        return;
    }

    if (buffer.capacity() <= buffer.size() + 1) {
        flush();
    }

    buffer.emplace_back(
        "[" + toString(level) + "] " +
        "[" + position + "]: " +
        message);
}

TString TLogger::toString(ELogMessageLevel level) const {
    switch (level) {
        case ELogMessageLevel::Trace:
            return "Trace";
        case ELogMessageLevel::Debug:
            return "Debug";
        case ELogMessageLevel::Normal:
            return "Normal";
        case ELogMessageLevel::Warning:
            return "Warning";
        case ELogMessageLevel::Fatal:
            return "Fatal";
        default:
            GE_THROW("Unknown log message level");
    }
}

const char* TLogger::GetFileName(const char* path) {
    const char* base = std::strrchr(filePath, '/');
    if (!base)
    {
        base = std::strrchr(filePath, '\\'); // for Windows platform
    }

    return base ? (base + 1) : filePath;
}

GE_END_ENGINE_NAMESPACE
