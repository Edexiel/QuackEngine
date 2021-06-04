#ifndef _ASSERTION_H_
#define _ASSERTION_H_

#include <string>
#include <chrono>
#include <ctime>
#include <fmt/core.h>
#include <fmt/color.h>

#ifdef NDEBUG
#define Assert_Release(check, ...)(check)
#define Assert_Fatal_Error(check, ...)(check)
#define Assert_Error(check, ...)(check)
#define Assert_Warning(check, ...)(check)
#else
#define Assert_Release(check, ...) (Debug::Assert(check, fmt::format(__VA_ARGS__), __FILE__, __LINE__, Debug::AssertLevel::A_RELEASE))
#define Assert_Fatal_Error(check, ...) (Debug::Assert(check, fmt::format(__VA_ARGS__), __FILE__, __LINE__, Debug::AssertLevel::A_FATAL_ERROR))
#define Assert_Error(check, ...) (Debug::Assert(check, fmt::format(__VA_ARGS__), __FILE__, __LINE__, Debug::AssertLevel::A_ERROR))
#define Assert_Warning(check, ...) (Debug::Assert(check, fmt::format(__VA_ARGS__), __FILE__, __LINE__, Debug::AssertLevel::A_WARNING))
#endif


namespace Debug
{

    enum class AssertLevel
    {
        A_RELEASE = 0,
        A_FATAL_ERROR, // The program will stop immediately if the error is true
        A_ERROR,        // The program will stop when the function DisplayAssertion is called if the error is true
        A_WARNING       // Don't stop the program
    };

    static AssertLevel assertLevel = AssertLevel::A_WARNING;

    inline bool Assert(bool check, const std::string &message, const char *file, unsigned int line,
                       AssertLevel assertLvl = AssertLevel::A_WARNING)
    {

        if (!check)
            return false;

        if (assertLvl > assertLevel)
            return false;

        /* Get the Current Time */
        time_t time = std::time(nullptr);
        tm *localTime = std::localtime(&time);
        const std::string stime = fmt::format("{}:{}:{}", localTime->tm_hour, localTime->tm_min, localTime->tm_sec);

        const char *levelString;

        switch (assertLvl)
        {
            case AssertLevel::A_RELEASE:
                levelString = "RELEASE";
                break;
            case AssertLevel::A_FATAL_ERROR:
                levelString = "FATAL_ERROR";
                break;
            case AssertLevel::A_ERROR:
                levelString = "ERROR";
                break;
            default:
                levelString = "WARNING";
                break;

        }
#if LINUX
        fmt::print(fg(fmt::color::red),"[{}][{}] {}:{} {}\n", stime, levelString, file, line, message);
#else
        fmt::print("[{}][{}] {}:{} {}\n", stime, levelString, file, line, message);

#endif
        if (assertLvl < AssertLevel::A_WARNING)
        {
            exit(5);
        }
        return true;
    }
}

#endif // _ASSERTION_H_
