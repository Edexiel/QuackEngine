#ifndef _LOG_H
#define _LOG_H

#include <chrono>
#include <string>
#include <ctime>
#include <fmt/core.h>
#include <fmt/color.h>


#ifdef NDEBUG
#define Log_Release(...) Debug::Log(fmt::format(__VA_ARGS__), __FILE__, __LINE__, Debug::LOG_LEVEL::L_RELEASE)
#define Log_Error(...) Debug::Log(fmt::format(__VA_ARGS__), __FILE__, __LINE__, Debug::LOG_LEVEL::L_ERROR)
#define Log_Warning(...) Debug::Log(fmt::format(__VA_ARGS__), __FILE__, __LINE__, Debug::LOG_LEVEL::L_WARNING)
#define Log_Info(...)
#define Log_Debug(...)
#else
#define Log_Release(...) Debug::Log(fmt::format(__VA_ARGS__), __FILE__, __LINE__, Debug::LOG_LEVEL::L_RELEASE)
#define Log_Error(...) Debug::Log(fmt::format(__VA_ARGS__), __FILE__, __LINE__, Debug::LOG_LEVEL::L_ERROR)
#define Log_Warning(...) Debug::Log(fmt::format(__VA_ARGS__), __FILE__, __LINE__, Debug::LOG_LEVEL::L_WARNING)
#define Log_Info(...) Debug::Log(fmt::format(__VA_ARGS__), __FILE__, __LINE__, Debug::LOG_LEVEL::L_INFO)
#define Log_Debug(...) Debug::Log(fmt::format(__VA_ARGS__), __FILE__, __LINE__, Debug::LOG_LEVEL::L_DEBUG)
#endif


namespace Debug
{

    enum class LOG_LEVEL
    {
        L_RELEASE, L_ERROR, L_WARNING, L_INFO, L_DEBUG
    };

    inline static LOG_LEVEL logLevel = LOG_LEVEL::L_DEBUG;

    inline void
    Log(const std::string &message, const char *file, unsigned int line, LOG_LEVEL logLvl = LOG_LEVEL::L_DEBUG)
    {

        if (logLvl > logLevel)
            return;

        std::string logMessage;

        /* Get the Current Time */
        time_t time = std::time(nullptr);
        tm *localTime = std::localtime(&time);
        const std::string stime = fmt::format("{}:{}:{}", localTime->tm_hour, localTime->tm_min, localTime->tm_sec);

        const char *levelString;
        fmt::color color;
        switch (logLvl)
        {
            case LOG_LEVEL::L_RELEASE:
                levelString = "RELEASE";
                color = fmt::color::white;
                break;
            case LOG_LEVEL::L_ERROR:
                levelString = "ERROR";
                color = fmt::color::red;
                break;
            case LOG_LEVEL::L_WARNING:
                levelString = "WARNING";
                color = fmt::color::yellow;
                break;
            case LOG_LEVEL::L_INFO:
                levelString = "INFO";
                color = fmt::color::forest_green;
                break;
            default:
                levelString = "DEBUG";
                color = fmt::color::coral;
                break;

        }
#if 1
        fmt::print(fg(color), "[{}][{}] {}:{} {}\n", stime, levelString, file, line, message);
#else
        fmt::print("[{}][{}] {}:{} {}\n", stime, levelString, file, line, message);
#endif

    }
}
#endif // _LOG_H
