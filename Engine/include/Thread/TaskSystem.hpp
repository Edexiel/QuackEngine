#pragma once

#include <functional>
#include <tuple>
#include <utility>
#include <memory>
#include <queue>
#include <mutex>

namespace Thread
{
    class TaskInterface
    {
        public:

        /* ==== Function ==== */
        TaskInterface(){};

        virtual void Execute(){};
        virtual void operator()(){};
    };


    template <typename... Args>
    class Task : public TaskInterface
    {
        public:

        /* ==== Variable ==== */
        std::function<void(Args...)> _function;
        std::tuple<Args...> _args;


        /* ==== Function ==== */

        Task(){};

        Task(std::function<void(Args...)> function, std::tuple<Args...> args)
        {
            _function = function;
            _args = args;
        };

        virtual void operator()() override
        {
            if (_function)
            {
                std::apply(_function, _args);
            }
        };


        virtual void Execute() override
        {
            if (_function)
            {
                std::apply(_function, _args);
            }
        };
    };

    class TaskSystem
    {
    public:

        std::queue<std::unique_ptr<TaskInterface>> _taskList;

        void AddTask(TaskInterface* tsk);

    };
}