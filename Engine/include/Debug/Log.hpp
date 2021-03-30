#ifndef _LOG_H
#define _LOG_H

#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <iomanip>


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
#define Log_Release(message) (Debug::Log(message, __FILENAME__, __func__, __LINE__, Debug::LogLevel::L_RELEASE))
#define Log_Error(message) (Debug::Log(message, __FILENAME__, __func__, __LINE__, Debug::LogLevel::L_ERROR))
#define Log_Warning(message) (Debug::Log(message, __FILENAME__, __func__, __LINE__, Debug::LogLevel::L_WARNING))
#define Log_Info(message) (Debug::Log(message, __FILENAME__, __func__, __LINE__, Debug::LogLevel::L_INFO))
#define Log_Debug(message) (Debug::Log(message, __FILENAME__, __func__, __LINE__, Debug::LogLevel::L_DEBUG))
#endif


namespace Debug
{

    enum class LogLevel
    {
        L_RELEASE, L_ERROR, L_WARNING, L_INFO, L_DEBUG
    };

    static LogLevel logLevel = LogLevel::L_DEBUG;

    void Log(const char *message, const char *file, const char *function, unsigned int line,
             LogLevel logLvl = LogLevel::L_DEBUG)
    {

        if (logLvl > logLevel)
            return;

        std::string logMessage;

        /* Get the Current Time */
        time_t time = std::time(nullptr);
        tm localTime = *std::localtime(&time);
        std::ostringstream oss;
        oss << std::put_time(&localTime, "%H:%M:%S");

        char *levelString;

        switch (logLvl)
        {
            case LogLevel::L_RELEASE:
                levelString = "RELEASE";
                break;
            case LogLevel::L_ERROR:
                levelString = "ERROR";
                break;
            case LogLevel::L_WARNING:
                levelString = "WARNING";
                break;
            case LogLevel::L_INFO:
                levelString = "INFO";
                break;
            default:
                levelString = "DEBUG";
                break;

        }
        printf("%s %s : %s : %s() l[%s] : %s\n", oss.str().c_str(), levelString, file, function,
               std::to_string(line).c_str(), message);
    }
}
#endif // _LOG_H
