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

//#ifdef DEVELOPPEMENT
    #define Log_Release(message) (Debug::Log(message, __FILENAME__, __func__, __LINE__, Debug::LogLevel::L_RELEASE))
    #define Log_Error(message) (Debug::Log(message, __FILENAME__, __func__, __LINE__, Debug::LogLevel::L_ERROR))
    #define Log_Warning(message) (Debug::Log(message, __FILENAME__, __func__, __LINE__, Debug::LogLevel::L_WARNING))
    #define Log_Info(message) (Debug::Log(message, __FILENAME__, __func__, __LINE__, Debug::LogLevel::L_INFO))
    #define Log_Debug(message) (Debug::Log(message, __FILENAME__, __func__, __LINE__, Debug::LogLevel::L_DEBUG))
//#endif
#ifdef RELEASE
    #define Log_Release(message) (message)
    #define Log_Error(message) (message)
    #define Log_Warning(message) (message)
    #define Log_Info(message) (message)
    #define Log_Debug(message) (message)
#endif

namespace Debug
{

    enum class LogLevel {L_RELEASE, L_ERROR, L_WARNING, L_INFO, L_DEBUG};

    static LogLevel logLevel = LogLevel::L_DEBUG;
    void Log(const char* message, const char* file, const char* function, unsigned int line, LogLevel logLvl = LogLevel::L_DEBUG)
    {

      if (logLvl > logLevel)
        return;

      std::string logMessage;

      /* Get the Current Time */
      time_t time = std::time(nullptr);
      tm localTime = *std::localtime(&time);
      std::ostringstream oss;
      oss << std::put_time(&localTime, "%H:%M:%S");

      /* Get file info */
      std::string location = std::string(" ") + file + " : " + function + "() l[" + std::to_string(line) + "] : ";


      switch (logLvl)
      {
      case LogLevel::L_RELEASE:   logMessage = oss.str() + " RELEASE : "  + location + message    + "\n"; printf( "%s", logMessage.c_str()); return;
      case LogLevel::L_ERROR:     logMessage = oss.str() + " ERROR : "    + location + message    + "\n"; printf( "%s", logMessage.c_str()); return;
      case LogLevel::L_WARNING:   logMessage = oss.str() + " WARNING : "  + location + message    + "\n"; printf( "%s", logMessage.c_str()); return;
      case LogLevel::L_INFO:      logMessage = oss.str() + " INFO : "     + location + message    + "\n"; printf( "%s", logMessage.c_str()); return;
      default:                    logMessage = oss.str() + " DEBUG : "    + location + message    + "\n"; printf( "%s", logMessage.c_str()); return;

      }
    }
}
#endif // _LOG_H
