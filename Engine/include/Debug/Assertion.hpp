#ifndef _ASSERTION_H_
#define _ASSERTION_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>

#ifdef WIN32
# include <io.h>
#define __FILENAME__ (strrchr(__FILE__,'\\')+1)
#endif
#ifdef LINUX
#include <cstring>
#define __FILENAME__ (strrchr(__FILE__,'/')+1)
#endif

#ifdef NDEBUG
#define Assert_Release(check, message)(check)
  #define Assert_Fatal_Error(check, message)(check)
  #define Assert_Error(check, message)(check)
  #define Assert_Warning(check, message)(check)
#else
  #define Assert_Release(check, message) (Debug::Assert(check, message, __FILENAME__, __func__, __LINE__, Debug::AssertLevel::A_RELEASE))
  #define Assert_Fatal_Error(check, message) (Debug::Assert(check, message, __FILENAME__, __func__, __LINE__, Debug::AssertLevel::A_FATAL_ERROR))
  #define Assert_Error(check, message) (Debug::Assert(check, message, __FILENAME__, __func__, __LINE__, Debug::AssertLevel::A_ERROR))
  #define Assert_Warning(check, message) (Debug::Assert(check, message, __FILENAME__, __func__, __LINE__, Debug::AssertLevel::A_WARNING))
#endif


namespace Debug
{

  enum class AssertLevel {  A_RELEASE = 0,
                            A_FATAL_ERROR, // The program will stop immediately if the error is true
                            A_ERROR,        // The program will stop when the function DisplayAssertion is called if the error is true
                            A_WARNING       // Don't stop the program
                         };

  static AssertLevel assertLevel = AssertLevel::A_WARNING;

  inline bool Assert(bool check, const char* message, const char* file, const char* function, unsigned int line, AssertLevel assertLvl = AssertLevel::A_WARNING)
  {

    if (!check)
      return false;

    if (assertLvl > assertLevel)
      return false;

    /* Get the Current Time */
    time_t time = std::time(nullptr);
    tm* localTime = std::localtime(&time);
    std::ostringstream oss;
    oss << std::put_time(localTime, "%H:%M:%S");

    const char* levelString;

    switch (assertLvl)
    {
    case AssertLevel::A_RELEASE:      levelString = "RELEASE";      break;
    case AssertLevel::A_FATAL_ERROR:  levelString = "FATAL_ERROR";  break;
    case AssertLevel::A_ERROR:        levelString = "ERROR";        break;
    default:                          levelString = "WARNING";      break;

    }
    printf("%s %s : %s : %s() l[%s] : %s\n", oss.str().c_str(), levelString, file, function, std::to_string(line).c_str(), message);

    if (assertLvl < AssertLevel::A_WARNING)
    {
      exit(5);
    }
    return true;
  }
}

#endif // _ASSERTION_H_
