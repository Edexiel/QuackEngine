#ifndef _LOG_H
#define _LOG_H

#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

namespace Debug
{

    enum class LogLevel {L_RELEASE, L_ERROR, L_WARNING, L_INFO, L_DEBUG};

    class Log
    {
    public:

        static LogLevel logLevel;
        static std::vector<Log> logList;

        Log(const std::string& message, LogLevel logLvl = L_DEBUG)
        {
            if (logLvl > logLevel)
                return;

            /* Get the Current Time */
            time_t time = std::time(nullptr);
            tm localTime = *std::localtime(&time);
            std::ostringstream oss;
            oss << std::put_time(&localTime, "%H:%M:%S");

            logMessage = oss.str();
            logMessage += " " + LogLevelToString(logLvl) + " : " + message + "\n";

            
            logList.push_back(*this);
        }

        static void DisplayLog()
        {
            for (unsigned int i = 0; i < logList.size(); i++)
            {
                std::cout << logList[i].logMessage;
            }
            logList.clear();
        }

    private:
        std::string logMessage;

        Log()
        {
            logList.push_back(*this);
        }

        void DisplayMessage()
        {
            logMessage += "\n";
            fprintf(stderr, "%s", logMessage.c_str());
            fflush(stderr);
        }

        std::string LogLevelToString(LogLevel logLV)
        {
            switch (logLV)
            {
                case L_RELEASE:   return  "RELEASE";
                case L_ERROR:     return  "ERROR";
                case L_WARNING:   return  "WARNING";
                case L_INFO:      return  "INFO";
                default:        return    "DEBUG";
                
            }
            return "";
        }
    };
}

Debug::LogLevel         Debug::Log::logLevel = Debug::LogLevel::L_DEBUG;
std::vector<Debug::Log> Debug::Log::logList  = std::vector<Debug::Log>();

#endif // _LOG_H
