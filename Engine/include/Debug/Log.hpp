#ifndef _LOG_H
#define _LOG_H

#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <fmt/core.h>
#include <fmt/color.h>


#ifdef WIN32
# include <io.h>
#define __FILENAME__ (strrchr(__FILE__,'\\')+1)
#endif
#ifdef LINUX
#define __FILENAME__ (strrchr(__FILE__,'/')+1)
#endif

#ifdef NDEBUG

#define Log_Release(message)
#define Log_Error(message)
#define Log_Warning(message)
#define Log_Info(message)
#define Log_Debug(message)
#else
#define Log_Release(message) (Debug::Log(message, __FILE__, __LINE__, Debug::LOG_LEVEL::L_RELEASE))
#define Log_Error(message) (Debug::Log(message, __FILE__, __LINE__, Debug::LOG_LEVEL::L_ERROR))
#define Log_Warning(message) (Debug::Log(message, __FILE__, __LINE__, Debug::LOG_LEVEL::L_WARNING))
#define Log_Info(message) (Debug::Log(message, __FILE__, __LINE__, Debug::LOG_LEVEL::L_INFO))
#define Log_Debug(message) (Debug::Log(message, __FILE__, __LINE__, Debug::LOG_LEVEL::L_DEBUG))
#endif


namespace Debug
{
    enum class LOG_LEVEL
    {
        L_RELEASE, L_ERROR, L_WARNING, L_INFO, L_DEBUG
    };

    inline static LOG_LEVEL logLevel = LOG_LEVEL::L_DEBUG;

    inline void Log(const char *message, const char *file, unsigned int line,
                    LOG_LEVEL logLvl = LOG_LEVEL::L_DEBUG)
    {

        if (logLvl > logLevel)
            return;

        std::string logMessage;

        /* Get the Current Time */
        time_t time = std::time(nullptr);
        tm localTime = *std::localtime(&time);
        std::ostringstream oss;
        oss << std::put_time(&localTime, "%H:%M:%S");

        const char *levelString;
        fmt::color color = fmt::color::white;
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
                color = fmt::color::steel_blue;
                break;
            default:
                levelString = "DEBUG";
                color = fmt::color::coral;
                break;

        }
        fmt::print(fg(color), "{} [{}] {}:{} {}\n", oss.str(), levelString, file, line, message);
    }
}
#endif // _LOG_H
