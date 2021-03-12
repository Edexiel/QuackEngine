#ifndef _ASSERTION_H_
#define _ASSERTION_H_

#include <iostream>
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

//#ifdef DEVELOPPEMENT
  #define Assert_Release(check, message) (Debug::Assert(check, message, __FILENAME__, __func__, __LINE__, Debug::AssertLevel::A_RELEASE))
  #define Assert_Fatal_Error(check, message) (Debug::Assert(check, message, __FILENAME__, __func__, __LINE__, Debug::AssertLevel::A_FATAL_ERROR))
  #define Assert_Error(check, message) (Debug::Assert(check, message, __FILENAME__, __func__, __LINE__, Debug::AssertLevel::A_ERROR))
  #define Assert_Warning(check, message) (Debug::Assert(check, message, __FILENAME__, __func__, __LINE__, Debug::AssertLevel::A_WARNING))
//#endif
#ifdef RELEASE
  #define Assert_Release(check, message) (check)
  #define Assert_Fatal_Error(check, message) (check)
  #define Assert_Error(check, message) (check)
  #define Assert_Warning(check, message) (check)
#endif

namespace Debug
{

enum class AssertLevel {    A_RELEASE,
                            A_FATAL_ERROR, // The program will stop immediately if the error is true
                            A_ERROR,        // The program will stop when the function DisplayAssertion is called if the error is true
                            A_WARNING       // Don't stop the program
};

static AssertLevel assertLevel = AssertLevel::A_WARNING;

bool Assert(bool check, const char* message, const char* file, const char* function, unsigned int line, AssertLevel assertLvl = AssertLevel::A_WARNING)
{

  if (!check)
    return false;

  if (assertLvl > assertLevel)
    return false;

  std::string assertMessage;

  /* Get the Current Time */
  time_t time = std::time(nullptr);
  tm localTime = *std::localtime(&time);
  std::ostringstream oss;
  oss << std::put_time(&localTime, "%H:%M:%S");

  /* Get file info */
  std::string location = std::string(" ") + file + " : " + function + "() l[" + std::to_string(line) + "] : ";


  switch (assertLvl)
  {
  case AssertLevel::A_RELEASE:      assertMessage = oss.str() + " RELEASE : "     + location + message    + "\n"; fprintf(stderr,"%s", assertMessage.c_str()); fflush(stderr); exit(70658465); return true;
  case AssertLevel::A_FATAL_ERROR:  assertMessage = oss.str() + " FATAL_ERROR : " + location + message    + "\n"; fprintf(stderr,"%s", assertMessage.c_str()); fflush(stderr); exit(70658465); return true;
  case AssertLevel::A_ERROR:        assertMessage = oss.str() + " ERROR : "       + location + message    + "\n"; fprintf(stderr,"%s", assertMessage.c_str()); fflush(stderr); exit(70658465); return true;
  default:                          assertMessage = oss.str() + " WARNING : "     + location + message    + "\n"; fprintf(stderr,"%s", assertMessage.c_str()); fflush(stderr); return true;
  }
  return false;
}
}

#endif // _ASSERTION_H_
