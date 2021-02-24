#ifndef _ASSERTION_H_
#define _ASSERTION_H_

#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

namespace Debug
{

    enum AssertionLevel {A_FATAL_ERROR, // The program will stop immediately if the error is true
                        A_ERROR,        // The program will stop when the function DisplayAssertion is called if the error is true
                        A_WARNING       // Don't stop the program
                        };              // The exit code is in Ascii

    class Assertion
    {
    public:

        static bool shouldExit;
        static AssertionLevel AssertionLevel;
        static std::vector<Assertion> AssertionList;

        Assertion(bool check, int line, std::string file, const std::string& message, enum AssertionLevel assertionLvl = AssertionLevel::A_WARNING)
        {
            if (!check)
                return;

            time_t time = std::time(nullptr);
            tm localTime = *std::localtime(&time);
            std::ostringstream oss;
            oss << std::put_time(&localTime, "%H:%M:%S");

            AssertionMessage = oss.str();
            AssertionMessage += " in file \"" + file + "\" l:" + std::to_string(line) + " " + AssertionLevelToString(assertionLvl) + " : " + message + "\n";

            if (assertionLvl == A_FATAL_ERROR)
            {
                std::cout << AssertionMessage << std::endl;
                exit(70658465);
            }
            else if (assertionLvl == A_ERROR)
            {
                shouldExit = true;
            }
            
            AssertionList.push_back(*this);
        }

        static void DisplayAssertion()
        {
            for (unsigned int i = 0; i < AssertionList.size(); i++)
            {
                std::cout << AssertionList[i].AssertionMessage;
            }
            AssertionList.clear();
            if (shouldExit)
                exit(69827982);
        }

    private:
        std::string AssertionMessage;

        Assertion()
        {
            AssertionList.push_back(*this);
        }

        void DisplayMessage()
        {
            AssertionMessage += "\n";
            fprintf(stderr, "%s", AssertionMessage.c_str());
            fflush(stderr);
        }

        std::string AssertionLevelToString(enum AssertionLevel AssertionLV)
        {
            switch (AssertionLV)
            {
                case A_FATAL_ERROR:   return  "FATAL_ERROR";
                case A_ERROR:         return  "ERROR";
                default:               return  "WARNING";
            }
            return "";
        }
    };
}

std::vector<Debug::Assertion>   Debug::Assertion::AssertionList   = std::vector<Debug::Assertion>();
bool                            Debug::Assertion::shouldExit      = false;

#endif // _ASSERTION_H_
