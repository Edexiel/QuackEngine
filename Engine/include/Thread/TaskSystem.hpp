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
        std::function<void(Args...)> function;
        std::tuple<Args...> args;


        /* ==== Function ==== */

        Task(){};

        Task(std::function<void(Args...)> F, std::tuple<Args...> _args)
        {
            function = F;
            args = _args;
        };

        virtual void operator()() override
        {
            if (function)
            {
                std::apply(function, args);
            }
        };


        virtual void Execute() override
        {
            if (function)
            {
                std::apply(function, args);
            }
        };
    };

    class LongTask : public TaskInterface
    {
    public:
        std::vector<std::shared_ptr<TaskInterface>> taskList;

        virtual void Execute() override;

        void AddTask(std::shared_ptr<TaskInterface> tsk);
    };

    class TaskSystem
    {
    public:

        std::queue<std::shared_ptr<TaskInterface>> taskList;

        void AddTask(std::shared_ptr<TaskInterface> tsk);

    };
}